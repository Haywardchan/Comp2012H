#include <algorithm>
#include <numeric>
#include "dataset.h"
#include "nn.h"
using namespace std;

void training(NN&, dataset&, const size_t&);
void testing(NN&, dataset&);

void nn_training_testing(dataset& data){		
	NN nn {
		new LayerLinear(PIXELS, 32),
		new LayerSigmoid,
		new LayerLinear(32   , 16),
		new LayerSigmoid,
		new LayerLinear(16   , 10),
		new LayerSigmoid,
	};

	for (size_t epoch = 0; epoch < 10; epoch++)
	{	
		training(nn, data, epoch);
		testing(nn, data);
	}	
}


void training(NN& nn, dataset& data, const size_t& epoch){
	vector<size_t> Sequence(data.get_data_size(TRAIN_LABEL));
	iota(Sequence.begin(), Sequence.end(), 0);
	random_shuffle(Sequence.begin(), Sequence.end());

	printf("================ Epoch %lu ================\n", epoch+1);

	for (size_t i = 0; i < Sequence.size(); i++) {
		vector<float> input = data.get_a_normalized_image(TRAIN_IMAGE, Sequence[i]);
		vector<float> one_hot_label(10);
		one_hot_label[data.get_a_label(TRAIN_LABEL, Sequence[i])] = 1;
		
		nn.backprop(input, one_hot_label);

		if ((i + 1) % 10 == 0)
			nn.apply();

		if ((i + 1) % 500 == 0) {
			printf("Epoch %lu: %lu / %lu\r", epoch+1, i+1, Sequence.size());
			fflush(stdout);
		}
	}
}


void testing(NN& nn, dataset& data){
	// START OF YOUR IMPLEMENTATION
	//initialize a float vector filled with 0 of size 11
	vector<float>freq(11, 0);
	vector<float>total_freq(10, 0);
	int size=data.get_data_size(TEST_LABEL);
	//fed the data using normalized images
	for(int i=0;i<size;i++){
		vector<float>img=nn(data.get_a_normalized_image(TEST_IMAGE, i));
		int max = 0;
		for (int i = 1; i < 10; i++) {
			max=(img[i]>img[max])?i:max;
		}
		// printf("%d",max);
		int answer=data.get_a_label(TEST_LABEL, i);
		if(max==answer)freq[max]+=1;
		total_freq[answer]+=1;
	}
	for(int i=0;i<10;i++)freq[10]+=freq[i];
	//print result
	if(size==0)size=1;
	printf("Overall accuracy: %.2f%\n",freq[10]/size *100);
	for(int i=0;i<10;i++){
		if(total_freq[i]==0)total_freq[i]=1;
		printf("Accuracy for digit %d: %.2f%\n",i,freq[i]/total_freq[i] *100);
	}
	//print freq list
	// for(int i=0;i<10;i++)printf("%d\n",freq[i]);
	// END OF YOUR IMPLEMENTATION
}


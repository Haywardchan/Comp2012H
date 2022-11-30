#include <algorithm>
#include <numeric>
#include "roy_dataset.h"
#include "nn.h"
#include <iostream>
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
	vector<float> input, output, print;
	int index, count {0}, digit_count;
	for (int i = 0; i < 10; i++){
		print.push_back(0);
	}
	for (int i = 0; i < data.get_data_size(TEST_IMAGE); i++){
		digit_count = 0;
		input = data.get_a_normalized_image(TEST_IMAGE, i);
		output = nn(input);
		index = max_element(output.begin(), output.end()) - output.begin();
		if (index == data.get_a_label(TEST_LABEL, i)){
			print[i]++;
			count++;
		}
	}

	int digit, rounded, percentage, decimal; 
	uint8_t compare {0};
	int total_digit_count {0};
	vector<int> output_stream;
	
	for (int i = 0; i < print.size(); i++, compare++, total_digit_count += digit_count){
		digit_count = 0;
		for (size_t j = 0; j < data.get_data_size(TEST_LABEL); j++){
			if ( compare == data.get_a_label(TEST_LABEL, j) ){
				digit_count++;	//total number of a specific integer
			}
		}

		digit = rounded = percentage = decimal = 0;
		print[i] = (print[i]*100000) / digit_count;
		digit = print[i] - (print[i]/10)*10;
		rounded = (digit > 4)? (print[i]/10 + 1) : (print[i]/10);
		percentage = rounded/100;
    	decimal = rounded - percentage*100;

		output_stream.push_back(percentage);
		output_stream.push_back(decimal);

	}

	digit = rounded = percentage = decimal = 0;
	total_digit_count = ( total_digit_count*100000 ) / data.get_data_size(TEST_LABEL);
	digit = total_digit_count - (total_digit_count / 10)*10;
	rounded = (digit > 4)? (total_digit_count/10 + 1) : (total_digit_count/10);
	percentage = rounded/100;
	decimal = rounded - percentage*100;

	cout << "Overall accuracy: " << percentage << '.' << decimal << '%' << endl;

	for (int i = 0; i < output_stream.size(); i++ ){
		if ( i%2 == 0 ){
			cout << "Accuracy for digit " << i << ": " << output_stream[i];
		}else{
			cout << '.' << output_stream[i] << '%' << endl;
		}
		 
	}
	return;
}

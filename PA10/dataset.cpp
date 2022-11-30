#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <random>
#include <functional>

#include "dataset.h"
using namespace std;


const char* PATH_TRAIN_LABELS = "train-labels-idx1-ubyte";
const char* PATH_TRAIN_IMAGES = "train-images-idx3-ubyte";
const char* PATH_TEST_LABELS = "t10k-labels-idx1-ubyte";
const char* PATH_TEST_IMAGES = "t10k-images-idx3-ubyte";


dataset::dataset(){;}


dataset::~dataset(){;}


void dataset::load_dataset() {
	ifstream fin;
	uint32_t MN, N, A, B;

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TRAIN_LABELS, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	N = __builtin_bswap32(N)/3;
	
	if (MN != 0x01080000) {
		cerr << "Invalid database" << endl;
		exit(1);
	}

	train_labels.resize(N);
	fin.read((char*)train_labels.data(), N * sizeof(uint8_t));

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TRAIN_IMAGES, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));

	N = __builtin_bswap32(N)/3;
	A = __builtin_bswap32(A);
	B = __builtin_bswap32(B);

	if (MN != 0x03080000 || A != COLS || B != ROWS) {
		cerr << "invalid database" << endl;
		exit(1);
	}

	train_images.resize(N);
	fin.read((char*)train_images.data(), N * sizeof(array<uint8_t, PIXELS>));

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TEST_LABELS, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	N = __builtin_bswap32(N)/3;

	if (MN != 0x01080000) {
		cerr << "Invalid database" << endl;
		exit(1);
	}

	test_labels.resize(N);
	fin.read((char*)test_labels.data(), N * sizeof(uint8_t));

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TEST_IMAGES, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));

	N = __builtin_bswap32(N)/3;
	A = __builtin_bswap32(A);
	B = __builtin_bswap32(B);

	if (MN != 0x03080000 || A != COLS || B != ROWS) {
		cerr << "invalid database" << endl;
		exit(1);
	}

	test_images.resize(N);
	fin.read((char*)test_images.data(), N * sizeof(array<uint8_t, PIXELS>));
}


void dataset::remove_some_train_data(const uint8_t digit, const size_t size){
	// START OF YOUR IMPLEMENTATION
	//assume size < number of digits and digit in [0,9]
	int count=0;
	vector<uint8_t>::iterator it1 = train_labels.end()-1;
	vector<array<uint8_t, PIXELS>>::iterator it2 = train_images.end()-1;
	while(count<size){
		if(*it1==digit){
			it1=train_labels.erase(it1);
			it2=train_images.erase(it2);
			count++;
		}
		it1--; it2--;
	}

	// END OF YOUR IMPLEMENTATION
}


void dataset::append_some_augmented_train_data(const uint8_t digit, const size_t size){
    vector<size_t> indices;
	unsigned int counter = 0;

    for (vector<uint8_t>::iterator it = train_labels.begin(); it != train_labels.end(); it++) {
        if (*it == digit){
			indices.push_back(distance(train_labels.begin(), it));
		}
    }

	vector<size_t>::iterator it2 = indices.begin();
	while(counter<size){	
		++counter;

		train_images.push_back(this->compound_augment_image(train_images[*it2]));
		train_labels.push_back(digit);
		
		it2++;
		if(it2 == indices.end())
			it2 = indices.begin();
	}
}


array<uint8_t, PIXELS> dataset::compound_augment_image(array<uint8_t, PIXELS>& img_ar){
	img_dt img = convert_image_dt(img_ar);
	size_t rand_num = rand()% 8;
	this->shift_image(img, shift_type(rand_num), rand()% 4);

	rand_num = rand()% 9 + ROWS - 4;
	this->resize_image(img, rand_num, rand_num);
	if(rand_num>ROWS){
		this->crop_image(img, (rand_num-ROWS)/2, (rand_num-COLS)/2, ROWS, COLS);
	}
	else{
		this->padding_image(img, (ROWS-rand_num)/2, ROWS-(ROWS-rand_num)/2-rand_num, (COLS-rand_num)/2, COLS-(COLS-rand_num)/2-rand_num);
	}

	array<uint8_t, PIXELS> img_ar_out = convert_image_dt(img);

	return img_ar_out;
}


void dataset::shift_image(img_dt& img, const enum shift_type dir, const size_t p, const uint8_t value){
	// START OF YOUR IMPLEMENTATION
	int rows = img.size();
	int cols= img[0].size();
	int v=value;

	//void crop_image(img_dt& img, const size_t y0, const size_t x0, 
	//const size_t new_rows, const size_t new_cols);

    //void padding_image(img_dt& img, const size_t top=0, const size_t down=0, 
	//const size_t left=0, const size_t right=0, const uint8_t value=0);
	switch(dir){//LEFT, RIGHT,  UP, DOWN, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT
		case LEFT:
			crop_image(img,0,p,rows,cols-p);
			padding_image(img,0,0,0,p,v);
			break;
															case RIGHT:
																crop_image(img,0,0,rows,cols-p);
																padding_image(img,0,0,p,0,v);
																break;
		case UP:
			crop_image(img,p,0,rows-p,cols);
			padding_image(img,0,p,0,0,v);
			break;
															case DOWN:
																crop_image(img,0,0,rows-p,cols);
																padding_image(img,p,0,0,0,v);
																break;
		case UPLEFT:
			crop_image(img,0,p,rows,cols-p);
			padding_image(img,0,0,0,p,v);
			crop_image(img,p,0,rows-p,cols);
			padding_image(img,0,p,0,0,v);
			break;
															case UPRIGHT:
																crop_image(img,0,0,rows,cols-p);
																padding_image(img,0,0,p,0,v);
																crop_image(img,p,0,rows-p,cols);
																padding_image(img,0,p,0,0,v);
																break;
		case DOWNLEFT:
			crop_image(img,0,0,rows-p,cols);
			padding_image(img,p,0,0,0,v);
			crop_image(img,0,p,rows,cols-p);
			padding_image(img,0,0,0,p,v);
			break;
															case DOWNRIGHT:
																crop_image(img,0,0,rows-p,cols);
																padding_image(img,p,0,0,0,v);
																crop_image(img,0,0,rows,cols-p);
																padding_image(img,0,0,p,0,v);
																break;
		default:return;
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::resize_image(img_dt& img, const size_t new_rows, const size_t new_cols){
	// START OF YOUR IMPLEMENTATION
	img_dt resized_img(new_rows,deque<uint8_t>(new_cols));
	int rows = img.size();
	int cols=img[0].size();
	for(int i=0;i<new_rows;i++){
		for(int j=0;j<new_cols;j++){
		//for every new pixel find its nearest neighbour pixel
			//choose bottom right as default by round up using original coordinates in scale
			double nx=(i+0.5)/new_rows*rows;
			double ny=(j+0.5)/new_cols*cols;
			int coordinate_x=nx;
			int coordinate_y=ny;
			while(coordinate_x>cols-1)coordinate_x--;
			while(coordinate_y>rows-1)coordinate_y--;
			resized_img[i][j]=img[coordinate_x][coordinate_y];
		}
	}
	//copy converter
	img=resized_img;
	// END OF YOUR IMPLEMENTATION
}


void dataset::crop_image(img_dt& img, const size_t y0, const size_t x0, const size_t new_rows, const size_t new_cols){
	// START OF YOUR IMPLEMENTATION
	int row=(int)y0;
	int col=(int)x0;
	// row=3;
	// col=1;
	int rows=img.size();
	int cols=img[0].size();
	// printf("r%dc%d\n",rows,cols);
	int reduced_rows=rows-(int)new_rows-row;
	int reduced_cols=cols-(int)new_cols-col;
	//crop row
	for(int i=0;i<row;i++){
		img.pop_front();
		// printf("popped a row of deque\n");
	}
	for(int i=0;i<reduced_rows;i++){
		img.pop_back();
		// printf("popped a row of deque at back\n");
	}
	//crop col
	for(int i=0;i<rows;i++){
		for(int j=0;j<col;j++){
			img[i].pop_front();
			// if(i==0)printf("popped a col\n");
		}
		for(int j=0;j<reduced_cols;j++){
			img[i].pop_back();
			// if(i==0)printf("popped a col at back\n");
		}
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::padding_image(img_dt& img, const size_t top, const size_t down, const size_t left, const size_t right, const uint8_t value){
	// START OF YOUR IMPLEMENTATION
	int n_row=img.size()+top+down;
	int cols=img[0].size();
	int v=value;
	// printf("l%d r%d t%d d%d\n",left-2,right+1,top+2,down+2);//1 2 3 4
	for(int i=0;i<top;i++){
		img.push_front(deque<uint8_t>(cols,v));
		// printf("pushed top\n");
	}
	for(int i=0;i<down;i++){
		img.push_back(deque<uint8_t>(cols,v));
		// printf("pushed down\n");
	}
	for(int i=0;i<n_row;i++){
		for(int j=0;j<left;j++){
			img[i].push_front(v);
			// if(i==0)printf("pushed left\n");
		}
		for(int j=0;j<right;j++){
			img[i].push_back(v);
			// if(i==0)printf("pushed right\n");
		}
	}
	// END OF YOUR IMPLEMENTATION
}


uint8_t	dataset::get_a_label(const data_type mode, const size_t index) const{
	switch(mode){
		case TRAIN_LABEL: 
			return train_labels[index];		break;
		case TEST_LABEL: 
			return test_labels[index];		break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}


img_dt dataset::convert_image_dt(const array<uint8_t, PIXELS>& img) const {
	// START OF YOUR IMPLEMENTATION
	img_dt converted_img(ROWS,deque<uint8_t>(COLS,0));
	//in case not fixed size
	for(int i=0;i<ROWS;i++)converted_img[0].resize(COLS);
	converted_img.resize(ROWS);
	//assume img have fixed size as bounded
	for (int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++)
			converted_img[i][j]=img[i*COLS+j];
	}
	return converted_img;
	// END OF YOUR IMPLEMENTATION
}


array<uint8_t, PIXELS>  dataset::convert_image_dt(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	array<uint8_t, PIXELS> converted_img={0};
	if(img.size()==ROWS){
		for (int i = 0; i < ROWS; i++){
			if(img[i].size()==COLS){
				for(int j = 0; j < COLS; j++)
					converted_img[i*COLS+j]=img[i][j];
			}else throw invalid_argument("img col isnt sized as default COLS");
		}
	}else throw invalid_argument("img row isnt sized as default ROWS");
	return converted_img;
	// END OF YOUR IMPLEMENTATION
}


array<uint8_t, PIXELS>	dataset::get_an_image(const enum data_type mode, const size_t index) const{
	switch(mode){
		case TRAIN_IMAGE:
			return train_images[index];		break;
		case TEST_IMAGE: 
			return test_images[index];		break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}


vector<float>	dataset::get_a_normalized_image(const enum data_type mode, const size_t index) const{
	const array<uint8_t, PIXELS>& img = this->get_an_image(mode, index);
	vector<float> img_normalized(PIXELS);

	transform(img.begin(), img.end(), img_normalized.begin(), normalize(255.0f));
	return img_normalized;
}


size_t	dataset::get_data_size(const enum data_type mode) const{
	switch(mode){
		case TRAIN_LABEL: 
			return train_labels.size();		break;
		case TEST_LABEL:
			return test_labels.size();		break;
		case TRAIN_IMAGE: 
			return train_images.size();		break;
		case TEST_IMAGE: 
			return test_images.size();		break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}


void dataset::print_image(const array<uint8_t, PIXELS>& img_ar) const {
	// START OF YOUR IMPLEMENTATION
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLS;j++)
			printf("%4d",img_ar[i*COLS+j]);
		printf("\n");
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::print_image(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	//init as img size
	int rows=img.size();
	int cols=img[0].size();
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++)
			{printf("%4d",img[i][j]);}
		printf("\n");
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::print_statistic(const enum data_type mode) const{
	// START OF YOUR IMPLEMENTATION
	//create a const iterator for const vector
	vector<uint8_t>::const_iterator it;
	//create an array to store number of labels recognised for each set
	array<int,10>arr={0};
	switch(mode){
		case TEST_IMAGE:
			for(it=test_labels.begin();it!=test_labels.end();it++){
				int data=*it;
				arr[data]++;
			}
			for(int i=0;i<10;i++){
				printf("Number of test images for digit %d: %d\n", i, arr[i]);
			}
			break;
		case TRAIN_IMAGE:
			for(it=train_labels.begin();it!=train_labels.end();it++){
				//iterate through the vector and dereference it for counting the number of labels
				int data=*it;
				arr[data]++;
			}
			//print corresponding result
			for(int i=0;i<10;i++){
				printf("Number of train images for digit %d: %d\n", i, arr[i]);
			}
			break;
	}
	// END OF YOUR IMPLEMENTATION
}

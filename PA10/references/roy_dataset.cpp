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

#include "roy_dataset.h"
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
	int id, start = train_labels.size() - 1;
	vector<uint8_t>::iterator p = train_labels.end();
	for (size_t i = 0; i < size; i++){
		p = find_if(p, train_labels.begin(), (*p == digit) );
		p--;
		for (int i = start; i >= 0; i--){
			if (train_labels[i] == digit){
				id = i;
				start = i - 1;
				train_labels.erase(p);
				break;
			}
		}
		train_images.erase( train_images.begin() + id );
	}

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

void shift_left(img_dt& img, const size_t p, const uint8_t value){
	for (int j = 0; j < ROWS ; j++){
        for (int i = 0; i < p ; i++){
            img.insert(img.begin()+j*ROWS+COLS, value);
			img.erase(img.begin()+ j*ROWS);   
        }
    }
	return;
}

void shift_right(img_dt& img, const size_t p, const uint8_t value){
	for (int j = 0; j < ROWS ; j++){
        for (int i = 0; i < p ; i++){
            img.insert(img.begin()+ j*ROWS, value);
            img.erase(img.begin()+j*ROWS+COLS);   
        }
    }
	return;
}

void shift_up(img_dt& img, const size_t p, const uint8_t value){
	for (int i = 0; i < p*COLS; i++){
        img.insert(img.end(), value);
        img.erase(img.begin());
    }
	return;
}

void shift_down(img_dt& img, const size_t p, const uint8_t value){
	for (int i = 0; i < p*COLS; i++){
        img.insert(img.begin(), value);
        img.erase(img.end() - 1);
    }
	return;
}

void dataset::shift_image(img_dt& img, const enum shift_type dir, const size_t p, const uint8_t value){
	vector<uint8_t>::iterator it;
	bool contain;
	int count;
	vector<int> position, block_length;

	switch (dir){
		case (LEFT) :		
			
			shift_left(img, p, value);
			break;

		case (RIGHT) :
			
			shift_right(img, p, value);
			break;

		case (UP) :

			shift_up(img, p, value);
			break;

		case (DOWN) :

			shift_down(img, p, value);
			break;

		case (UPLEFT) :

			shift_left(img, p, value);
			shift_up(img, p, value);
			break;

		case (UPRIGHT) :

			shift_right(img, p, value);
			shift_up(img, p, value);
			break;

		case (DOWNLEFT) :

			shift_left(img, p, value);
			shift_down(img, p, value);
			break;

		case (DOWNRIGHT) : 

			shift_right(img, p, value);
			shift_down(img, p, value);
			break;
	}
}


void dataset::resize_image(img_dt& img, const size_t new_rows, const size_t new_cols){
	vector<float> dis;
    img_dt resized;
    double d_new_rows = static_cast<double>(new_rows);
    double d_new_cols = static_cast<double>(new_cols);
    float y = ( ROWS / d_new_rows ) ;
    float x = ( COLS / d_new_cols ) ;
    double x1, x0, y1, y0, distance;
    
    for (int i = 0; i < new_rows; i++){
        for (int j = 0; j < new_cols; j++){
            x1 = ( ( j*x + (j + 1)*x ) / 2 );
            y1 = ( ( i*y + (i + 1)*y ) / 2 );
            dis.clear();
            for (int k = 0; k < ROWS; k++){
                for (int l = 0; l < COLS; l++){
                    x0 = k + 0.5;
                    y0 = l + 0.5;
                    distance = ( (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) >= 0)? (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) : - ( (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) );
                    dis.push_back( distance );
                }
            }
            resized.push_back( img[ min_element( dis.begin(), dis.end() ) - dis.begin() ] );
        }
    }
	img = resized;

	return;
}


void dataset::crop_image(img_dt& img, const size_t y0, const size_t x0, const size_t new_rows, const size_t new_cols){
	vector<int> cropped, tmp;
    int space;
    img.erase( img.begin(), img.begin() + y0*COLS);

    img.erase( img.begin() + y0*( COLS + new_cols ), img.end() );

	for (size_t i = 0; i < new_rows; i++){
		tmp.clear();
		for ( int j = 0; j < COLS; j++){
			tmp.push_back(img[i*COLS + j]);
		}

		tmp.erase( tmp.begin()  , tmp.begin() + x0 );
		tmp.erase( tmp.begin() + new_cols, tmp.end() );

		for (int j = 0; j < tmp.size(); j++){
			cropped.push_back(tmp[j]);
		}

	}

	return;
}


void dataset::padding_image(img_dt& img, const size_t top, const size_t down, const size_t left, const size_t right, const uint8_t value){
	for (int i = 0; i < top; i++){
		for (int j = 0; j < COLS; j++){
			img[i*COLS + j] = value;
		}
	}

	for (int i = ROWS - 1; i >= ROWS - down; i--){
		for (int j = 0; j < COLS; j++){
			img[i*COLS + j] = value;
		}
	}

	for (int i = 0; i < left; i++){
		for (int j = 0; j < ROWS; j++){
			img[j*COLS + i] = value;
		}
	}

	for (int i = COLS - 1; i >= COLS - right; i--){
		for (int j = 0; j < ROWS; j++){
			img[j*COLS + i] = value;
		}
	}

	return;
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
	img_dt vector;
	for  (int i = 0; i < img.size(); i++){
		vector.push_back(img[i]);
	}
	return vector;
}


array<uint8_t, PIXELS>  dataset::convert_image_dt(const img_dt& img) const {
	array<uint8_t, PIXELS> array;
	for (int i = 0; i < img.size(); i++){
		array[i] = img[i];
	}
	return array;
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
	int space;
	for (size_t i = 0; i < PIXELS; i++){
		if ( i != 0 && i%(COLS) == 0 ) cout << endl;
		if (img_ar[i] < 10){
			space = 3;
		}else if(img_ar[i] < 100){
			space = 2;
		}else{
			space = 1;
		}
		for (int j = 0; j < space; j++) cout << " ";
		cout << img_ar[i];
	}
}


void dataset::print_image(const img_dt& img) const {
	int space;
	for (size_t i = 0; i < PIXELS; i++){
		if ( i != 0 && i%(COLS) == 0 ) cout << endl;
		if (img[i] < 10){
			space = 3;
		}else if(img[i] < 100){
			space = 2;
		}else{
			space = 1;
		}
		for (int j = 0; j < space; j++) cout << " ";
		cout << +img[i];
	}
}


void dataset::print_statistic(const enum data_type mode) const{
	for (int i = 0; i <= 9; i++){
		cout << "Number of ";
		switch (mode){
			case (TRAIN_IMAGE) : cout << "train";
			case (TEST_IMAGE) : cout << "test";
		}
		cout << " images for digit " << i << ": ";
		
		switch (mode){
			case (TRAIN_IMAGE) : cout << get_data_size(TRAIN_IMAGE);
			case (TEST_IMAGE) : cout << get_data_size(TEST_IMAGE);
		}
		cout << endl;

	}

	return;
}

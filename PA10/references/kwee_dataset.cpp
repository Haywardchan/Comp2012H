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
	size_t items_left = size;
	vector<uint8_t>::iterator label_it = train_labels.end();
	vector<array<uint8_t, PIXELS>>::iterator image_it = train_images.end();
	while (items_left > 0) {
		label_it--;
		image_it--;
		if (*label_it == digit) {
			label_it = train_labels.erase(label_it);
			image_it = train_images.erase(image_it);
			items_left--;
		}
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
	// cout << p << endl;
	int rows = img.size();
	int cols = img.at(0).size();
	// cout << rows << " " << cols << endl;
	switch (dir) {
		case UP:
			crop_image(img, p, 0, rows-p, cols);
			padding_image(img, 0, p, 0, 0, value);
			break;
		case DOWN:
			crop_image(img, 0, 0, rows-p, cols);
			padding_image(img, p, 0, 0, 0, value);
			break;
		case LEFT:
			crop_image(img, 0, p, rows, cols-p);
			padding_image(img, 0, 0, 0, p, value);
			break;
		case RIGHT:
			crop_image(img, 0, 0, rows, cols-p);
			padding_image(img, 0, 0, p, 0, value);
			break;
		case UPLEFT:
			shift_image(img, UP, p, value);
			shift_image(img, LEFT, p, value);
			break;
		case UPRIGHT:
			shift_image(img, UP, p, value);
			shift_image(img, RIGHT, p, value);
			break;
		case DOWNLEFT:
			shift_image(img, DOWN, p, value);
			shift_image(img, LEFT, p, value);
			break;
		case DOWNRIGHT:
			shift_image(img, DOWN, p, value);
			shift_image(img, RIGHT, p, value);
			break;
		default:
			throw runtime_error("shift_img: invalid shift_type.");
			break;
	}
	
	// END OF YOUR IMPLEMENTATION
}


void dataset::resize_image(img_dt& img, const size_t new_rows, const size_t new_cols){
	// START OF YOUR IMPLEMENTATION
	int rows = img.size();
	int cols = img.at(0).size();
	img_dt new_img(new_rows, deque<uint8_t>(new_cols, 0));
	for (int r = 0; r < new_rows; r++) {
		for (int c = 0; c < new_cols; c++) {
			new_img[r][c] = img[(int) 
					((double) (r + 0.5) / new_rows * rows) // get integer part
				][ (int) 
					((double) (c + 0.5) / new_cols * cols) 
				];
		}
	}
	img = new_img;	
	// END OF YOUR IMPLEMENTATION
}


void dataset::crop_image(img_dt& img, const size_t y0, const size_t x0, const size_t new_rows, const size_t new_cols){
	// START OF YOUR IMPLEMENTATION
	// first, crop the rows
	img.erase(img.begin(), img.begin() + y0);
	img.erase(img.begin() + new_rows, img.end());
	for (img_dt::iterator it = img.begin(); it != img.end(); it++) {
		it->erase(it->begin(), it->begin() + x0);
		it->erase(it->begin() + new_cols, it->end());
		// cout << it->size() << endl;
	}	
	// cout << img.size() << endl;
	// print_image(img);
	// getchar();
	// END OF YOUR IMPLEMENTATION
}


void dataset::padding_image(img_dt& img, const size_t top, const size_t down, const size_t left, const size_t right, const uint8_t value){
	// START OF YOUR IMPLEMENTATION
	// first, pad the existing rows
	int newSize = img.at(0).size() + left + right; 
	// cout << "newSIze: " << newSize << endl;
	for (img_dt::iterator it = img.begin(); it != img.end(); it++) {
		it->insert(it->begin(), left, value);
		it->insert(it->end(), right, value);
	}
	deque<uint8_t> temp(newSize, value);
	// cout << temp.size() << " " << top << " " << down << endl;
	img.insert(img.begin(), top, temp);
	img.insert(img.end(), down, temp);
	// for (img_dt::iterator it = img.begin(); it != img.end(); it++) cout << it->size() << endl;
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
	img_dt res;
	res.resize(ROWS);
	for (int r = 0; r < ROWS; r++) res.at(r).resize(COLS);
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			res[r][c] = img[c + r * ROWS];
		}
	}	
	return res;	
	// END OF YOUR IMPLEMENTATION
}


array<uint8_t, PIXELS>  dataset::convert_image_dt(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	if (img.size() != ROWS) throw runtime_error("convert_image_dt: wrong number of rows.");
	for (int r = 0; r < ROWS; r++) if (img.at(r).size() != COLS) throw runtime_error("convert_image_dt. wrong number of cols.");
	array<uint8_t, PIXELS> res;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			res[c + r * ROWS] = img[r][c];
		}
	}	
	return res;
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
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			printf("%4d", img_ar[c + COLS * r]);
		}
		cout << endl;
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::print_image(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	int rows = img.size();
	int cols = img.at(0).size();
	for (int r = 0; r < rows; r++) {
		if (img.at(r).size() != cols) // just for checking
			throw runtime_error("print_image: img is not rectangular.");
		// for (deque<uint8_t>::const_iterator it = img.at(r).begin(); it != img.at(r).end(); it++) {
		// 	printf("%4d", *it);
		// }
		for (int c = 0; c < cols; c++) {
			printf("%4d", img[r][c]);
		}
		cout << endl;
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::print_statistic(const enum data_type mode) const{
	// START OF YOUR IMPLEMENTATION
	int statistics[10] = {0};
	vector<uint8_t>::const_iterator iter;
	switch (mode) {
		case TRAIN_IMAGE:
			for (iter = train_labels.begin(); iter != train_labels.end(); iter++) {
				statistics[*iter]++;
			}
			for (int i = 0; i <= 9; i++) {
				cout << "Number of train images for digit " << i
					<< ": " << statistics[i] << endl;
			}
			break;
		case TEST_IMAGE:
			for (iter = test_labels.begin(); iter != test_labels.end(); iter++) {
				statistics[*iter]++;
			}
			for (int i = 0; i <= 9; i++) {
				cout << "Number of test images for digit " << i
					<< ": " << statistics[i] << endl;
			}
			break;
	}
	// END OF YOUR IMPLEMENTATION
}

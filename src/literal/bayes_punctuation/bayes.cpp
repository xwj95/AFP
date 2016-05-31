#include "defines.h"

#define TRAIN_SIZE 120000
#define TEST_SIZE 60000
#define FEATURE_SIZE 30
#define FEATURE_BIN 2
#define LABEL_SIZE 2
#define EPS 1e-7

int train_punctuation[TRAIN_SIZE][FEATURE_SIZE];
int train_label[TRAIN_SIZE];
int train_size = 0;

int test_punctuation[TEST_SIZE][FEATURE_SIZE];
int test_label[TEST_SIZE];
int test_size = 0;

double p_y[LABEL_SIZE];
double p_xy[FEATURE_SIZE][FEATURE_BIN][LABEL_SIZE];

int feature_size = 23;
int feature_bin = 2;
int label_size = 2;

int load_feature(string filename, int punctuation[][FEATURE_SIZE], int &size) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	size = 0;
	string line;
	while (getline(fin, line)) {
		stringstream ss;
		ss << line;
		for (int f = 0; f < feature_size; ++f) {
			ss >> train_punctuation[size][f];
		}
		++size;
	}
	cout << "Size = " << size << endl;
	fin.close();
	return 0;
}

int load_label(string filename, int label[], int size) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	for (int i = 0; i < size; ++i) {
		fin >> label[i];
	}
	fin.close();
	return 0;
}

int bayes_train(int punctuation[][FEATURE_SIZE], int label[], int size, double p_y[LABEL_SIZE], double p_xy[FEATURE_SIZE][FEATURE_BIN][LABEL_SIZE]) {
	for (int f = 0; f < feature_size; ++f) {
		for (int l = 0; l < label_size; ++l) {
			for (int b = 0; b < feature_bin; ++b) {
				p_xy[f][b][l] = 0;
			}
		}
	}
	for (int l = 0; l < label_size; ++l) {
		p_y[l] = 0;
	}
	for (int i = 0; i < size; ++i) {
		p_y[label[i]] += 1;
		for (int f = 0; f < feature_size; ++f) {
			int bin = punctuation[i][f];
			if (bin > 0) {
				bin = 1;
			}
			p_xy[f][bin][label[i]] += 1;
		}
	}
	for (int f = 0; f < feature_size; ++f) {
		for (int l = 0; l < label_size; ++l) {
			for (int b = 0; b < feature_bin; ++b) {
				cout << "F[" << f << "] = " << b << ", label = " << l << ": " << p_xy[f][b][l] << endl;
				p_xy[f][b][l] /= p_y[l];
				p_xy[f][b][l] += EPS;
			}
		}
		cout << endl;
	}
	for (int l = 0; l < label_size; ++l) {
		p_y[l] /= size;
		// cout << p_y[l] << ' ';
	}
	cout << endl;
	return 0;
}

int bayes_test(int punctuation[][FEATURE_SIZE], int label[], int size, double p_y[LABEL_SIZE], double p_xy[FEATURE_SIZE][FEATURE_BIN][LABEL_SIZE]) {
	int hit = 0;
	for (int i = 0; i < size; ++i) {
		double rst = -1;
		int lbl = 0;
		for (int l = 0; l < label_size; ++l) {
			double p = p_y[l];
			for (int f = 0; f < feature_size; ++f) {
				int bin = punctuation[l][f];
				if (bin > 0) {
					bin = 1;
				}
				p *= p_xy[f][bin][l];
			}
			if (p > rst) {
				rst = p;
				lbl = l;
			}
		}
		// cout << rst << ' ' << lbl << ' ' << label[i] << endl;
		if (label[i] == lbl) {
			hit += 1;
		}
		label[i] = lbl;
	}
	cout << "Accuracy = " << (double) hit / size << endl;
	return 0;
}

int save_label(string filename, int label[], int size) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < size; ++i) {
		fout << label[i] << endl;
	}
	fout.close();
	return 0;
}

int main() {
	load_feature("../txt/train_punctuation.txt", train_punctuation, train_size);
	load_feature("../txt/test_punctuation.txt", test_punctuation, test_size);
	load_label("../txt/train_label.txt", train_label, train_size);
	load_label("../txt/test_label.txt", test_label, test_size);
	bayes_train(train_punctuation, train_label, train_size, p_y, p_xy);
	bayes_test(test_punctuation, test_label, test_size, p_y, p_xy);
	save_label("./predict.txt", test_label, test_size);
	return 0;
}

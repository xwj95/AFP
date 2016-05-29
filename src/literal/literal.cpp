#include "defines.h"

vector<string> train_literals;
vector<int> train_clicks;

vector<string> test_literals;
vector<int> test_clicks;

vector<string> dictionary;

int load(string filename, vector<string> &literals, vector<int> &clicks, bool istrain) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	literals.clear();
	clicks.clear();
	string literal;
	int click;
	while (!fin.eof()) {
		getline(fin, literal);
		if (literal == "") {
			break;
		}
		literals.push_back(literal);
		if (istrain) {
			fin >> click;
			clicks.push_back(click);
		}
		getline(fin, literal);
	}
	cout << "Size = " << literals.size() << endl;
	fin.close();
	return 0;
}

int load_dictionary(string filename, vector<string> &dictionary) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	dictionary.clear();
	string word;
	while (!fin.eof()) {
		word = "";
		fin >> word;
		if (word == "") {
			break;
		}
		dictionary.push_back(word);
	}
	cout << "Size = " << dictionary.size() << endl;
	fin.close();
	return 0;
}

int save_literal(string filename, vector<string> &literals) {
	ofstream fout;
	fout.open(filename.data());
	int cnt = 0;
	for (int i = 0; i < literals.size(); ++i) {
		int flag = 1;
		for (int j = 0; j < i; ++j) {
			if (literals[i] == literals[j]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			cnt += 1;
			fout << literals[i] << endl;
		}
	}
	cout << "Count = " << cnt << endl;
	fout.close();
	return 0;
}

int save_vector(string filename, vector<string> &literals, vector<string> &dictionary) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < literals.size(); ++i) {
		if (i % 1000 == 0) {
			cout << "Now " << i << endl;
		}
		for (int j = 0; j < dictionary.size(); ++j) {
			int flag = 0;
			if (literals[i].find(dictionary[j]) < literals[i].length()) {
				flag = 1;
			}
			fout << flag;
			if (j < dictionary.size() - 1) {
				fout << " ";
			}
		}
		fout << endl;
	}
	fout.close();
	return 0;
}

int save_category(string filename, vector<int> &clicks) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < clicks.size(); ++i) {
		fout << clicks[i] << endl;
	}
	fout.close();
	return 0;
}

int main() {
	load("train.txt", train_literals, train_clicks, true);
	load("test.txt", test_literals, test_clicks, false);
	load_dictionary("dictionary.txt", dictionary);
	save_vector("train_vector.txt", train_literals, dictionary);
	save_vector("test_vector.txt", test_literals, dictionary);
	save_category("train_category.txt", train_clicks);
	save_category("test_category.txt", test_clicks);
	return 0;
}

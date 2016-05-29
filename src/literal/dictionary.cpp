#include "defines.h"

vector<string> literals;
vector<string> words;
vector<string> dictionary;

int load_literal(string filename, vector<string> &literals) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	literals.clear();
	string literal;
	while (!fin.eof()) {
		getline(fin, literal);
		if (literal == "") {
			break;
		}
		literals.push_back(literal);
	}
	cout << "Size = " << literals.size() << endl;
	fin.close();
	return 0;
}

int load_word(string filename, vector<string> &words) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	words.clear();
	string word;
	while (!fin.eof()) {
		fin >> word;
		words.push_back(word);
		getline(fin, word);
	}
	cout << "Size = " << words.size() << endl;
	fin.close();
	return 0;
}

int select_word(vector<string> &literals, vector<string> &words, vector<string> &dictionary) {
	dictionary.clear();
	for (int i = 0; i < words.size(); ++i) {
		if (i % 1000 == 0) {
			cout << "Now " << i << endl;
		}
		bool select = false;
		for (int j = 0; j < literals.size(); ++j) {
			if (literals[j].find(words[i]) < literals[j].length()) {
				select = true;
				break;
			}
		}
		if (select) {
			dictionary.push_back(words[i]);
		}
	}
	return 0;
}

int save_dictionary(string filename, vector<string> &dictionary) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < dictionary.size(); ++i) {
		fout << dictionary[i] << endl;
	}
	cout << "Size = " << dictionary.size() << endl;
	fout.close();
	return 0;
}

int main() {
	load_literal("literal.txt", literals);
	load_word("./sogou/SogouLabDic.txt", words);
	select_word(literals, words, dictionary);
	save_dictionary("dictionary.txt", dictionary);
	return 0;
}

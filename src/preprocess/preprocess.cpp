#include "defines.h"
#include "data.h"

vector<Data*> train;
vector<Data*> test;

int destroy(vector<Data*> &dataset) {
	for (int i = 0; i < dataset.size(); ++i) {
		delete dataset[i]->user;
		delete dataset[i]->ad;
		delete dataset[i]->feedback;
		delete dataset[i];
	}
	dataset.clear();
	return 0;
}

bool isnumber(string &s) {
	for (int i = 0; i < s.length(); ++i) {
		if ((s[i] < '0') || (s[i] > '9')) {
			return false;
		}
	}
	return true;
}

string int2str(int x) {
	stringstream ss;
	string s;
	ss << x;
	ss >> s;
	return s;
}

int str2int(string &s) {
	stringstream ss;
	int x;
	ss << s;
	ss >> x;
	return x;
}

int load(string filename, vector<Data*> &dataset, bool istrain) {
	ifstream fin;
	fin.open(filename.data());
	if (!fin) {
		cerr << "Loading '" << filename << "' failed!" << endl;
		return -1;
	}
	ifstream fpic;
	string str;
	dataset.clear();
	while (!fin.eof()) {
		str = "";
		fin >> str;
		if (str == "") {
			break;
		}
		Data *data = new Data();

		User *user = new User();
		user->qq = str;
		fin >> user->gender >> user->year >> user->surf_scene >> user->marriage_status >> user->education >> user->profession;
		data->user = user;

		Ad *ad = new Ad();
		fin >> ad->creative_id >> ad->category_id >> ad->series_id >> ad->advertiser_id >> ad->product_type;
		if (ad->product_type < 25) {
			fin >> ad->product_id;
		}
		fin >> ad->img_url;
		fin >> str;
		if (str.substr(0, 4) != "http") {
			ad->literal = str;
		}
		else {
			ad->dest_url = str;
			fin >> ad->literal;
		}
		while (1) {
			fin >> str;
			if (isnumber(str)) {
				break;
			}
			ad->literal = ad->literal + " " + str;
		}
		data->ad = ad;

		ad->dirname = "../../images/";
		ad->filename = int2str(ad->creative_id) + ".jpg";
		fpic.open((ad->dirname + ad->filename).data());
		if (!fpic) {
			cerr << "'" << ad->dirname + ad->filename << "'" << " does not exist!" << endl;
			return -1;
		}
		fpic.close();

		Feedback *feedback = new Feedback();
		feedback->imp_time = str2int(str);
		fin >> feedback->pos_id;
		if (istrain) {
			fin >> feedback->click_num;
		}
		data->feedback = feedback;

		dataset.push_back(data);
	}
	fin.close();
	cout << "Size = " << dataset.size() << endl;
	return 0;
}

int save_image(string filename, vector<Data*> &dataset, bool istrain) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < dataset.size(); ++i) {
		Data *data = dataset[i];
		User *user = data->user;
		Ad *ad = data->ad;
		Feedback *feedback = data->feedback;
		fout << ad->filename << endl;
		fout << user->gender << ' ' << user->year << ' ';
		fout << ad->product_type << ' ';
		if (istrain) {
			fout << feedback->click_num;
		}
		fout << endl;
	}
	fout.close();
	return 0;
}

int save_literal(string filename, vector<Data*> &dataset, bool istrain) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < dataset.size(); ++i) {
		Data *data = dataset[i];
		User *user = data->user;
		Ad *ad = data->ad;
		Feedback *feedback = data->feedback;
		fout << ad->literal << endl;
		if (istrain) {
			fout << feedback->click_num;
		}
		fout << endl;
	}
	fout.close();
	return 0;
}

int save_information(string filename, vector<Data*> &dataset, bool istrain) {
	ofstream fout;
	fout.open(filename.data());
	for (int i = 0; i < dataset.size(); ++i) {
		Data *data = dataset[i];
		User *user = data->user;
		Ad *ad = data->ad;
		Feedback *feedback = data->feedback;
		fout << user->qq << ", " << user->gender << ", " << user->year << ", " << user->surf_scene << ", " << user->marriage_status << ", " << user->education << ", " << user->profession << ", ";
		fout << ad->creative_id << ", " << ad->category_id << ", " << ad->series_id << ", " << ad->advertiser_id << ", " << ad->product_type << ", " << ad->product_id << ", ";
		fout << feedback->imp_time << ", " << feedback->pos_id;
		if (istrain) {
			fout << ", " << feedback->click_num;
		}
		fout << endl;
	}
	fout.close();
	return 0;
}

int main() {
	load("../../data/train11w.data", train, true);
	save_image("../image/train.txt", train, true);
	save_literal("../literal/train.txt", train, true);
	save_information("../information/train.csv", train, true);
	load("../../data/test5w.data", test, false);
	save_image("../image/test.txt", test, false);
	save_literal("../literal/test.txt", test, false);
	save_information("../information/test.csv", test, false);
	destroy(train);
	destroy(test);
	return 0;
}

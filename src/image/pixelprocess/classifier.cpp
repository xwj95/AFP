#include "classifier.h"

void Classifier::init()
{
	trainCounter = 0;
	testCounter = 0;
}

void Classifier::readinTrain()
{
	ifstream fin("../txt/train.txt");
	string str;
	while(getline(fin, str))
	{
		str = "../../../images/" + str;
		int i = trainCounter;
		train[i].name = str;
		fin >> train[i].gender >> train[i].year >> train[i].type >> train[i].num;
		getline(fin, str);
		trainCounter++;
	}
	fin.close();
}

void Classifier::readinTest()
{
	ifstream fin("../txt/test.txt");
	string str;
	while(getline(fin, str))
	{
		str = "../../../images/" + str;
		int i = testCounter;
		test[i].name = str;
		fin >> test[i].gender >> test[i].year >> test[i].type;
		getline(fin, str);
		testCounter++;
	}
	fin.close();
}

void Classifier::pixelProcess()
{
	for (int i = 0; i < trainCounter; i++)
	{
		Image img;
		img.setName(train[i].name);
		// img.open();
		// img.setAttribute(train[i].gender, train[i].year, train[i].type, train[i].num);
	}
}

void Classifier::run()
{
	init();
	readinTrain();
	readinTest();
	pixelProcess();
}



#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include "image.h"

class Classifier
{
	Attribute train[120000];	//train total: 112248
	Attribute test[60000];		//test total: 56355
	int trainCounter, testCounter;
	void init();
	void readinTrain();
	void readinTest();
	void pixelProcess();
public:
	void run();
};


#endif
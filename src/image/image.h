#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "attribute.h"

class Image
{
private:
	Attribute attr;
	Mat mat;
public:
	void setName(string name);
	void open();
	void show();
	void setAttribute(int gender, int year, int type);
	void setAttribute(int gender, int year, int type, int num);
};


#endif
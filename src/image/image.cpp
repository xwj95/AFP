#include "image.h"

void Image::setName(string name)
{
	attr.name = name;
}

void Image::open()
{
	mat = imread(attr.name.data());
	if (mat.empty())
	{
		cout << "the image: " << attr.name << " is not exist" << endl;
		return;
	}	
}

void Image::show()
{
	namedWindow(attr.name.data(), WINDOW_AUTOSIZE);
	imshow(attr.name.data(), mat);
	waitKey(0);
}

void Image::setAttribute(int gender, int year, int type)
{
	attr.gender = gender;
	attr.year = year;
	attr.type = type;
}

void Image::setAttribute(int gender, int year, int type, int num)
{
	attr.gender = gender;
	attr.year = year;
	attr.type = type;
	attr.num = num;
}

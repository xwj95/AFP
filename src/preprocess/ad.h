#ifndef __AD__
#define __AD__

#include "defines.h"

class Ad {
public:
	int creative_id;
	long long category_id;
	long long series_id;
	long long advertiser_id;
	int product_type;
	long long product_id;
	string img_url;
	string dest_url;
	string literal;

	string filename;
};

#endif

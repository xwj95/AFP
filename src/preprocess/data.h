#ifndef __DATA__
#define __DATA__

#include "defines.h"
#include "user.h"
#include "ad.h"
#include "feedback.h"

class Data {
public:
	User *user;
	Ad *ad;
	Feedback *feedback;
};

#endif

#pragma once

#include <time.h>
#include <iostream>

using namespace std;

#define  LTFUN_TM 	LtTimeRecorder tm(__FUNCTION__);

class LtTimeRecorder
{
public:
	LtTimeRecorder(const string &sFunc):sFlag(sFunc)
	{
		time(&tmS);
	}

	~LtTimeRecorder()
	{
		time(&tmE);
		cout << "\n\n " << sFlag << " cost time = " << difftime(tmE, tmS) << " seconds \n";
	}

private:
	string  sFlag;
	time_t  tmS;
	time_t  tmE;
};

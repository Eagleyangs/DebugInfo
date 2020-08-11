#pragma once

#include <time.h>
#include <iostream>

using namespace std;

#define  IFUN_TM 	TimeRecorder tm(__FUNCTION__);

class TimeRecorder
{
public:
	TimeRecorder(const string &sFunc):sFlag(sFunc)
	{
		time(&tmS);
	}

	~TimeRecorder()
	{
		time(&tmE);
		cout << "\n\n " << sFlag << " cost time = " << difftime(tmE, tmS) << " seconds \n";
	}

private:
	string  sFlag;
	time_t  tmS;
	time_t  tmE;
};

/*
	IFUN_TM; put fun {} include. Usage: type fun { IFUN_TM; Process; return type;}
*/
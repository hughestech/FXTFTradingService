#if !defined SingletonClass_H
#define SingletonClass_H

#include <iostream>
#include "../Common/FXTFLog.h"

using namespace std;

class SingletonClass
{
private:
	static bool mInstanceFlag;
	static SingletonClass *mSingletonClass;

	FXTFLog						*mFXTFLog;

	SingletonClass();
	~SingletonClass();

public:
	static SingletonClass* getInstance();

	FXTFLog* getFXTFLog(){return mFXTFLog;}
	void setFXTFLog(FXTFLog* aFXTFLog){mFXTFLog=aFXTFLog;}
};

#endif
#include "../Common/SingletonClass.h"

bool SingletonClass::mInstanceFlag				= false;
SingletonClass* SingletonClass::mSingletonClass = NULL;

SingletonClass::SingletonClass()
{
	
}

SingletonClass::~SingletonClass()
{

}

SingletonClass* SingletonClass::getInstance()
{
	if(!mInstanceFlag)
	{
		mSingletonClass = new SingletonClass();
		mInstanceFlag = true;
		return mSingletonClass;
	}
	else
	{
		return mSingletonClass;
	}

	// mSingletonClass = new SingletonClass();
	//return mSingletonClass;
}
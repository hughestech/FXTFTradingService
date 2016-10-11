#if !defined DepositMoneyModel_H
#define DepositMoneyModel_H

using namespace std;

class DepositMoneyModel
{
private:
	int mMT4LoginID;
	double mDepositBalance;


public:
	DepositMoneyModel();
	~DepositMoneyModel();

	int getMT4LoginID(){return mMT4LoginID;}
	void setMT4LoginID(int aMT4LoginID){mMT4LoginID=aMT4LoginID;}

	double getDepositBalance(){return mDepositBalance;}
	void setDepositBalance(double aDepositBalance){ mDepositBalance=aDepositBalance; }
};

#endif
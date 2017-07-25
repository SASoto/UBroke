// UBroke.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "UBrokeheader.h"

//double UBAccount::weeklyInc = -1;

int main()
{
	cout << "UBroke" << endl;
	cout << "-------" << endl;

	UBAccount user;
	user.CheckUser();
	
	cout << "Welcome " << user.getUser() << endl;
	user.CalcDailyInc();
	user.CalcWMY();

	cout << "Are you wondering if you can afford:" << endl;
	cout << "1 | Metrocards?" << endl;
	int subject = 0;
	cin >> subject;

	cout << "Well, let's find out!";

	switch (subject) {
		case 1:
			user.CalcMetro();
			break;
		default:
			break;
	}

	cout << "Well, there you go." << endl;
	cout << "Continue? ";
	char response;
	cin >> response;

    return 0;
}


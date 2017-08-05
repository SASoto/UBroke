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

	bool displaymess = false;
	int subject = 0;
	do {
		if (displaymess == true)
			cout << "Anything else you want to check?" << endl;
		else 
			cout << "What do you want to do today?" << endl;

		cout << "1 | Figure out Metrocard payments." << endl;
		cout << "5 | Change Account Info." << endl;
		cout << "9 | Exit." << endl;
		cin >> subject;

		switch (subject) {
		case 1:
			displaymess = true;
			user.CalcMetro();
			break;
		case 5:
			displaymess = true;
			user.MakeChanges();
			break;
		case 9:
			displaymess = false;
			break;
		default:
			displaymess = false;
			cout << "Oops! That's not an available option." << endl;
			break;
		}
	} while (subject != 9);

	cout << "Take care!" << endl;
	char response;
	cin >> response;
	return 0;
}


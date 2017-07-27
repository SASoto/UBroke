#include "stdafx.h"
#include "UBrokeheader.h"

double regR = 2.75;
double expR = 6.50;
double sevenUP = 32.00;
double sevenExpP = 59.50;
double thirtyUP = 121.00;

void UBAccount::CheckUser() {
	string response;
	do {
		string username;
		cout << "Please enter your username or signup with a new UBroke account (no spaces)." << endl;
		cin >> username;

		int tracker = 0;
		ifstream UBfile;
		UBfile.open("UBrokeAccts.txt");
		string searchStr;
		while (UBfile >> searchStr) {
			if (searchStr == username)
			{
				tracker = 1;
				break;
			}
		}
		UBfile.close();

		if (tracker == 1) {
			setUser(username);
		}
		else {
			cout << "Would you like to create a UBroke account with this username? ";
			cin >> response;

			if (response == "yes" || response == "Yes" || response == "y" || response == "Y") {
				ofstream print("UBrokeAccts.txt", ios_base::app);
				print << username << "\n";
				setUser(username);
				UBfile.close();
			}
		}
	} while (response == "no" || response == "No");
}

void UBAccount::CalcDailyInc() {
	cout << "Do you get paid hourly or weekly? ";
	string getsPaid;
	cin >> getsPaid;

	if (getsPaid == "hourly" || getsPaid == "Hourly")
	{
		hour_or_week = 0;
		cout << "How much do you get paid hourly? $";
		double salary;
		cin >> salary;
		setSalary(salary);

		cout << "How many hours do you work in a week? ";
		int hours;
		cin >> hours;

		int numof_hours = 0;
		setHours(hours);
	}
	else
	{
		hour_or_week = 1;
		cout << "How much do you get paid weekly? $";
		double salary;
		cin >> salary;
		setSalary(salary);
		setWeeklyInc(salary);

		cout << "How many days do you work in a week? ";
		int numof_days = 0;
		cin >> numof_days;
		setDays(numof_days);

		cout << "How many hours do you work in a day? ";
		int numof_hours = 0;
		setHours(numof_hours);
	}

	double retDays = getDays();
	double retHours = getHours();
	double retSalary = getSalary();
	if (getsPaid == "hourly" || getsPaid == "Hourly") {
		double dailyInc = retHours * retSalary;
		setDailyInc(dailyInc);
	}
	else {
		double dailyInc = (retSalary / retDays);
		setDailyInc(dailyInc);
	}
}

void UBAccount::CalcWMY() {
	double retWeeklyInc = getWeeklyInc();
	if (retWeeklyInc == -1) {
		double retDays = getDays();
		double retDailyInc = getDailyInc();
		double weeklyInc = retDailyInc * retDays;
		setWeeklyInc(weeklyInc);
		retWeeklyInc = weeklyInc;
	}

	double monthlyInc = retWeeklyInc * (30.42 / 7);
	setMonthlyInc(monthlyInc);

	double yearlyInc = monthlyInc * 12;
	setYearlyInc(yearlyInc);
}

void UBAccount::CalcMetro() {
	cout << "How many bus/train trips do you make in a day? ";
	int numof_trips;
	cin >> numof_trips;

	cout << "How many (if any) of these trips are covered by ride transfers? ";
	int transferT;
	cin >> transferT;

	cout << "For how many days of the week do you travel this often? ";
	int numof_tripdays;
	cin >> numof_tripdays;

	cout << "How many of these trips are express bus service trips? ";
	int expDayTrips;
	cin >> expDayTrips;

	int regDayTrips = numof_trips - expDayTrips;
	int costRTW = (regDayTrips - transferT) * regR;
	int costETW = expDayTrips * expR;
	double dailyCost = costRTW + costETW;
	cout << "You spend $" << dailyCost << " every day on bus/train rides." << endl;

	int weeklyTrips;
	int weeklyRegT;
	int weeklyExpT;
	weeklyTrips = numof_trips * numof_tripdays;
	weeklyRegT = numof_tripdays * regDayTrips;
	weeklyExpT = numof_tripdays * expDayTrips;

	double weeklyCost = dailyCost * numof_tripdays;
	cout << "You spend $" << weeklyCost << " every week on bus/train rides." << endl;

	double monthlyTrips;
	double monthlyRegT;
	double monthlyExpT;

	monthlyTrips = weeklyTrips * (30.42 / 7); // Based on average # of days in a month
	monthlyRegT = weeklyRegT * (30.42 / 7);
	monthlyExpT = weeklyExpT * (30.42 / 7);

	double monthlyCost = weeklyCost * (30.42 / 7);
	cout << "You spend $" << monthlyCost << " every month on bus/train rides." << endl;

	double yearlyTrips;
	double yearlyRegT;
	double yearlyExpT;

	yearlyTrips = monthlyTrips * 12;
	yearlyRegT = monthlyRegT * 12;
	yearlyExpT = monthlyExpT * 12;

	double yearlyCost = monthlyCost * 12;
	cout << "You spend $" << yearlyCost << " every year on bus/train rides." << endl;

	OPMetro(costRTW, costETW);
}

void UBAccount::OPMetro(int costRTW, int costETW) {
	if ((costRTW  > sevenUP) || ((costRTW + costETW) > sevenUP)) {
		sevenUP * (30.42 / 7);
	}
	
}
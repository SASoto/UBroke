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
		string userName;
		cout << "Please enter your username or signup with a new UBroke account (no spaces)." << endl;
		cin >> userName;

		int tracker = 0;
		ifstream UBfile;
		UBfile.open("UBrokeAccts.txt");
		string searchStr;
		while (UBfile >> searchStr) {
			if (searchStr == userName)
			{
				tracker = 1;
				UBfile.close();
				break;
			}
		}

		if (tracker == 1) {
			setUser(userName);
		}
		else {
			cout << "Would you like to create a UBroke account with this username? ";
			cin >> response;

			if (response == "yes" || response == "Yes" || response == "y" || response == "Y") {
				//ofstream UBfile;
				//UBfile.open("UBrokeAccts.txt");
				ofstream print("UBrokeAccts.txt", ios_base::app);
				print << userName;
				setUser(userName);
				print.close();

				this->CalcDailyInc();
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
		//hour_or_week = 0;
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
		//hour_or_week = 1;
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

	this->CalcWMY();
}

void UBAccount::CalcWMY() {
	double retWeeklyInc = getWeeklyInc();
	if (retWeeklyInc == -1) {
		double retHours = getHours();
		double retDailyInc = getDailyInc();
		double weeklyInc = retDailyInc * retHours;
		setWeeklyInc(weeklyInc);
		retWeeklyInc = weeklyInc;
	}

	double monthlyInc = retWeeklyInc * (30.42 / 7);
	setMonthlyInc(monthlyInc);

	double yearlyInc = monthlyInc * 12;
	setYearlyInc(yearlyInc);

	this->WriteTo();
}

void UBAccount::WriteTo() {
	//cout << "Im in here" << endl;
	string userName = getUser();
	//cout << "The user is: " << userName << endl;
	ifstream UBfile;
	UBfile.open("UBrokeAccts.txt");
	string searchStr;
	while (UBfile >> searchStr) {
		//cout << "Im in the func" << endl;
		if (searchStr == userName)
		{
			//cout << "Im in the func" << endl;
			UBfile.close();
			//cout << "Im in the func" << endl;
			double dailyInc = getDailyInc();
			//cout << "Daily: " << dailyInc << endl;
			double weeklyInc = getWeeklyInc();
			//cout << "Weekly: " << weeklyInc << endl;
			double monthlyInc = getMonthlyInc();
			//cout << "Monthly: " << monthlyInc << endl;
			double yearlInc = getYearlyInc();
			//cout << "Yearly: " << yearlyInc << endl;
			ofstream print("UBrokeAccts.txt", ios_base::app);
			print << setw(3) << setfill(' ') << setw(13) << dailyInc << setw(3) << setfill(' ') << setw(13) << weeklyInc << setw(3) << setfill(' ') << setw(13) << monthlyInc << setw(3) << setfill(' ') << setw(13) << yearlyInc << "\n";
			print.close();
			break;
		}
	}
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
	int costRTD = (regDayTrips - transferT) * regR;
	int costETD = expDayTrips * expR;
	double dailyCost = costRTD + costETD;
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

	OPMetro(costRTD, costETD);
}

void UBAccount::OPMetro(int costRTD, int costETD) {
	//5% bonus added to metrocard purchases or additions of of $5.50 or mroe
	//last decimal rounded up in bonus fare
	//same deal with express bus fare
	//dont forget about reduced fare customers
	double totalCostD = costRTD + costETD;
	double costSUPM = sevenUP * (30.42 / 7);
	if (totalCostD > sevenUP) {
		//if (costSUPM > thirtyUP) {
			cout << "The most optimal way to pay for your bus/train rides each month is to buy a single thirty-day unlimited Metrocard." << endl;
		//}
		/*(else {
			double costLeftOver = thirtyUP - costSUPM;
			costLeftOver / regR;
		}*/
	}
	else {
		double costM = (costRTD + costETD) * (30.42 / 7);
		if (costM > costSUPM) {
			cout << "The most optimal way to pay for your bus/train rides each month is to buy a single thirty-day unlimited Metrocard." << endl;
		}
		else if (costM > thirtyUP) {
			cout << "The most optimal way to pay for your bus/train rides each month is to buy a single thirty-day unlimited Metrocard." << endl;
		}
		else {
			cout << "Continue paying $" << totalCostD << "a day for your Metrocards." << endl;
			cout << "And with 5% cash bonus on any Metrocard purchases or additions above or equal to $5.50, it is most optimal to pay for your daily Metrocard in a single payment of " << totalCostD << ", which will result in a " << totalCostD * 0.05 << " added bonus." << endl;
		}
	}
}

void UBAccount::MakeChanges() {
	cout << "What do you want to change about your account?" << endl;
	cout << "1 | " << endl;
	cout << "2 | " << endl;
	cout << "3 | " << endl;
	cout << "4 | " << endl;
	cout << "5 | " << endl;
	cout << "6 | " << endl;

	bool displaymess = false;
	int response;
	do {
		if (displaymess == true) {
			cout << "Anything else you want to change?" << endl;
			cin >> response;
		}
		switch (response) {
			case 1:
				displaymess = true;
				break;
			case 2:
				displaymess= true;
				break;
			case 3:
				displaymess = true;
				break;
			case 4:
				displaymess = true;
				break;
			case 5:
				displaymess = true;
				break;
			case 6:
				displaymess = true;
				break;
			case 9:
				displaymess = false;
				break;
			default:
				cout << "Oops! That's not an available option." << endl;
				displaymess = false;
				break;
		}
	} while (response != 9);
}
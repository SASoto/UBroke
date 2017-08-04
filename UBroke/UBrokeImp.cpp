#include "stdafx.h"
#include "UBrokeheader.h"

double regR = 2.75;
double expR = 6.50;
double sevenUP = 32.00;
double sevenExpP = 59.50;
double thirtyUP = 121.00;

int lof_Spaces;

void UBAccount::CheckUser() {
	string response;
	do {
		string userName;
		cout << "Please enter your username or signup with a new UBroke account (no spaces and with a max of 10 char)." << endl;
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
			this->RetrieveInfo();
		}
		else {
			cout << "Would you like to create a UBroke account with this username? ";
			cin >> response;

			if (response == "yes" || response == "Yes" || response == "y" || response == "Y") {
				//ofstream UBfile;
				//UBfile.open("UBrokeAccts.txt");
				lof_Spaces = 13 - userName.length();
				/*ofstream print("UBrokeAccts.txt", ios_base::app);
				print << userName << setfill(' ') << setw(lof_Spaces);
				print.close();*/
				setUser(userName);

				this->Questionnaire();
			}
		}
	} while (response == "no" || response == "No");
}

void UBAccount::RetrieveInfo() {
	ifstream UBfile;
	UBfile.open("UBrokeAccts.txt");
	string searchStr;
	while (UBfile >> searchStr) {
		if (searchStr == userName) {
			int tracker = 0;
			double incomes;
			while(UBfile >> incomes) {
				cout << "INCOMES: " << incomes << endl;
				switch (tracker) {
				case 0:
					setDailyInc(incomes);
					tracker++;
					break;
				case 1:
					setWeeklyInc(incomes);
					tracker++;
					break;
				case 2:
					setMonthlyInc(incomes);
					tracker++;
					break;
				case 3:
					setYearlyInc(incomes);
					tracker++;
					break;
				default:
					break;
				}
			}
			UBfile.close();
			break;
		}
	}
}

void UBAccount::Questionnaire() {
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

	this->CalcDailyInc(getsPaid);
}

void UBAccount::ChangeUser(string newUserName) {
	string currUserName = getUser();
	int len = currUserName.length();
	int reqSpace = lof_Spaces + len;
	if (reqSpace > 13) {
		while (reqSpace != 13) {
			reqSpace -= 1;
			lof_Spaces -= 1;
		}
	}

	ifstream UBfile;
	UBfile.open("UBrokeAccts.txt");
	ofstream Tempfile("Tempfile.txt", ios_base::app);

	//char searchChar;
	string searchStr;
	int madeChange = 0;
	//string tempForOne;
	//string wholeLine;
	while (UBfile >> searchStr) {
		//UBfile.get(searchChar);
		string tempForOne = searchStr;
		//stringstream stream;
		//stream << searchChar;
		//stream >> searchStr;
		cout << "CURR: " << currUserName << endl;
		cout << "STR: " << searchStr << endl;
		//if (madeChange == 1) { madeChange = 0; }
		//else {
			if (searchStr == currUserName) {
				//ofstream Tempfile("Tempfile.txt", ios_base::app);
				double dailyInc = getDailyInc();
				//cout << "Daily: " << dailyInc << endl;
				double weeklyInc = getWeeklyInc();
				//cout << "Weekly: " << weeklyInc << endl;
				double monthlyInc = getMonthlyInc();
				//cout << "Monthly: " << monthlyInc << endl;
				double yearlInc = getYearlyInc();
				cout << "NEW: " << newUserName << endl;
				Tempfile << newUserName << setw(3) << setfill(' ') << setw(13) << ""/*<< dailyInc << setw(3) << setfill(' ') << setw(13) << weeklyInc << setw(3) << setfill(' ') << setw(13) << monthlyInc << setw(3) << setfill(' ') << setw(13) << yearlyInc << "\n"*/;
				//print.close();
				//UBfile.close();
				setUser(newUserName);
				//madeChange = 1;
				//Tempfile.close();
			}
			else {
				//ofstream Tempfile("Tempfile.txt", ios_base::app);
				cout << "IN SECOND PART NOW" << endl;
				string addLine;
				if (getline(UBfile, searchStr)) {
					addLine += tempForOne;
					addLine += searchStr;
					//addLine.push_back('\n');
					Tempfile << addLine << "\n";
				}
			}
		//}
	}
	UBfile.close();
	Tempfile.close();

	this->CopyOver();
}

void UBAccount::CopyOver() {
	ofstream rewriteMain("UBrokeAccts.txt", fstream::trunc);
	rewriteMain.close();
	
	ifstream Tempfile;
	Tempfile.open("TempFile.txt");
	ofstream UBfile("UBrokeAccts.txt", ios_base::app);

	string searchStr;
	while (getline(Tempfile, searchStr)) {
		string addLine;
		addLine += searchStr;
		UBfile << addLine << "\n";
	}
	Tempfile.close();
	UBfile.close();

	ofstream rewriteTemp("TempFile.txt", fstream::trunc);
	rewriteTemp.close();
}

void UBAccount::CalcDailyInc(string getsPaid) {
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
		string userName = getUser();

		//ifstream UBfile;
		//UBfile.open("UBrokeAccts.txt");
		//string searchStr;
		/*while (UBfile >> searchStr) {
			if (searchStr == userName)
			{*/
				//UBfile.close();
				//string userName = getUser();
				double dailyInc = getDailyInc();
				cout << "Daily: " << dailyInc << endl;
				double weeklyInc = getWeeklyInc();
				cout << "Weekly: " << weeklyInc << endl;
				double monthlyInc = getMonthlyInc();
				cout << "Monthly: " << monthlyInc << endl;
				double yearlInc = getYearlyInc();
				cout << "Yearly: " << yearlyInc << endl;
				ofstream print("UBrokeAccts.txt", ios_base::app);
				print << userName << setw(3) << setfill(' ') << setw(13) << dailyInc << setw(3) << setfill(' ') << setw(13) << weeklyInc << setw(3) << setfill(' ') << setw(13) << monthlyInc << setw(3) << setfill(' ') << setw(13) << yearlyInc << "\n";
				print.close();
				//break;
			//}
		//}
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
	double costRTD = (regDayTrips - transferT) * regR;
	double costETD = expDayTrips * expR;
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

void UBAccount::OPMetro(double costRTD, double costETD) {
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
	bool displaymess = false;
	int response;
	do {
		if (displaymess == true)
			cout << "Anything else you want to change?" << endl;
		else
			cout << "What do you want to change about your account?" << endl;
		
		cout << "1 | Username" << endl;
		cout << "2 | Salary" << endl;
		cout << "9 | Go Back." << endl;
		cin >> response;

		switch (response) {
			case 1: {
				cout << "Enter your new username (no space and with a 10 chararacter maximum): ";
				string newUserName;
				cin >> newUserName;
				this->ChangeUser(newUserName);
				displaymess = true;
				break;
			}
			case 2:
				cout << "In order to change your salary information, you must first answer a few questions beforehand." << endl;
				this->Questionnaire();
				displaymess= true;
				break;
			case 9:
				displaymess = false;
				break;
			default:
				displaymess = false;
				cout << "Oops! That's not an available option." << endl;
				break;
		}
	} while (response != 9);
}
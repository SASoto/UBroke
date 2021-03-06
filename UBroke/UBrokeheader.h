#pragma once
#include "stdafx.h"
#include <ctime>
#include <utility>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

//time_t t = time(NULL);
//tm* timePtr = localtime(&t);
//timePtr->tm_sec, min, hour, mday, mon, year

extern double regR;
extern double expR;
extern double sevenUP;
extern double sevenExpP;
extern double thirtyUP;

/*enum Months {January, February, March, April, May, June, July,
			August, September, October, November, December};*/

class UBAccount {
	public:
		void CheckUser();
		void RetrieveInfo();
		void Questionnaire();
		void ChangeUser(string);
		void ChangeSalary();
		void CopyOver();
		void CalcDailyInc(string);
		void CalcWMY();
		void WriteTo();
		void CalcMetro();
		void OPMetro(double, double);
		void MakeChanges();

		//Set Personal Info
		void setUser(string username) {
			this->userName = username;
		};
		void setSalary(double salary) {
			this->salary = salary;
		};
		void setHours(double numof_hours) {
			this->numof_hours = numof_hours;
		};
		void setDays(double numof_days) {
			this->numof_days = numof_days;
		};
		//Set Income Info
		void setDailyInc(double dailyInc) {
			this->dailyInc = dailyInc;
		};
		void setWeeklyInc(double weeklyInc) {
			this->weeklyInc = weeklyInc;
		};
		void setMonthlyInc(double monthlyInc) {
			this->monthlyInc = monthlyInc;
		}
		void setYearlyInc(double yearlyInc) {
			this->yearlyInc = yearlyInc;
		};

		string getUser() {
			return this->userName;
		}
		double getSalary() {
			return this->salary;
		}
		double getHours() {
			return this->numof_hours;
		}
		double getDays() {
			return this->numof_days;
		}
		double getDailyInc() {
			return this->dailyInc;
		}
		double getWeeklyInc() {
			return this->weeklyInc;
		}
		double getMonthlyInc() {
			return this->monthlyInc;
		}
		double getYearlyInc() {
			return this->yearlyInc;
		}

	private:
		string userName;
		double salary;
		double numof_hours;
		double numof_days;
		double dailyInc;
		double weeklyInc = -1;
		double monthlyInc;
		double yearlyInc;
};
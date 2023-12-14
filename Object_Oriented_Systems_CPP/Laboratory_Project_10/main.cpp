
#include<iostream>
using namespace std;

class Date {
	
	int _day, _month, _year;

public:
	Date(int = 0, int = 0, int = 0);
	Date operator+(int days);
	friend ostream & operator<<(ostream &, const Date &);
};

Date::Date(int d, int m, int y){
    _day=d;
    _month=m;
    _year=y;
}
Date Date::operator+(int days){
    Date dt;
    dt._day = _day + days;
    dt._month = _month;
    dt._year = _year;

    if(dt._day > 30){
        dt._month += dt._day/30;
        dt._day = dt._day % 30;
    }
    if(dt._month > 12){
        dt._year += dt._month/12;
        dt._month = dt._month % 12;
    }
    return dt;
} 

ostream& operator<<(ostream&, const Date & date){
    return cout << date._day << "." << date._month << "." << date._year;
}

int main(int argc, char *argv[])
{
    Date begin_task = Date(26,10,2023);
    cout << "Die Aufgabe beginnt am " << begin_task << endl;
    Date end_task = begin_task + 6;
    cout << "Die Aufgabe endet am " << end_task << endl;
    Date one_year_and_one_month_later = begin_task + 390;
    cout << "Ein Jahr und ein Monat nach Aufgabenbeginn ist der " << one_year_and_one_month_later << endl;
    Date three_years_and_eleven_months_later = begin_task + 1410;
    cout << "Drei Jahre und 11 Monate nach Aufgabenbeginn ist der " << three_years_and_eleven_months_later << endl;
}



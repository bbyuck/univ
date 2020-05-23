#include <iostream>
#include <string>

using namespace std;

class Date {

private:
	int month; //멤버변수
	int day;
	int year;
	
public:

	Date(int M, int D, int Y) { // 생성자
		setMonth(M);
		setDay(D);
		setYear(Y);
	}


		int getMonth() {
			if (month <= 12) {
				return month;
			}
			else {
				return 0;
			}
		}

		int getYear() {
			if (month > 12) {
				year++;
				month = 1;
			}
			return year;
		}

		int getDay() {
			if (month == 1) { // 1월이면
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			} // 월별 날짜 제한
			if (month == 2) {
				if (day > 28) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 3) {
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 4) {
				if (day > 30) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 5) {
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 6) {
				if (day > 30) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 7) {
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 8) {
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 9) {
				if (day > 30) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 10) {
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 11) {
				if (day > 30) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}

			if (month == 12) {
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			}
		}

		void setMonth(int M) {
			month = M;
		}
		void setDay(int D) {
			day = D;
		}
		void setYear(int Y) {
			year = Y;
		}


		int displayDate1() {
			return getYear();
		}
		int displayDate2() {
			return getMonth();
		}
		int displayDate3() {
			return getDay();
		}
	
};

int main() {
	int day = 0;
	int month = 0;
	int year = 0;
	
	cout << "오늘은 몇 년입니까? : ";
	cin >> year;
	cout << endl;

	cout << "오늘은 몇 월입니까? : ";
	cin >> month;
	cout << endl;

	cout << "오늘은 몇 일입니까? : ";
	cin >> day;
	cout << endl;

	Date show(month, day, year);
	cout << "오늘의 날짜는 : " << show.displayDate2() << "/" << show.displayDate3() << "/" << show.displayDate1();

	cout << endl;

	
	return 0;
}
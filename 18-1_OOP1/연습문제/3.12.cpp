#include <iostream>
#include <string>

using namespace std;

class Date {

private:
	int month; //�������
	int day;
	int year;
	
public:

	Date(int M, int D, int Y) { // ������
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
			if (month == 1) { // 1���̸�
				if (day > 31) {
					month++;
					return 1;
				}
				else {
					return day;
				}
			} // ���� ��¥ ����
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
	
	cout << "������ �� ���Դϱ�? : ";
	cin >> year;
	cout << endl;

	cout << "������ �� ���Դϱ�? : ";
	cin >> month;
	cout << endl;

	cout << "������ �� ���Դϱ�? : ";
	cin >> day;
	cout << endl;

	Date show(month, day, year);
	cout << "������ ��¥�� : " << show.displayDate2() << "/" << show.displayDate3() << "/" << show.displayDate1();

	cout << endl;

	
	return 0;
}
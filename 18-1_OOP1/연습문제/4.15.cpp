#include <iostream>
#include <iomanip>

using namespace std;

class AccruedLeave { // AccruedLeave 클래스 선언

public:
	AccruedLeave(double W, double A) { // 클래스 생성자, 멤버변수를 매개변수로 초기화
		WorkedHour = W;
		Accrued = A;
	}
	void setWorkedHour(double W) {
		WorkedHour = W;
	}
	void setAccrued(double W, double A) {
		Accrued = 2 + (0.1 * WorkedHour);
	}

	double getWorkedHour() {
		return WorkedHour;
	}
	double getAccrued() {
		return Accrued;
	}


private:
	double WorkedHour; // 멤버변수 선언
	double Accrued;
};

int main() {
	double WorkedHour = 0; // 변수 초기화
	double Accrued = 0;

	AccruedLeave time{ WorkedHour,Accrued }; // 객체 생성

	while (true) {
		cout << "Enter number of hours worked (-1 to end): ";
		cin >> WorkedHour;
		if (WorkedHour == -1)
			break;
		time.setWorkedHour(WorkedHour);
		time.setAccrued(WorkedHour, Accrued);
		cout << "Accrued leave: " << fixed << setprecision(2) << time.getAccrued() << " hours";
		cout << endl << endl;
	}
	return 0;
}
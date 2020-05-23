#include <iostream>
#include <iomanip>

using namespace std;

class AccruedLeave { // AccruedLeave Ŭ���� ����

public:
	AccruedLeave(double W, double A) { // Ŭ���� ������, ��������� �Ű������� �ʱ�ȭ
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
	double WorkedHour; // ������� ����
	double Accrued;
};

int main() {
	double WorkedHour = 0; // ���� �ʱ�ȭ
	double Accrued = 0;

	AccruedLeave time{ WorkedHour,Accrued }; // ��ü ����

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
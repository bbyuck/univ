#include <iostream>
#include <iomanip>

using namespace std;

class FuelUsage {

public:
	FuelUsage(double d, double f, double td, double tf) { //class ������

		distance = d;
		TotalDistance = td;
		TotalFuel = tf;
		fuel = f;
	}

	void setDistance(double d) {
		distance = d;
	}
	void setTotalDistance(double td, double d) { // ��ü�Ÿ��� �� set �Լ�
		if (d > 0) {
			TotalDistance = TotalDistance + distance;
		}
	}
	void setFuel(double f) {
		fuel = f;
	}
	void setTotalFuel(double tf, double f) { // ��ü������ �� set �Լ�
		if (f > 0) {
			TotalFuel = TotalFuel + fuel;
		}
	}
	double getDistance() {
		return distance;
	}
	double getFuel() {
		return fuel;
	}
	double getKPL() { // kms per liter ���ϴ� �Լ�
		return getDistance() / getFuel();
	}
	double getTotalDistance() const {
		return TotalDistance;
	}
	double getTotalFuel() const {
		return TotalFuel;
	}
	double getTotalKPL() { // ��ü �Ÿ� / ��ü ���� �Լ�
		return getTotalDistance() / getTotalFuel();
	}

private:
	double distance; // ��� ������
	double TotalDistance{ 0 }; // �Ÿ��� ���� ����Ʈ���� 0
	double fuel;
	double TotalFuel{ 0 }; // ������ ���� ����Ʈ���� 0
};


int main() {
	double distance = 0;
	double fuel = 0;
	double TotalDistance = 0;
	double TotalFuel = 0;

	FuelUsage trip{ distance, fuel, TotalDistance, TotalFuel };
	while (true) {
		cout << "Enter kilometers driven (-1 to quit) : ";
		cin >> distance;
		trip.setDistance(distance);
		if (distance == -1)
			break;
		cout << "Enter liters use : ";
		cin >> fuel;
		trip.setFuel(fuel);
		trip.setTotalDistance(TotalDistance, distance);
		trip.setTotalFuel(TotalFuel, fuel);

		cout << "Kms per liter this trip : " << fixed << setprecision(6) << trip.getKPL() << endl;
		cout << "Total kms per liter : " << fixed << setprecision(6) << trip.getTotalKPL() << endl << endl;
	}

	return 0;
}
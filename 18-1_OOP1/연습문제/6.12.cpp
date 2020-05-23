#include <iostream>
#include <iomanip>

using namespace std;


int calculateCharges(double time) {
	int charges = 20; // �ʱ� ��� 20.00$

	if (time > 3) {
		charges += 5 * (static_cast<int>(time) - 3); // �ð� ����
	}
	if (charges >= 50) { // ����� �ִ�ġ�� 50 �޷�
		charges = 50;
	}
	return charges;
}

int main() {
	double time[3] = { 0, 1, 2 }; // �迭�� ���� time�� �Է¹���
	

	for (int count = 0; count <= 2; count++) { // �ð� time�� �Է¹޴� for��
		cout << count + 1 << "�� ���� ���� �ð��� �Է��ϼ���.";
		cin >> time[count];
	
		if (time[count] > 24) { // 24�ð����� ����
			cout << "\n ���� �ð��� 24�ð��� �ѱ� �� �����ϴ�. �ٽ� �Է��ϼ���." << endl;
			count--;
			continue;
		}
	}

	cout << "\nCar" << setw(12) << "Hours" << setw(15) << "Charges" << endl; // ǥ UI

	for (int count = 0; count <= 2; count++) { // �� ���� �ð��� ����� ǥ UI�� ���
		cout << count +1 << setw(14) << time[count] << setw(10) << "$" << calculateCharges(time[count]) << ".00" << endl; 
	}
	
	int totalCharges = 0; // ����� ���� �����ϰ� ����� ���� ���� �� 0���� �ʱ�ȭ
	
	for (int count = 0; count <= 2; count++) { // ����� ������ calculateCharges()�Լ��� �̿��� ���
		totalCharges += calculateCharges(time[count]);
	}
	
	double totalTime = time[0] + time[1] + time[2]; // �ð��� ���� ���� ���� �� ����

	cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << "total : " << setw(7) << totalTime << setw(10) << "$" << totalCharges << ".00" << endl; // total ���� ���


	return 0;
}


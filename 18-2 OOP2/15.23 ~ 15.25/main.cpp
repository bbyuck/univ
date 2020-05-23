#include <iostream>
#include <bitset>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	bitset<1024> nums;

	nums.set(); // ��� ���� �Ҽ��� �����ϰ� 1�� �ʱ�ȭ
	nums.set(0, false);
	nums.set(1, false);
	for (int i = 2; i < 1024; i++) {
		if (nums[i]) {
			for (int j = i * i; j < 1024; j += i) {
				nums.set(j, false);
			}
		}
	}
	int input;
	cout << "(15.23)�Ҽ����� Ȯ���Ϸ��� �� �Է� : ";
	cin >> input;
	
	if (nums[input]) {
		cout << input << "�� �Ҽ��Դϴ�." << endl;
	}
	else {
		cout << input << "�� �Ҽ��� �ƴմϴ�." << endl;
	}

	cout << "2 ~ 1023 ������ �Ҽ�: " << endl;
	int count = 0;
	int numCount = 0;
	for (int i = 0; i < 1024; i++) {
		if (count % 10 == 0 && count != 0) { // 10���� 
			cout << endl; 
			count = 0;
		}
		if (nums[i]) {
			cout << i << " ";
			count++;
			numCount++;
		}
	}
	cout << "\n\n�Ҽ��� �� ������ " << numCount << "��" << endl;

	vector<int> primeFactor;
	int inputCopy = input;

	if (!nums[input]) {
		for (int i = 0; input != 1; i++) {
			if (nums[i]) {
				while (input % i == 0) {
					input /= i;
					primeFactor.push_back(i);
				}
			}
		}

		cout << "(15.25)The unique prime factorization of " << inputCopy << " is : ";

		int count = 0;
		for (auto Factors : primeFactor) {
			cout << (count == 0 ? "" : " * ") << Factors;
			count++;
		}

		cout << "\n\n(15.24)prime factors: " << endl;

		auto last = unique(primeFactor.begin(), primeFactor.end());
		primeFactor.erase(last, primeFactor.end()); // �ߺ���� ����

		for (auto Factors : primeFactor) {
			cout << Factors << " ";
		}
		cout << endl;
	} // primeFactor �� �ڵ����� �������� ���ĵǾ� push��
}
#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

const size_t rowSize = 2; // 2X3 �迭�� �����ϱ� ���� ��������
const size_t columnSize = 3;

int main() {
	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 �迭 t ����(a), �� ��� elemnents�� 0���� �ʱ�ȭ(h)

	cout << setw(5);
	for (int i = 0; i <= t.size(); ++i) {
		cout << i << "��" << "   ";
	}
	cout << endl;
	for (size_t i = 0; i < t.size(); ++i) {
		cout << i << "��: ";
		for (size_t j = 0; j < t[i].size(); ++j) {
			cout << t[i][j] << "     ";
		}
		cout << endl;
	}
}
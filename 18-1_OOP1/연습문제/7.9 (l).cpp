#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 �迭�� �����ϱ� ���� ��������
const size_t columnSize = 3;

int main() {
	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 �迭 t ����(a), �� ��� elemnents�� 0���� �ʱ�ȭ(h)

	int lowestNum = t[0][0]; // ���� ���� ���� ������ ������ �����ϰ� 2X3 �迭 t �� ù��° ���� ������������ �ʱ�ȭ

	for (size_t i = 0; i < t.size(); ++i) {
		for (size_t j = 0; j < t[i].size(); ++j) {
			if (lowestNum > t[i][j]) {
				lowestNum = t[i][j];
			}
		}
	}
	cout << "���� ���� ���� " << lowestNum << endl; // ���� ���� �� ���
}
#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 �迭�� �����ϱ� ���� ��������
const size_t columnSize = 3;

int main() {

	//(a)

	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 �迭 t ����(a), �� ��� elemnents�� 0���� �ʱ�ȭ(h)
															 //���� ������� �ʰ� 0 ���� �ʱ�ȭ


	//	(g) 1��(row == 1)�� 2��(column == 2)�� elements ��� 0 ���� �ʱ�ȭ �ϴ� ���� for statement													
	for (size_t row = 0; row < t.size(); ++row) {
		for (size_t column = 0; column < t[row].size(); ++column) {
			if (row == 1) {
				t[row][column] = 0;
			}
			else if (column == 2) {
				t[row][column] = 0;
			}
		}
	}
}
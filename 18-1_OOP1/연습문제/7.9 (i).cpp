#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 �迭�� �����ϱ� ���� ��������
const size_t columnSize = 3;

int main() {

	//(a)

	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 �迭 t ����(a), �� ��� elemnents�� 0���� �ʱ�ȭ(h)
															 //���� ������� �ʰ� 0 ���� �ʱ�ȭ


	for (size_t row = 0; row < t.size(); ++row) {	//(i) for ���� ���� �迭 t �ʱ�ȭ
		for (size_t column = 0; column < t[row].size(); ++column) {
			t[row][column] = 0;
		}
	}
}
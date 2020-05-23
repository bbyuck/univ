#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 �迭�� �����ϱ� ���� ��������
const size_t columnSize = 3;

int main() {

	//(a)

	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 �迭 t ����(a), �� ��� elemnents�� 0���� �ʱ�ȭ(h)
															 //���� ������� �ʰ� 0 ���� �ʱ�ȭ

															
	for (auto row : t) { //	(j) ���� ��� for ���� ���� �迭 t �ʱ�ȭ
		for (auto &elements : row) { // pass-by-reference�� �迭�� �ּҸ� �޾ƿ� �迭�� �� ��ü�� 0���� ����
			elements = 0;
			cout << elements << ' ';
		}
		cout << endl;
	}
}
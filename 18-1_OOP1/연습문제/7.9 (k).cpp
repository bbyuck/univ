#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 �迭�� �����ϱ� ���� ��������
const size_t columnSize = 3;

int main() {

	//(a)

	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 �迭 t ����(a), �� ��� elemnents�� 0���� �ʱ�ȭ(h)
															 //���� ������� �ʰ� 0 ���� �ʱ�ȭ
															 
	for (int i = 0; i < t.size(); ++i) {//	(k)t�� elements�� ���� �Է¹޾� �迭�� �ʱ�ȭ �ϴ� for��
		for (int j = 0; j < t[i].size(); ++j) {
			int num;
			cout << i << "�� " << j << "���� ������ ���� �Է��ϼ���.";
			cin >> num;
			t[i][j] = num;
		}
	}
	//����� ���� �ʱ�ȭ�� �Ǿ����� ���� Ȯ��
	for (int i = 0; i < t.size(); ++i) {
		for (int j = 0; j < t[i].size(); ++j) {
			cout << t[i][j] << " ";
		}
		cout << endl;
	}
}
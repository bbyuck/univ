#include <iostream>

using namespace std;

int main() {
	for (unsigned int count{ 1 }; count <= 10; count++) {
		if (count == 5) {
			++count; // continue���� ���� �ʱ�� ������ ����̹Ƿ� ���������� ������ �Է��ϸ� continue���� ������ ȿ���� ��Ÿ����.
		}
		cout << count << " ";
	}
	cout << "\nUsed continue to skip printing 5" << endl;	
}
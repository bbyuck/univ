#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main() {
	int n; // ������ ����� n ����
	
	srand(time(0)); // �ð��� �õ�� Ȱ��

	//(a)
	n = rand() % 3; // ������ n�� �ּ�(lvalue)�� 0 <= n <= 3 ������ ������ ���� rand()�Լ��� ���� 
	cout << "(a) 0 <= n <= 3 : " << n << endl;

	//(b) 
	n = 1 + rand() % 50; // 1 <= n <= 50
	cout << "(b) 1 <= n <= 50 : " << n << endl;
	
	//(c)
	n = 2 + rand() % 43; // 2 <= n <=44
	cout << "(c) 2 <= n <= 44 : " << n << endl;

	//(d)
	n = 500 + rand() % 179; // 500 <= n <= 678;
	cout << "(d) 500 <= n <= 678 : " << n << endl;
	
	//(e)
	n = -2 + rand() % 5; // -2 <= n <= 2
	cout << "(e) -2 <= n <= 2 : " << n << endl;

	//(f)
	n = -3 + rand() % 16; // -3 <= n <= 12
	cout << "(f) -3 <= n <= 12 : " << n << endl;
	return 0;
}
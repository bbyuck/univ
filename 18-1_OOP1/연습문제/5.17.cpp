#include <iostream>
#include <iomanip>
#include "Calculating.h"


using namespace std;


int main() {

	int ncounter;

	double nProduct1 = 0;
	double nProduct2 = 0;
	double nProduct3 = 0;
	double nProduct4 = 0;
	double nProduct5 = 0; // product�� �Ǹŷ�(��) - ��ǰ������ ������������ �ʱ����� double ������ Ÿ�� ���

	double Product1 = 0;
	double Product2 = 0;
	double Product3 = 0;
	double Product4 = 0;
	double Product5 = 0;

	double total = 0; //�Ǹž�
	Calculating Sales(nProduct1, nProduct2, nProduct3, nProduct4, nProduct5, Product1, Product2, Product3, Product4, Product5, total);
	do {
		cout << "�Ǹ��� ��ǰ ��ȣ�� �Է��ϼ���(���Ḧ ���ϸ� -1�� �Է��ϼ���) : "; // ���� ����������
		cin >> ncounter;
		if (ncounter == -1) {
			break;
		}
		if (ncounter > 5) {
			cout << "��ȣ�� �� �� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
			continue;
		}
		cout << "�Ǹŷ��� �Է��ϼ��� : ";
		int number = 0;
		cin >> number;
		switch (ncounter) { // switch�� ����
		case 1: 
			nProduct1 += number;
			break;
		case 2: 
			nProduct2 += number;
			break;
		case 3: 
			nProduct3 += number;
			break;
		case 4: 
			nProduct4 += number;
			break;
		case 5: 
			nProduct5 += number;
			break;
		default:
			break;
		}// switch�� �� switch�� �̿��Ͽ� �Է¹��� �Ǹŷ� ����
	} while (ncounter != -1);
	Sales.setnProduct1(nProduct1);
	Sales.setnProduct2(nProduct2);
	Sales.setnProduct3(nProduct3);
	Sales.setnProduct4(nProduct4);
	Sales.setnProduct5(nProduct5);

	Sales.setProduct1(Product1, nProduct1);
	Sales.setProduct2(Product2, nProduct2);
	Sales.setProduct3(Product3, nProduct3);
	Sales.setProduct4(Product4, nProduct4);
	Sales.setProduct5(Product5, nProduct5);

	cout << "\n" << setw(19) << "�Ǹŷ�" << endl;
	cout << "Product 1 :  " << nProduct1 << endl;
	cout << "Product 2 :  " << nProduct2 << endl;
	cout << "Product 3 :  " << nProduct3 << endl;
	cout << "Product 4 :  " << nProduct4 << endl;
	cout << "Product 5 :  " << nProduct5 << endl;
	cout << "\n" << setw(19) << "�Ǹž�" << endl;
	cout << "Product1  :  " << Sales.getProduct1() << endl;
	cout << "Product2  :  " << Sales.getProduct2() << endl;
	cout << "Product3  :  " << Sales.getProduct3() << endl;
	cout << "Product4  :  " << Sales.getProduct4() << endl;
	cout << "Product5  :  " << Sales.getProduct5() << endl;
	cout << "   �Ѿ�   :  ";
	Sales.setTotal(total);
	cout << endl;
	return 0;
}
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
	double nProduct5 = 0; // product의 판매량(수) - 제품가격을 변수지정하지 않기위해 double 데이터 타입 사용

	double Product1 = 0;
	double Product2 = 0;
	double Product3 = 0;
	double Product4 = 0;
	double Product5 = 0;

	double total = 0; //판매액
	Calculating Sales(nProduct1, nProduct2, nProduct3, nProduct4, nProduct5, Product1, Product2, Product3, Product4, Product5, total);
	do {
		cout << "판매한 제품 번호를 입력하세요(종료를 원하면 -1을 입력하세요) : "; // 루프 빠져나오기
		cin >> ncounter;
		if (ncounter == -1) {
			break;
		}
		if (ncounter > 5) {
			cout << "번호를 잘 못 입력했습니다. 다시 입력해주세요." << endl;
			continue;
		}
		cout << "판매량을 입력하세요 : ";
		int number = 0;
		cin >> number;
		switch (ncounter) { // switch문 시작
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
		}// switch문 끝 switch문 이용하여 입력받은 판매량 저장
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

	cout << "\n" << setw(19) << "판매량" << endl;
	cout << "Product 1 :  " << nProduct1 << endl;
	cout << "Product 2 :  " << nProduct2 << endl;
	cout << "Product 3 :  " << nProduct3 << endl;
	cout << "Product 4 :  " << nProduct4 << endl;
	cout << "Product 5 :  " << nProduct5 << endl;
	cout << "\n" << setw(19) << "판매액" << endl;
	cout << "Product1  :  " << Sales.getProduct1() << endl;
	cout << "Product2  :  " << Sales.getProduct2() << endl;
	cout << "Product3  :  " << Sales.getProduct3() << endl;
	cout << "Product4  :  " << Sales.getProduct4() << endl;
	cout << "Product5  :  " << Sales.getProduct5() << endl;
	cout << "   총액   :  ";
	Sales.setTotal(total);
	cout << endl;
	return 0;
}
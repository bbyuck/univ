#include <iostream>

class Calculating {

public:
	Calculating(double np1, double np2, double np3, double np4, double np5, double p1, double p2, double p3, double p4, double p5, double t) { // 생성자
		nProduct1 = np1;
		nProduct2 = np2;
		nProduct3 = np3;
		nProduct4 = np4;
		nProduct5 = np5;

		Product1 = p1;
		Product2 = p2;
		Product3 = p3;
		Product4 = p4;
		Product5 = p5;

		total = t;
	}

	void setnProduct1(double np1) {
		nProduct1 = np1;
	}
	void setnProduct2(double np2) {
		nProduct2 = np2;
	}
	void setnProduct3(double np3) {
		nProduct3 = np3;
	}
	void setnProduct4(double np4) {
		nProduct4 = np4;
	}
	void setnProduct5(double np5) {
		nProduct5 = np5;
	}

	void setProduct1(double p1, double np1) { // Product들의 개별 판매액 구해서 저장하는 set함수
		Product1 = nProduct1 * 2.98;
	}
	void setProduct2(double p2, double np2) {
		Product2 = nProduct2 * 4.50;
	}
	void setProduct3(double p3, double np3) {
		Product3 = nProduct3 * 9.98;
	}
	void setProduct4(double p4, double np3) {
		Product4 = nProduct4 * 4.49;
	}
	void setProduct5(double p5, double np4) {
		Product5 = nProduct5 * 6.87;
	}
	void setTotal(double t) { // 총 판매액 계산하여 출력하는 함수
		total = Product1 + Product2 + Product3 + Product4 + Product5;
		std::cout << total;
	}

	double getProduct1() { // 개별 판매액값 반환으로 출력에 이용할 함수
		return Product1;
	}
	double getProduct2() {
		return Product2;
	}
	double getProduct3() {
		return Product3;
	}
	double getProduct4() {
		return Product4;
	}
	double getProduct5() {
		return Product5;
	}


private:
	double nProduct1;
	double nProduct2;
	double nProduct3;
	double nProduct4;
	double nProduct5; // product의 판매량(수) - 제품가격을 변수지정하지 않기위해 double 데이터 타입 사용

	double Product1;
	double Product2;
	double Product3;
	double Product4;
	double Product5;


	double total; //판매액
};

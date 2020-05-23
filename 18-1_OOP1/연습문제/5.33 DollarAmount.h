// Fig. 5.8: DollarAmount.h
// DollarAmount class stores dollar amounts as a whole numbers of pennies

#include <string>
#include <cmath>


class DollarAmount {
public:
		DollarAmount(int64_t DPart, int64_t CPart) { //생성자
		dollars = DPart; // 생성자를 통한 멤버변수 달러와 센트 int64_t 형 매개변수로 초기화
		cents = CPart;
	}

	void add(DollarAmount right) { // add함수
		dollars += right.dollars;  // 달러와 센트를 각각 더해주는 함수 추가
		cents += right.cents;
		
		if (cents >= 100) { // 만약 센트에 저장된 값이 100을 넘어가면 100센트를 1달러로 환전
			dollars++;
			cents -= 100; // 100센트에 1달러
		}
	}
	void subtract(DollarAmount right) { // add함수와 동일
		dollars -= right.dollars;
		cents -= right.cents;
		
		if (cents < 0) { // 만약 센트가 0보다 작아지면
			dollars--;
			cents = 100 - abs(cents); // cents가 - 되면 dollar에서 1달러를 빼온다
		}
	}


	void addInterest(int rate, int divisor) {
		DollarAmount interest{
		((dollars * 100 + cents) * rate + divisor / 2) / divisor / 100, // 반올림 기술은 5.32번이 아닌 기존 예제의 기술을 사용
		((dollars * 100 + cents) * rate + divisor / 2) / divisor % 100 // 멤버변수가 amount 한 개에서 dollars와 cents로 두 개가 되었으므로 객체의 매개변수도 두 개로 늘려준다.
		};
		add(interest);
	}

	void divide(int divisor) { // 추가된 divide 함수 int형 매개변수를 받아 계산하는 함수
		if (dollars < 0) {
			dollars = -(abs(dollars)* 100 + cents) / divisor / 100;
			cents = (abs(dollars) * 100 + cents) / divisor % 100;
		}
		else {
			dollars = (dollars * 100 + cents) / divisor / 100;
			cents = (dollars * 100 + cents) / divisor % 100; // divide함수도 동일한 반올림 기술 사용
		}
	}

	std::string toString() const {
		return std::to_string(dollars) + "." + (cents < 10 ? "0" : "" ) + std::to_string(cents); // amount 멤버변수를 dollars와 cents 두개의 멤버변수로 나누면서 출력도 바뀜
	}
private:
	int64_t dollars; // 멤버변수를 둘로 나눈다
	int64_t cents;
};

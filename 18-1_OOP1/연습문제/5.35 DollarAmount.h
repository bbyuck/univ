#include <string>
#include <cmath>

class DollarAmount {

public:
	DollarAmount(int64_t value) : amount{value} {} // 생성자

	void add(DollarAmount right) { // 멤버함수들
		amount += right.amount;
	}

	void subtract(DollarAmount right) { 
		amount -= right.amount;
	}

	void addInterest(int rate, int divisor) { // interest 객체를 생성해 add 멤버함수를 불러와 amount에 이자를 더하는 멤버함수
		DollarAmount interest{
			(amount * rate + divisor / 2) / divisor
		};
	
		add(interest);
	}

	std::string toString() const{ // amount를 달러와 센트로 나누어 string 형으로 반환해주는 멤버함수
		std::string dollars{ std::to_string(amount / 100) };
		std::string cents{ std::to_string(std::abs(amount % 100)) };
		return dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
	}
private:
	int64_t amount{ 0 };
};
// Fig. 5.8: DollarAmount.h
// DollarAmount class stores dollar amounts as a whole numbers of pennies

#include <string>
#include <cmath>

class DollarAmount {
public:
	DollarAmount(int64_t DPart, int64_t CPart) {// 새로운 생성자(5.30)
		dollars = DPart;
		cents = CPart;
		amount = getAmount(DPart, CPart);
	}

	int64_t getAmount(int64_t DPart, int64_t CPart) {
		amount = (DPart * 100) + CPart;
		return amount;
	}

	explicit DollarAmount(int64_t value) {
		amount = value;
	}  // 기존 생성자


	void add(DollarAmount right) {
		amount += right.amount;
	}
	void subtract(DollarAmount right) {
		amount -= right.amount;
	}

	void addInterest(int rate, int divisor) {
		DollarAmount interest{
			(amount * rate + divisor / 2) / divisor
		};

		add(interest);
	}

	void divide(int divisor) {
		amount /= divisor;
	} // divisor value로 amount를 나눈다

	std::string toString() const {
		std::string dollars(std::to_string(amount / 100));
		std::string cents(std::to_string(abs(amount % 100)));
		return dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
	}

private:
	int64_t amount;
	int64_t dollars;
	int64_t cents;
};
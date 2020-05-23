#include <string>
#include <cmath>

class DollarAmount {

public:
	DollarAmount(int64_t value) : amount{value} {} // ������

	void add(DollarAmount right) { // ����Լ���
		amount += right.amount;
	}

	void subtract(DollarAmount right) { 
		amount -= right.amount;
	}

	void addInterest(int rate, int divisor) { // interest ��ü�� ������ add ����Լ��� �ҷ��� amount�� ���ڸ� ���ϴ� ����Լ�
		DollarAmount interest{
			(amount * rate + divisor / 2) / divisor
		};
	
		add(interest);
	}

	std::string toString() const{ // amount�� �޷��� ��Ʈ�� ������ string ������ ��ȯ���ִ� ����Լ�
		std::string dollars{ std::to_string(amount / 100) };
		std::string cents{ std::to_string(std::abs(amount % 100)) };
		return dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
	}
private:
	int64_t amount{ 0 };
};
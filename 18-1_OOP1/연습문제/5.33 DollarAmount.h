// Fig. 5.8: DollarAmount.h
// DollarAmount class stores dollar amounts as a whole numbers of pennies

#include <string>
#include <cmath>


class DollarAmount {
public:
		DollarAmount(int64_t DPart, int64_t CPart) { //������
		dollars = DPart; // �����ڸ� ���� ������� �޷��� ��Ʈ int64_t �� �Ű������� �ʱ�ȭ
		cents = CPart;
	}

	void add(DollarAmount right) { // add�Լ�
		dollars += right.dollars;  // �޷��� ��Ʈ�� ���� �����ִ� �Լ� �߰�
		cents += right.cents;
		
		if (cents >= 100) { // ���� ��Ʈ�� ����� ���� 100�� �Ѿ�� 100��Ʈ�� 1�޷��� ȯ��
			dollars++;
			cents -= 100; // 100��Ʈ�� 1�޷�
		}
	}
	void subtract(DollarAmount right) { // add�Լ��� ����
		dollars -= right.dollars;
		cents -= right.cents;
		
		if (cents < 0) { // ���� ��Ʈ�� 0���� �۾�����
			dollars--;
			cents = 100 - abs(cents); // cents�� - �Ǹ� dollar���� 1�޷��� ���´�
		}
	}


	void addInterest(int rate, int divisor) {
		DollarAmount interest{
		((dollars * 100 + cents) * rate + divisor / 2) / divisor / 100, // �ݿø� ����� 5.32���� �ƴ� ���� ������ ����� ���
		((dollars * 100 + cents) * rate + divisor / 2) / divisor % 100 // ��������� amount �� ������ dollars�� cents�� �� ���� �Ǿ����Ƿ� ��ü�� �Ű������� �� ���� �÷��ش�.
		};
		add(interest);
	}

	void divide(int divisor) { // �߰��� divide �Լ� int�� �Ű������� �޾� ����ϴ� �Լ�
		if (dollars < 0) {
			dollars = -(abs(dollars)* 100 + cents) / divisor / 100;
			cents = (abs(dollars) * 100 + cents) / divisor % 100;
		}
		else {
			dollars = (dollars * 100 + cents) / divisor / 100;
			cents = (dollars * 100 + cents) / divisor % 100; // divide�Լ��� ������ �ݿø� ��� ���
		}
	}

	std::string toString() const {
		return std::to_string(dollars) + "." + (cents < 10 ? "0" : "" ) + std::to_string(cents); // amount ��������� dollars�� cents �ΰ��� ��������� �����鼭 ��µ� �ٲ�
	}
private:
	int64_t dollars; // ��������� �ѷ� ������
	int64_t cents;
};

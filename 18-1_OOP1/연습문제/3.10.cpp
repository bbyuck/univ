/*
��ü���� ���α׷���1 - 004 �й�
�й� : 12130919
�̸� : ����
140p Exercises
*/


// 3.10
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;


class invoice { // invoice class ����
private: // private ������
	string number;
	string description;
	int quantity, price;
	double taxrate, discount;

public: // public ������
	invoice(string PartNumber, string Description, int Quantity, int Price, double TaxRate, double DiscountRate)
	{
		setPartNumber(PartNumber);
		setDescription(Description);
		setQuantity(Quantity);
		setPrice(Price);
		setTaxRate(TaxRate);
		setDiscountRate(DiscountRate);
	}

	void setPartNumber(string PartNumber) {
		number = PartNumber;
	}
	string getPartNumber() const {
		return number;
	}
	void setDescription(string Description) {
		description = Description;
	}
	string getDescription() {
		return description;
	}
	void setQuantity(int Quantity) {
		quantity = Quantity;
	}
	int getQuantity() {
		if (quantity >= 0) {
			return quantity;
		}
		else {
			return 0;
		}
	}
	void setPrice(int Price) {
		price = Price;
	}
	int getPrice() {
		if (price >= 0) {
			return price;
		}
		else {
			return 0;
		}
	}
	void setTaxRate(double TaxRate) {
		taxrate = TaxRate; // �º��� private
	}
	double getTaxRate() {
		return taxrate * 0.002;
	}
	void setDiscountRate(double DiscountRate) {
		discount = DiscountRate;
	}
	double getDiscountRate() {
		return 0;
	}
	double getInvoiceAmount()
	{
		return getQuantity()*getPrice() + getQuantity()*getPrice()*getTaxRate();
	}

};


int main()
{
	string number, description;
	int price, quantity;
	double taxrate, discount;
	discount = 0;
	taxrate = 0;
	cout << "ǰ�� ��ȣ�� �Է��ϼ���. : ";
	getline(cin, number);
	cout << "������ �Է��ϼ���. : ";
	getline(cin, description);
	cout << "Item�� ���� �Է��ϼ���. : ";
	cin >> quantity;
	cout << "Item 1���� ������ �Է��ϼ���. : ";
	cin >> price;


	invoice show(number, description, price, quantity, discount, taxrate);
	cout << "���� �ݾ� : " << show.getInvoiceAmount();

	return 0;
}

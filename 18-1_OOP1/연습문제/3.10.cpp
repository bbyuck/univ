/*
객체지향 프로그래밍1 - 004 분반
학번 : 12130919
이름 : 강혁
140p Exercises
*/


// 3.10
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;


class invoice { // invoice class 시작
private: // private 접근자
	string number;
	string description;
	int quantity, price;
	double taxrate, discount;

public: // public 접근자
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
		taxrate = TaxRate; // 좌변이 private
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
	cout << "품목 번호를 입력하세요. : ";
	getline(cin, number);
	cout << "설명을 입력하세요. : ";
	getline(cin, description);
	cout << "Item의 양을 입력하세요. : ";
	cin >> quantity;
	cout << "Item 1개당 가격을 입력하세요. : ";
	cin >> price;


	invoice show(number, description, price, quantity, discount, taxrate);
	cout << "송장 금액 : " << show.getInvoiceAmount();

	return 0;
}

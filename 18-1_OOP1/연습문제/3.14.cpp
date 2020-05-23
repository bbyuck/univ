#include <iostream>
#include <string>

using namespace std;

class Account {

public:
	Account(string firstName, string lastName, double initialBalance, unsigned int accountNumber) 
		: 
		name1{ firstName }, name2{ lastName }, accountnumber{ accountNumber } { // 멤버변수 초기화

		if (initialBalance > 0) {
			balance = initialBalance;
		}

	}
	void deposit(int depositAmount) {
		if (depositAmount > 0) {
			balance = balance + depositAmount;
		}
	}

	double getBalance() {
		return balance;
	}
	
	void setFirstName(string firstName) {
		name1 = firstName;
	}
	void setLastName(string lastName) {
		name2 = lastName;
	}

	string getFirstName() const {
		return name1;
	}
	string getLastName() const {
		return name2;
	}

	void setAccountNumber(unsigned int accountNumber) {
		accountnumber = accountNumber;
	}
	unsigned int getAccountNumber() {
		return accountnumber;
	}

private:
	
	string name1;

	string name2;
	//과제시작 3.14번

	unsigned int accountnumber;// 문제에서 주어진 멤버변수들
	string firstName;
	string lastName;
	double balance = { 0 };

}; // 클래스 종료

int main() {
	
	unsigned int accountNumber1; // 입력받을 계좌번호 변수 선언
	unsigned int accountNumber2;

	cout << "Enter first account number : ";
	cin >> accountNumber1;
	cout << endl;
	cout << "Enter second account number : ";
	cin >> accountNumber2;
	cout << endl;

	Account account1{ "Jane", "Green", 50 , accountNumber1 }; // 객체에 멤버변수 추가
	Account account2{ "John" ,"Blue", -7, accountNumber2 };

	cout << account1.getFirstName() << " " << account1.getLastName() << "'s Account Number is " << account1.getAccountNumber();
	cout << endl;
	cout << account2.getFirstName() << " " << account2.getLastName() << "'s Account Number is " << account2.getAccountNumber();
	

	cout << endl << endl;
	cout << "account1: " << account1.getFirstName() << " " << account1.getLastName() << " balance is $" << account1.getBalance();
	cout << endl;

	cout << "account2: " << account2.getFirstName() << " " << account2.getLastName() << " balance is $" << account2.getBalance();
	cout << endl;




		cout << endl << endl;
		cout << "Enter deposit amount for account1: "; // 지시문
		int depositAmount;
		cin >> depositAmount;
		cout << "adding " << depositAmount << " to account1 balance";
		account1.deposit(depositAmount);

		cout << endl << endl;
		cout << "account1: " << account1.getFirstName() << " " << account1.getLastName() << " balance is $" << account1.getBalance();
		cout << endl;
		cout << "account2: " << account2.getFirstName() << " " << account2.getLastName() << " balance is $" << account2.getBalance();

		cout << endl << endl;
		cout << "Enter deposit amount for account2: "; // 지시문
		cin >> depositAmount;
		cout << "adding " << depositAmount << " to account2 balance";
		account2.deposit(depositAmount);

		cout << endl << endl;
		cout << "account1: " << account1.getFirstName() << " " << account1.getLastName() << " balance is $" << account1.getBalance();
		cout << endl;
		cout << "account2: " << account2.getFirstName() << " " << account2.getLastName() << " balance is $" << account2.getBalance();

	
}
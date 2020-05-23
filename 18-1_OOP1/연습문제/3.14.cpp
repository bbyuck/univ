#include <iostream>
#include <string>

using namespace std;

class Account {

public:
	Account(string firstName, string lastName, double initialBalance, unsigned int accountNumber) 
		: 
		name1{ firstName }, name2{ lastName }, accountnumber{ accountNumber } { // ������� �ʱ�ȭ

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
	//�������� 3.14��

	unsigned int accountnumber;// �������� �־��� ���������
	string firstName;
	string lastName;
	double balance = { 0 };

}; // Ŭ���� ����

int main() {
	
	unsigned int accountNumber1; // �Է¹��� ���¹�ȣ ���� ����
	unsigned int accountNumber2;

	cout << "Enter first account number : ";
	cin >> accountNumber1;
	cout << endl;
	cout << "Enter second account number : ";
	cin >> accountNumber2;
	cout << endl;

	Account account1{ "Jane", "Green", 50 , accountNumber1 }; // ��ü�� ������� �߰�
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
		cout << "Enter deposit amount for account1: "; // ���ù�
		int depositAmount;
		cin >> depositAmount;
		cout << "adding " << depositAmount << " to account1 balance";
		account1.deposit(depositAmount);

		cout << endl << endl;
		cout << "account1: " << account1.getFirstName() << " " << account1.getLastName() << " balance is $" << account1.getBalance();
		cout << endl;
		cout << "account2: " << account2.getFirstName() << " " << account2.getLastName() << " balance is $" << account2.getBalance();

		cout << endl << endl;
		cout << "Enter deposit amount for account2: "; // ���ù�
		cin >> depositAmount;
		cout << "adding " << depositAmount << " to account2 balance";
		account2.deposit(depositAmount);

		cout << endl << endl;
		cout << "account1: " << account1.getFirstName() << " " << account1.getLastName() << " balance is $" << account1.getBalance();
		cout << endl;
		cout << "account2: " << account2.getFirstName() << " " << account2.getLastName() << " balance is $" << account2.getBalance();

	
}
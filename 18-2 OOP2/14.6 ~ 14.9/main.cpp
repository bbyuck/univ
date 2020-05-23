#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

void displayInfo(fstream&, int, string, string, double);

int main() {
	int mastAccountNum;
	int transAccountNum;
	
	double mastBalance;
	double transBalance;
	
	string mastFname;
	string mastLname;

	ifstream inOldMastFile{ "oldmast.dat", ios::in};
	ifstream inTransFile{ "trans.dat", ios::in };
	fstream newMastFile{ "newmast.dat", ios::out };

	if (!inOldMastFile) {
		cerr << "\"oldmast.dat\" ������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	if (!inTransFile) {
		cerr << "\"trans.dat\" ������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	if (!newMastFile) {
		cerr << "\"newmast.dat\" ������ �� �� �����ϴ�." << endl;
		exit(EXIT_FAILURE);
	}

	cout << "���� �о����\n";
	inTransFile >> transAccountNum >> transBalance;

	while (!inOldMastFile.eof()) {
	
		inOldMastFile >> mastAccountNum >> mastFname >> mastLname >> mastBalance;
		
		while (mastAccountNum < transAccountNum && !inOldMastFile.eof()) {
			displayInfo(newMastFile, mastAccountNum, mastFname, mastLname, mastBalance);
			inOldMastFile >> mastAccountNum >> mastFname >> mastLname >> mastBalance;
		}
		
		if (mastAccountNum > transAccountNum) {
			cout << "Unmatched transaction record for account " << transAccountNum << endl;
			inTransFile >> transAccountNum >> transBalance;
		}
		else if (mastAccountNum < transAccountNum) {
			cout << "Unmatched transaction record for account " << transAccountNum << endl;
			inTransFile >> transAccountNum >> transBalance;
		}
		while (mastAccountNum == transAccountNum && !inTransFile.eof()) {
			mastBalance += transBalance;
			inTransFile >> transAccountNum >> transBalance;
		}
		displayInfo(newMastFile, mastAccountNum, mastFname, mastLname, mastBalance);

	}		
	
	inTransFile.close();
	inOldMastFile.close();
	newMastFile.close();
}




void displayInfo(fstream& outFile, int accountNum, string mastFname, string mastLname , double balance) {
	outFile << accountNum << ' ' << mastFname << ' ' << mastLname << ' ' << setprecision(2) << fixed << balance << endl; // ���Ϸ�
	cout << accountNum << ' ' << mastFname << ' ' << mastLname << ' '<< setprecision(2) << fixed << balance << endl; // �ܼ����
}
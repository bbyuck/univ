#include <iostream>
#include <bitset>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	bitset<1024> nums;

	nums.set(); // 모든 수를 소수라 가정하고 1로 초기화
	nums.set(0, false);
	nums.set(1, false);
	for (int i = 2; i < 1024; i++) {
		if (nums[i]) {
			for (int j = i * i; j < 1024; j += i) {
				nums.set(j, false);
			}
		}
	}
	int input;
	cout << "(15.23)소수인지 확인하려는 수 입력 : ";
	cin >> input;
	
	if (nums[input]) {
		cout << input << "은 소수입니다." << endl;
	}
	else {
		cout << input << "은 소수가 아닙니다." << endl;
	}

	cout << "2 ~ 1023 사이의 소수: " << endl;
	int count = 0;
	int numCount = 0;
	for (int i = 0; i < 1024; i++) {
		if (count % 10 == 0 && count != 0) { // 10개당 
			cout << endl; 
			count = 0;
		}
		if (nums[i]) {
			cout << i << " ";
			count++;
			numCount++;
		}
	}
	cout << "\n\n소수의 총 갯수는 " << numCount << "개" << endl;

	vector<int> primeFactor;
	int inputCopy = input;

	if (!nums[input]) {
		for (int i = 0; input != 1; i++) {
			if (nums[i]) {
				while (input % i == 0) {
					input /= i;
					primeFactor.push_back(i);
				}
			}
		}

		cout << "(15.25)The unique prime factorization of " << inputCopy << " is : ";

		int count = 0;
		for (auto Factors : primeFactor) {
			cout << (count == 0 ? "" : " * ") << Factors;
			count++;
		}

		cout << "\n\n(15.24)prime factors: " << endl;

		auto last = unique(primeFactor.begin(), primeFactor.end());
		primeFactor.erase(last, primeFactor.end()); // 중복요소 삭제

		for (auto Factors : primeFactor) {
			cout << Factors << " ";
		}
		cout << endl;
	} // primeFactor 가 자동으로 오름차순 정렬되어 push됨
}
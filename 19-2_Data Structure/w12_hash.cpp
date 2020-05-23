#include <iostream>
#include <string>

using namespace std;

#define MAX 353333
#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

class node {
public:
	int key;
	int value;
	int flag;
	bool isChecked;
	node() {
		key = -1;
		value = -1;
		flag = NOITEM;
	}
	~node() {};
};

node hashArr[MAX];

int hashfunc(int idx) {
	return idx % MAX;
}

int hashfunc2(int idx) {
	return (17 - (idx % 17));
}

void tableInsertLinear(int key) {
	int probing = 1;

	while (hashArr[hashfunc(hashfunc(key) + (probing - 1))].flag == ISITEM) {
		probing++;
	}

	if (hashArr[hashfunc(hashfunc(key) + (probing - 1))].flag != ISITEM) {
		hashArr[hashfunc(hashfunc(key) + (probing - 1))].flag = ISITEM;
		hashArr[hashfunc(hashfunc(key) + (probing - 1))].value = hashfunc(hashfunc(key) + (probing - 1));
		hashArr[hashfunc(hashfunc(key) + (probing - 1))].key = key;
	}
}

void tableSearchLinear(int key) {
	int probing = 1;

	while (hashArr[hashfunc(hashfunc(key) + (probing - 1))].flag != NOITEM) {
		if (hashArr[hashfunc(hashfunc(key) + (probing - 1))].key == key) {
			break;
		}
		probing++;
	}
	if (hashArr[hashfunc(hashfunc(key) + (probing - 1))].key == key) {
		cout << 1 << " " << probing << endl;
	}
	else {
		cout << 0 << " " << probing << endl;
	}
}


void tableDeleteLinear(int key) {
	int probing = 1;

	while (hashArr[hashfunc(hashfunc(key) + (probing - 1))].flag != NOITEM) {
		if (hashArr[hashfunc(hashfunc(key) + (probing - 1))].key == key){
			break;
		}
		probing++;
	}
	if (hashArr[hashfunc(hashfunc(key) + (probing - 1))].key == key) {
		hashArr[hashfunc(hashfunc(key) + (probing - 1))].key = -1;
		hashArr[hashfunc(hashfunc(key) + (probing - 1))].value = -1;
		hashArr[hashfunc(hashfunc(key) + (probing - 1))].flag = AVAILABLE;
		cout << 1 << " " << probing << endl;
	}
	else {
		cout << 0 << " " << probing << endl;
	}
}


void tableInsertDouble(int key) {
	int probing = 1;

	while (hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].flag == ISITEM) {
		probing++;
	}

	if (hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].flag != ISITEM) {
		hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].flag = ISITEM;
		hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].key = key;
		hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].value = hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)));
	}
}


void tableSearchDouble(int key) {
	int probing = 1;
	
	while (hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].flag != NOITEM) {
		if (hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].key == key) {
			break;
		}
		probing++;
	}

	if (hashArr[hashfunc(hashfunc(key) + ((probing - 1) * hashfunc2(key)))].key == key) {
		cout << 1 << " " << probing << endl;
	}
	else {
		cout << 0 << " " << probing << endl;
	}
}


void tableClear() {
	for (int i = 0; i < MAX; i++) {
		hashArr[i].flag = NOITEM;
		hashArr[i].key = -1;
		hashArr[i].value = -1;
		hashArr[i].isChecked = false;
	}
}


int main() {

	int T;
	int N;
	int key;

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> key;
			tableInsertLinear(key);
		}
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> key;
			tableDeleteLinear(key);
		}
		tableClear();
	}
	return 0;
}
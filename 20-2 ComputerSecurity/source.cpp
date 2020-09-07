#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#define HEADER_SIZE 54
#define MSG_HEADER_SIZE 3
#define MSG_HEADER_IDX 54

vector<int> ctob(char);
char btoc(vector<int>);

void encode();
void decode();

const string INPUT_FILE_NAME = "origin.bmp";
const string OUTPUT_FILE_NAME = "stego.bmp";



int main(int argc, char* argv[]) {
	char option = argv[1][0];
	switch(option) {
	case 'e':
		encode();
		break;
	case 'd':
		decode();
		break;
	default:
		break;
	}

	//cout << (int)'’';

	return 0;
}

void decode() {
	ifstream in;
	string message;
	vector<int> binary;

	int msgSize = 0;
	int msgCnt = 0;
	int ptr = HEADER_SIZE + MSG_HEADER_SIZE;
	int binCnt = 0;
	int size;
	char* buf;
	char* msg_header_buf;

	in.open(OUTPUT_FILE_NAME, ios::in | ios::binary);
	in.seekg(MSG_HEADER_IDX, ios::beg);

	msg_header_buf = new char[3];
	in.read(msg_header_buf, 3);

	in.seekg(0, ios::end);
	size = in.tellg();
	buf = new char[size];
	in.seekg(0, ios::beg);
	in.read(buf, size);

	int exp = 1;
	for (int i = 0; i < MSG_HEADER_SIZE; i++) {
		msgSize += exp * (int)msg_header_buf[i];
		exp *= 256;
	}

	while (msgCnt < msgSize) {
		if (binCnt == 0) {
			binary.clear();
			binary.assign(8, 0);

			if ((int)buf[ptr] % 2 == 0) {
				binary[binCnt] = 0;
			}
			else {
				binary[binCnt] = 1;
			}
			binCnt++;
		}
		else if (binCnt == 7) {
			if ((int)buf[ptr] % 2 == 0) {
				binary[binCnt] = 0;
			}
			else {
				binary[binCnt] = 1;
			}

			char M = btoc(binary);
			message.push_back(M);
			binCnt = 0;
			msgCnt++;
		}
		else {
			if ((int)buf[ptr] % 2 == 0) {
				binary[binCnt] = 0;
			}
			else {
				binary[binCnt] = 1;
			}
			binCnt++;
		}
		ptr++;
	}

	cout << message;
	in.close();
}

void encode() {
	//ofstream out;
	ifstream in;
	ofstream out;
	string message;
	vector<int> binary;

	long ptr = 0;
	int msgCnt = 0;
	int binCnt = 0;
	int size;
	char* buf;

	getline(cin, message);
	int msgSize = message.size();

	out.open(OUTPUT_FILE_NAME, ios::out | ios::binary | ios::trunc);
	in.open(INPUT_FILE_NAME, ios::in | ios::binary);

	in.seekg(0, ios::end);
	size = in.tellg();
	in.seekg(0, ios::beg);

	buf = new char[size];
	in.read(buf, size);

	while (ptr < size) {
		if (ptr < HEADER_SIZE) {
			// 헤더
			out.write((char*)&buf[ptr], 1);
		}
		else if (HEADER_SIZE <= ptr && ptr < HEADER_SIZE + MSG_HEADER_SIZE) {
			// 메세지 헤더 추가
			out.write((char*)&msgSize, 3);
			ptr += MSG_HEADER_SIZE;
			continue;
		}
		else if (msgCnt < msgSize) {
			// 메세지
			if (binCnt == 0) {
				// 다음 글자 buffer에서 가져오기
				char M = message[msgCnt];

				binary.clear();
				binary = ctob(M);

				if ((int)buf[ptr] % 2 == 0 && binary[binCnt] == 1) {
					buf[ptr] += 1;
					out.write((char*)&buf[ptr], 1);
				}
				else if ((int)buf[ptr] % 2 == 1 && binary[binCnt] == 0) {
					int debug = buf[ptr];
					if ((int)buf[ptr] == 255) buf[ptr]--;
					else buf[ptr] += 1;
					debug = buf[ptr];
					out.write((char*)&buf[ptr], 1);
				}
				else {
					out.write((char*)&buf[ptr], 1);
				}

				binCnt++;
			}
			else if (binCnt == 7) {
				//현재 메세지 글자의 마지막 binary num
				if ((int)buf[ptr] % 2 == 0 && binary[binCnt] == 1) {
					buf[ptr] += 1;
					out.write((char*)&buf[ptr], 1);
				}
				else if ((int)buf[ptr] % 2 == 1 && binary[binCnt] == 0) {
					if ((int)buf[ptr] == 255) buf[ptr] -= 1;
					else buf[ptr] += 1;
					out.write((char*)&buf[ptr], 1);
				}
				else {
					out.write((char*)&buf[ptr], 1);
				}
				msgCnt++;
				binCnt = 0;
			}
			else {
				if ((int)buf[ptr] % 2 == 0 && binary[binCnt] == 1) {
					buf[ptr] += 1;
					out.write((char*)&buf[ptr], 1);
				}
				else if ((int)buf[ptr] % 2 == 1 && binary[binCnt] == 0) {
					if ((int)buf[ptr] == 255) buf[ptr] -= 1;
					else buf[ptr] += 1;
					out.write((char*)&buf[ptr], 1);
				}
				else {
					out.write((char*)&buf[ptr], 1);
				}

				binCnt++;

			}
		}
		else {
			// 메세지 입력 후 남은 데이터
			out.write((char*)&buf[ptr], 1);
		}
		ptr++;
	}

	in.close();
	out.close();
}

vector<int> ctob(char c) {
	vector<int> a;
	a.assign(8, 0);

	for (int i = 7; c > 0; i--)
	{
		a[i] = c % 2;
		c = c / 2;
	}

	return a;
}

char btoc(vector<int> b) {
	int exp = 1;
	int dec = 0;
	for (int i = 7; i >= 0; i--) {
		dec += b[i] * exp;
		exp *= 2;
	}
	return (char)dec;
}


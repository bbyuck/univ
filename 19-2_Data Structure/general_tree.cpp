#include <iostream>
#include <string>
#define HEAP_SIZE 1000
using namespace std;

enum direction{MIN = 1, MAX = -1};

class heap {
private:
	int h[HEAP_SIZE];
	int root;
	int last;
	int direction;
public:
	heap(int _direction) {
		h[0] = -1;
		root = 0;
		last = 0;
		direction = _direction;
	}
	int size() {
		return last;
	}
	bool isEmpty() {
		return last == 0;
	}
	
	void insert(int x) {
		if (isEmpty()) {
			root++;
			last++;
			h[last] = x;
		}
		else {
			last++;
			h[last] = x;
		}
		
		upheap(last);
	}

	void downheap(int i) {
		int tmp = i;
		int left = 2 * i;
		int right = 2 * i + 1;

		if (right <= last) {
			if (direction * h[left] <= direction * h[right]) {
				if (direction * h[tmp] > direction * h[left]) {
					node_swap(tmp, left);
					downheap(left);
				}
			}
			else {
				if (direction * h[tmp] > direction* h[right]) {
					node_swap(tmp, right);
					downheap(right);
				}
			}
		}
		else if (left <= last) {
			if (direction * h[tmp] > direction * h[left]) {
				node_swap(tmp, left);
				downheap(left);
			}
		}
	}

	int pop() {
		if (isEmpty()) {
			return -1;
		}
		else {
			int val = h[root];
			h[root] = h[last];
			h[last] = -1;
			last--;
			downheap(root);
			return val;
		}
	}
	int top() {
		if (isEmpty()) {
			return -1;
		}
		else {
			return h[root];
		}
	}

	void node_swap(int i1, int i2) {
		int tmp = h[i1];
		h[i1] = h[i2];
		h[i2] = tmp;
	}
	void upheap(int i) {
		int tmp = i;
		while ((tmp > root) && (direction * h[tmp / 2] > direction * h[tmp])) {
			node_swap(tmp, tmp / 2);
			tmp /= 2;
		}
	}


	void print() {
		if (isEmpty()) {
			cout << -1 << endl;
		}
		else {
			for (int i = 1; i <= last; i++) {
				cout << h[i] << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	heap h(MIN);

	int N;
	int num;
	string cmd;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == "insert") {
			cin >> num;
			h.insert(num);
		}
		else if (cmd == "size") {
			cout << h.size() << endl;
		}
		else if (cmd == "isEmpty") {
			cout << h.isEmpty() << endl;
		}
		else if(cmd == "print") {
			h.print();
		}
		else if (cmd == "pop") {
			cout << h.pop() << endl;
		}
		else if (cmd == "top") {
			cout << h.top() << endl;
		}
	}

	return 0;
}
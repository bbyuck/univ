#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum direction{MIN = 1, MAX = -1};

class heap {
public:
	vector<int> h;
	int last;
	int root;
	int direction;

	heap(int _direction) {
		direction = _direction;
		last = 0;
		root = 1;
		h.push_back(-1);
	}

	int size() {
		return last;
	}

	bool isEmpty() {
		return last == 0;
	}

	void insert(int k) {
		last++;
		h.push_back(k);
		upheap(last);
	}

	void node_swap(int i1, int i2) {
		int tmp = h[i1];
		h[i1] = h[i2];
		h[i2] = tmp;
	}

	void upheap(int idx) {
		int parent;
		while (idx > root) {
			parent = idx / 2;
			if ((direction * h[parent]) > (direction * h[idx])) {
				node_swap(parent, idx);
			}
			else {
				break;
			}
			idx = parent;
		}
	}

	int pop() {
		if (isEmpty()) {
			return -1;
		}
		int val = h[root];
		h[root] = h[last];
		h.pop_back();
		last--;
		downheap(root);
		return val;
	}
	void downheap(int idx) {
		int right = idx * 2 + 1;
		int left = idx * 2;

		if (right <= last) {
			if ((direction * h[right]) <= (direction * h[left])) {
				if ((direction * h[idx]) > (direction * h[right])) {
					node_swap(idx, right);
					downheap(right);
				}
			}
			else {
				if ((direction * h[idx]) > (direction * h[left])) {
					node_swap(idx, left);
					downheap(left);
				}
			}
		}
		else if (left <= last) {
			if ((direction * h[idx]) > (direction * h[left])) {
				node_swap(idx, left);
				downheap(left);
			}
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
	vector<int> minlist;
	heap minh(MIN);
	int T;
	int N;
	int p;
	int num;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N >> p;
		for (int j = 0; j < N;j++) {
			cin >> num;
			minh.insert(num);
		}
		cout << minh.h[p] << endl;
		while (!minh.isEmpty()) {
			minlist.push_back(minh.pop());
		}
		cout << minlist[p - 1 ] << endl;
		while (!minlist.empty()) {
			minlist.pop_back();
		}

	}
	return 0;
}
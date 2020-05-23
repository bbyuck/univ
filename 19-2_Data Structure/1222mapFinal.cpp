#include <iostream>
#include <string>
using namespace std;

class entry {
public:
	string key;
	string val;

	entry(string _key, string _val) {
		key = _key;
		val = _val;
	}
};

class node {
public:
	node* next;
	node* prev;
	entry* e;

	node(string _key, string _val) {
		next = NULL;
		prev = NULL;
		e = new entry(_key, _val);
	}
};

class map {
public:
	node* header;
	node* trailer;
	int n;

	map() {
		header = new node("", "");
		trailer = new node("", "");
		n = 0;
	}

	bool isEmpty() {
		return n == 0;
	}

	int size() {
		return n;
	}

	node* find(string k) {		// O(N) time
		if (isEmpty()) {
			return NULL;
		}
		node* tmp = header->next;
		while (tmp != NULL) {
			if (tmp->e->key == k) {
				return tmp;
			}
			tmp = tmp->next;
		}
		return NULL;
	}

	void put(string k, string v) {	// O(1) time
		node* newNode = new node(k, v);
		if (isEmpty())
		{
			header->next = newNode;
			newNode->prev = header;
			newNode->next = trailer;
			trailer->prev = newNode;
			n++;
			return;
		}
		else {
			node* tmp = find(k);
			if (tmp == NULL) {
				trailer->prev->next = newNode;
				newNode->prev = trailer->prev;
				newNode->next = trailer;
				trailer->prev = newNode;
				n++;
				return;
			}
			else {
				tmp->e->val = v;
				return;
			}
		}
	}

	void erase(string k) {
		if (isEmpty()) {
			cout << -1 << " ";
			return;
		}
		node* target = find(k);	// O(N) time
		
		target->prev->next = target->next;
		target->next->prev = target->prev;

		delete target;
	}
};

int main() {
	map m;

	int N;
	string k, v;
	
	string cmd;
	node* tmp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == "put") {
			cin >> k >> v;
			m.put(k, v);
		}
		else if (cmd == "empty") {
			cout << (m.isEmpty() ? "true" : "false") << endl;
		}
		else if (cmd == "find") {
			cin >> k;
			if ((tmp = m.find(k)) != NULL) {
				cout << tmp->e->key << "," << tmp->e->val << endl;
			}
			else {
				cout << "end" << endl;
			}
		}
		else if (cmd == "size") {
			cout << m.size() << endl;
		}
		else if (cmd == "erase") {
			cin >> k;
			m.erase(k);
		}
	}

	return 0;
}
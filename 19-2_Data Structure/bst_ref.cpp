#include <iostream>
#include <string>
using namespace std;

class node {
private:
	int key;
	int depth;
	int degree;
	node* parent;
	node* left;
	node* right;
	bool search_flag;
public:
	node(int k) {
		key = k;
		depth = 0;
		degree = 0;
		parent = NULL;
		left = NULL;
		right = NULL;
		search_flag = false;
	}
	bool isExternal() {
		return (left == NULL && right == NULL);
	}
	bool isInternal() {
		return (left != NULL || right != NULL);
	}
	bool isRoot() {
		return parent == NULL;
	}
	bool isExist() {
		return search_flag;
	}
	int getDepth() {
		return depth;
	}
	int getDegree() {
		return degree;
	}
	friend class bst;
};

class bst {
private:
	node* root;
	int n;
	int height;
public:
	bst() {
		root = NULL;
		n = 0;
	}
	int size() {
		return n;
	}
	bool isEmpty() {
		return n == 0;
	}
	node* lookup(int k) {
		if (isEmpty()) {
			return NULL;
		}
		else {
			node* target = root;
			target->search_flag = false;
			while (target != NULL) {
				if (k == target->key) {
					target->search_flag = true;
					return target;
				}
				if (k > target->key) {
					if (target->right == NULL) {
						return target;
					}
					target = target->right;
				}
				else if (k < target->key) {
					if (target->left == NULL) {
						return target;
					}
					target = target->left;
				}
			}
			return target;
		}
	}
	void insert(int k) {
		node* newNode = new node(k);
		if (isEmpty()) {
			root = newNode;
			n++;
			return;
		}
		else {
			node* parent = lookup(k);
			newNode->parent = parent;
			newNode->depth = parent->depth + 1;
			if (k > parent->key) {
				parent->right = newNode;
			}
			else if (k < parent->key) {
				parent->left = newNode;
			}
			parent->degree++;
			n++;
		}
	}
	node* getRoot() {
		return root;
	}

	int getDegree(node* v) {
		return v->degree;
	}

	void deletion(int k) {
		node* target = lookup(k);
		if (target->isExternal()) {            //child 0
			if (k > target->parent->key) {
				target->parent->right = NULL;
			}
			else if (k < target->parent->key) {
				target->parent->left = NULL;
			}
			delete target;
			n--;
			return;
		}
		else if (target->left != NULL && target->right != NULL) { //child 2
			node* w = lookup(k);
			int tmp;
			w = w->right;
			while (w->left != NULL) {
				w = w->left;
			}
			tmp = w->key;
			deletion(w->key);
			target->key = tmp;
		}
		else {                     //child 1
			if (target->right != NULL) {
				target->right->parent = target->parent;
				if (k > target->parent->key) {
					target->parent->right = target->right;
				}
				else if (k < target->parent->key) {
					target->parent->left = target->right;
				}
			}
			else if (target->left != NULL) {
				target->left->parent = target->parent;
				if (k > target->parent->key) {
					target->parent->right = target->left;
				}
				else if (k < target->parent->key) {
					target->parent->left = target->left;
				}
				n--;
				delete target;
			}
		}
	}

	void treeDestructor(node* v) {
		if (v == NULL) {
			return;
		}

		if (v->left != NULL) {
			treeDestructor(v->left);
		}
		if (v->right != NULL) {
			treeDestructor(v->right);
		}
		n--;
		delete(v);
	}

	void preorder(node* v) {
		if (v == NULL) {
			return;
		}
		cout << v->key << " ";
		preorder(v->left);
		preorder(v->right);
	}
};


int main() {
	bst* t = new bst();

	/*
	t->insert(5);
	t->insert(3);
	t->insert(2);
	t->insert(10);
	t->insert(8);
	t->insert(7);
	t->insert(1);
	t->insert(6);
	t->insert(15);
	t->preorder(t->getRoot());
	t->deletion(10);
	t->deletion(7);
	t->deletion(3);
	cout << endl;
	t->preorder(t->getRoot());
	t->treeDestructor(t->getRoot());
	*/

	int T;
	int N;
	int M;
	int num;
	node* target;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> num;
			t->insert(num);
		}
		cin >> M;
		for (int j = 0; j < M; j++) {
			cin >> num;
			target = t->lookup(num);
			if (target->isExist()) {
				cout << target->getDegree() << " ";
				cout << target->getDepth() << endl;
			}
			else {
				cout << 0 << endl;
			}
		}
		t->treeDestructor(t->getRoot());
		delete t;
		t = new bst();
	}

	return 0;
}
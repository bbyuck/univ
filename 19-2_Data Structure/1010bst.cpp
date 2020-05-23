#include <iostream>
#include <string>

using namespace std;

class node {
private:
	int key;
	int depth;
	int degree;
	bool exist;
	node* parent;
	node* right;
	node* left;
public:
	node(int k) {
		key = k;
		depth = 0;
		degree = 0;
		parent = NULL;
		right = NULL;
		left = NULL;
		exist = false;
	}

	bool isRoot() {
		return parent == NULL;
	}
	bool isExternal() {
		return right == NULL && left == NULL;
	}
	bool isInternal() {
		return right != NULL || left != NULL;
	}
	bool isExist() {
		return exist;
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
	int height;
public:
	bst() {
		root = NULL;
		height = 0;
	}

	bool isEmpty() {
		return root == NULL;
	}

	node* lookup(int k) {
		if (isEmpty()) {
			return NULL;
		}
		node* v = root;
		v->exist = false;
		while (v != NULL) {
			v->exist = false;
			if (k == v->key) {
				v->exist = true;
				return v;
			}
			if (k > v->key) {
				if (v->right == NULL) {
					return v;
				}
				v = v->right;
			}
			else if (k < v->key) {
				if (v->left == NULL) {
					return v;
				}
				v = v->left;
			}
		}
		return v;
	}

	void deletion(int k) {
		if (isEmpty()) {
			return;
		}
		node* target = lookup(k);
		if (target->isExternal()) {
			if (k > target->parent->key) {
				target->parent->right = NULL;
			}
			else if (k < target->parent->key) {
				target->parent->left = NULL;
			}
			delete target;
		}
		else if (target->right != NULL && target->left != NULL) {
			node* w = target->right;
			while (w->left != NULL) {
				w = w->left;
			}
			int tmp = w->key;
			deletion(w->key);
			target->key = tmp;
		}
		else {
			if (target->isRoot()) {
				if (target->left != NULL) {
					root = root->left;
				}
				else if (target->right != NULL) {
					root = root->right;
				}
				root->parent = NULL;
			}
			else {
				if (target->left != NULL) {
					if (k > target->parent->key) {
						target->parent->right = target->left;
					}
					else if (k < target->parent->key) {
						target->parent->left = target->left;
					}
					target->left->parent = target->parent;
				}
				else if (target->right != NULL) {
					if (k > target->parent->key) {
						target->parent->right = target->right;
					}
					else if (k < target->parent->key) {
						target->parent->left = target->left;
					}
					target->right->parent = target->parent;
				}
			}
			delete target;
		}
		
	}

 	void insertion(int k) {
		node* newNode = new node(k);
		if (isEmpty()) {
			root = newNode;
			height = 1;
			return;
		}
		node* target = lookup(k);
		newNode->parent = target;
		newNode->depth = target->depth + 1;
		if (height < newNode->depth) {
			height = newNode->depth;
		}
		target->degree++;
		if (k > target->key) {
			target->right = newNode;
		}
		else if (k < target->key) {
			target->left = newNode;
		}
	}


	int getHeight() {
		return height;
	}
	node* getRoot() {
		return root;
	}

	void preorder(node* v) {
		if (v == NULL) {
			return;
		}
		cout << v->key << " ";
		if (v->left != NULL) {
			preorder(v->left);
		}
		if (v->right != NULL) {
			preorder(v->right);
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
		delete v;
	}
};

int main() {
	int T;
	int N;
	int num;
	int M;
	bst* t;

	cin >> T;
	for (int i = 0; i < T; i++) {
		t = new bst();
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> num;
			t->insertion(num);
		}
		cin >> M;
		for (int j = 0; j < M; j++) {
			cin >> num;
			t->deletion(num);
		}
		t->preorder(t->getRoot());
		cout << endl;
		t->treeDestructor(t->getRoot());
	}
	return 0;
}
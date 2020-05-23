#include <iostream>
using namespace std;

class node {
private:
	int key;
	node* parent;
	node* left;
	node* right;
public:
	node(int _key) {
		key = _key;
		parent = NULL;
		left = NULL;
		right = NULL;
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
	friend class bst;
};

class bst {
private:
	node* root;
	int n;

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

	node* getRoot() {
		return root;
	}

	node* lookup(int k, node* v) {
		while (v != NULL) {
			if (v->key == k) {
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

	void insertion(int k) {
		node* target = lookup(k, root);
		node* newNode = new node(k);

		if (isEmpty()) {
			root = newNode;
		}
		else {
			newNode->parent = target;
			if (k > target->key) {
				target->right = newNode;
			}
			else if (k < target->key) {
				target->left = newNode;
			}
		}
		n++;
	}

	void deletion(int k) {
		node* target = lookup(k, root);
		node* w;
		int tmp;
		if (target->isExternal()) {										// 1. child가 없을 때(external node 일 때)
			if (target == root) {
				delete root;
				n--;
				return;
			}
			else {
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
		}
		else if (target->left != NULL && target->right != NULL) {		// 2. child가 두 개일 때
			w = target->right;
			while (w->left != NULL) {
				w = w->left;
			}
			tmp = w->key;
			deletion(w->key);
			target->key = tmp;
			n--;
			return;
		}
		else {															// 3. child가 한 개일 때
			if (target == root) {
				if (target->left != NULL) {	//left child가 존재
					root = root->left;
				}
				else if (target->right != NULL) {
					root = root->right;
				}
				delete target;
				return;
			}
			else {
				if (target->left != NULL) {	//left child가 존재
					target->left->parent = target->parent;
					if (k > target->parent->key) {
						target->parent->right = target->left;
					}
					else if (k < target->parent->key) {
						target->parent->left = target->left;
					}
				}
				else if (target->right != NULL) {
					target->right->parent = target->parent;
					if (k > target->parent->key) {
						target->parent->right = target->right;
					}
					else if (k < target->parent->key) {
						target->parent->left = target->right;
					}
				}
				delete target;
				return;
			}
		}
	}

	void inorder(node* v) {
		if (v == NULL) {
			return;
		}
		if (v->isInternal()) {
			inorder(v->left);
		}
		cout << v->key << " ";
		if (v->isInternal()) {
			inorder(v->right);
		}
	}
};

int main() {
	bst myTree;

	myTree.insertion(1);
	myTree.insertion(17);
	myTree.insertion(2);
	myTree.insertion(12);
	myTree.insertion(3);
	myTree.insertion(10);
	myTree.insertion(9);
	myTree.insertion(7);
	myTree.insertion(8);
	myTree.insertion(22);
	myTree.insertion(42);
	myTree.inorder(myTree.getRoot());
	cout << endl;
	myTree.deletion(17);
	myTree.deletion(10);
	myTree.deletion(7);
	myTree.inorder(myTree.getRoot());
	return 0;
}
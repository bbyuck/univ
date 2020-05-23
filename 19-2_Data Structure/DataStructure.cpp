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

	node* lookup(int k, node* v) {
		while (v != NULL) {
			if (k == v->key) {
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
		/*
		if (v->isExternal()) {
			return v;
		}
		if (k > v->key) {
			if (v->right == NULL) {
				return v;
			}
			v = lookup(k, v->right);
		}
		else if (k < v->key) {
			if (v->left == NULL) {
				return v;
			}
			v = lookup(k, v->left);
		}
		if (v->key == k) {
			return v;
		}
		*/
	}

	void insertion(int k) {
		node* newNode = new node(k);
		node* target;
		if (this->isEmpty()) {
			root = newNode;
		}
		else {
			target = lookup(k, root);
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
		node* target;
		int tmp;
		if (this->isEmpty()) {
			return;
		}
		else {
			target = lookup(k, root);

			if (target->isExternal()) {                           //1. target이 external node 인경우
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
			else if (target->left != NULL && target->right != NULL) {   //2. target이 두 개의 child를 갖는 경우
				node* w = target->right;
				while (w->left != NULL) {
					w = w->left;
				}
				tmp = w->key;
				if (w->isExternal() && w->parent != NULL) {
					if (k > w->parent->key) {
						w->parent->right = NULL;
					}
					else if (k < w->parent->key && w->parent != NULL) {
						w->parent->left = NULL;
					}
				}
				else if (w->isInternal()) {
					deletion(w->key);
				}
				target->key = tmp;
				if (w == NULL) {
					delete w;
				}
			}
			else {                                          //3. target이 한 개의 child를 갖는 경우                        
				if (!target->isRoot()) {
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
							target->parent->left = target->right;

						}
						target->right->parent = target->parent;
					}
				}
				else {
					if (target->left != NULL) {
						target->left->parent = NULL;
						root = target->left;
					}
					else if (target->right != NULL) {
						target->right->parent = NULL;
						root = target->right;
					}
				}
			}
			n--;
		}
	}

	void preOrder(node* v) {
		if (v == NULL) {
			return;
		}
		cout << v->key << " ";
		preOrder(v->left);
		preOrder(v->right);
	}
	void inOrder(node* v) {
		if (v == NULL) {
			return;
		}
		if (v->isExternal()) {
			inOrder(v->left);
		}
		cout << v->key << " ";
		if (v->isExternal()) {
			inOrder(v->right);
		}
	}

	node* getRoot() {
		return root;
	}
};
int main() {

	bst myTree;
	myTree.insertion(1);
	myTree.insertion(14);
	myTree.insertion(5);
	myTree.insertion(2);
	myTree.insertion(27);
	myTree.insertion(23);
	myTree.insertion(17);
	myTree.insertion(8);
	myTree.insertion(9);
	myTree.insertion(16);
	myTree.insertion(10);
	
	myTree.preOrder(myTree.getRoot());
	cout << endl;

	myTree.deletion(1);
	myTree.deletion(17);
	myTree.deletion(8);
	
	myTree.preOrder(myTree.getRoot());
	
	return 0;
}
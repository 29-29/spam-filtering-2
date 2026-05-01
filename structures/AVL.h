#ifndef AVL_H
#define AVL_H

template <class E>
struct Node {
	E data;
	Node<E> *left;
	Node<E> *right;
	int height;

	Node (E d, Node<E> *l=nullptr, Node<E> *r=nullptr) {
		this->data = d;
		this->left = l;
		this->right = r;
	}

	void setLeft(Node<E> *n) {
		this->left = n;
	}

	void setRight(Node<E> *n) {
		this->right = n;
	}
};

int max(int a, int b) {
	if (a >= b) return a;
	return b;
}

template <class E>
int height(Node<E> *n) {
	if (n == nullptr) return 0;
	int height = max(
		height(n->left),
		height(n->right)
	);
	n->height = height;
	return height
}

int getBalance(Node<E> *n) {
	if (n == nullptr) return 0;
	return height(n->right) - height(n->left);
}

template <class E>
Node<E> *leftRotate(Node<E> *n) {
	Node<E> *r = n->right;
	Node<E> *temp = r->left;

	n->right = temp;
	r->left = n;

	n->height = max(height(n->right), height(n->left)) + 1;
	r->height = max(height(r->right), height(r->left)) + 1;

	return r;
}

template <class E>
Node<E> *rightRotate(Node<E> *n) {
	Node<E> *r = n->left;
	Node<E> *temp = r->right;

	n->left = temp;
	r->right = n;

	n->height = max(height(n->right), height(n->left)) + 1;
	r->height = max(height(r->right), height(r->left)) + 1;

	return r;
}

#endif
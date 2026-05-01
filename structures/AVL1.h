#ifndef AVL1_H
#define AVL1_H

#include <iostream>

template <class E>
struct Node {
	E data;
	Node<E> *left;
	Node<E> *right;
	size_t height;

	Node(E d, Node<E> *l=nullptr, Node<E> *r=nullptr) {
		this->data = d;
		this->left = l;
		this->right = r;
		this->height = 0;
	}

	void setLeft(Node<E> *d) {
		this->left = d;
	}

	void setRight(Node<E> *d) {
		this->right = d;
	}
};

// TREE PROPERTIES

template <class E>
int treeHeight(Node<E>*);

template <class E>
int treeSize(Node<E>*);

template <class E>
int balanceFactor(Node<E>*);

template <class E>
bool isBalanced(Node<E>*);

template <class E>
// Node<E> *nextCenter(Node<E> *r, Node<E> *&parent, bool first=true);
Node<E> *nextCenter(Node<E> *r, Node<E> *&parent);

template <class E>
bool isLeaf(Node<E>*);

template <class E>
void printTree(Node<E> *r, int s=0);

template <class E>
void printTreeHeight(Node<E> *r, int s=0);

template <class E>
void printTreeBalanceFactors(Node<E>*, int=0);

int max(int, int);

// TREE MANIPULATION

template <class E>
void rebalance(Node<E>*&);

template <class E>
void binaryInsert(Node<E> *&r, E d);

template <class E>
void rotateLeft(Node<E>*&);

template <class E>
void rotateRight(Node<E>*&);

template <class E>
void treeSearch(Node<E>*, E);

template <class E>
void treeRemove(Node<E> *&r, E d);

template <class E>
void treeRemove_(Node<E> *&r, E d, Node<E> *&parent, int parentDir);

template <class E>
void treeInsert(Node<E>*&, Node<E>*&);

// MISC

template <class E>
Node<E> *maxNode(Node<E> *r, Node<E> *&trail);

#include "AVL1.cpp"
#endif
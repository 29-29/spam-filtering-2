int max(int a, int b) {
	if (a >= b) return a;
	return b;
}

template <class E>
int treeHeight(Node<E> *a) {
	if (a == nullptr) return 0;
	int height = 1 + max(
		treeHeight(a->left),
		treeHeight(a->right)
	);
	a->height = height;
	return height;
}

template <class E>
int balanceFactor(Node<E> *r) {
	return treeHeight(r->right) - treeHeight(r->left);
}

template <class E>
bool isBalanced(Node<E> *r) {
	return abs( balanceFactor(r) ) <= 1;
}

// template <class E>
// Node<E> *nextCenter(Node<E> *r, Node<E> *&parent, bool first) {
// 	if (first) {
// 		if (r->left) {
// 			first = false;
// 			return nextCenter(r->left, r, first);
// 		}
// 		else {
// 			return r;
// 		}
// 	} else {
// 		if (r->right) {
// 			first = false;
// 			return nextCenter(r->right, r, first);
// 		}
// 		else {
// 			return r;
// 		}
// 	}
// }

template <class E>
bool isLeaf(Node<E> *r) {
	return r->left == nullptr && r->right == nullptr;
}

template <class E>
void printTree(Node<E> *r, int s) {
	if (r == nullptr) return;

	if (r->right) {
		printTree(r->right, s+1);
	}

	for (int i=0; s-i; i++) std::cout << "    ";
	std::cout << r->data << "\n";

	if (r->left) {
		printTree(r->left, s+1);
	}
}

template <class E>
void printTreeHeight(Node<E> *r, int s) {
	if (!r) return;

	if (r->right) {
		printTreeHeight(r->right, s+1);
	}

	for (int i=0; s-i; i++) std::cout << "    ";
	std::cout << treeHeight(r) << "\n";

	if (r->left) {
		printTreeHeight(r->left, s+1);
	}
}

template <class E>
void rotateLeft(Node<E> *&r) {
	Node<E> *b = r, *a = r->left, *c = r->right;
	r = a;
	b->left = a->right;
	a->right = b;
}

template <class E>
void rotateRight(Node<E> *&r) {
	Node<E> *b = r, *a = r->left, *c = r->right;
	r = c;
	b->right = c->left;
	c->left = b;
}

template <class E>
void rebalance(Node<E> *&a) {
	if (isBalanced(a)) return;
	if (balanceFactor(a) > 0) {
		if (balanceFactor(a->right) < 0)
			rotateLeft(a->right);
		rotateRight(a);
	}
	else if (balanceFactor(a) < 0) {
		if (balanceFactor(a->left) > 0)
			rotateRight(a->left);
		rotateLeft(a);
	}
}

template <class E>
void printTreeBalanceFactors(Node<E> *r, int s) {
	if (r == nullptr) return;

	if (r->right) {
		printTreeBalanceFactors(r->right, s+1);
	}

	for (int i=0; s-i; i++) std::cout << "    ";
	std::cout << balanceFactor(r) << "\n";

	if (r->left) {
		printTreeBalanceFactors(r->left, s+1);
	}
}

template <class E>
int treeSize(Node<E> *r) {
	if (r == nullptr) return 0;
	return 1 + treeSize(r->left) + treeSize(r->right);
}

template <class E>
Node<E>* treeSearch(Node<E> *r, E d) {
	// Queue<Node*> searchQueue = Queue<Node*>();
	if (r == nullptr) return nullptr;
	Node<E> cur = r;
	bool found = false;
	while (cur && !found) {
		if (cur.data == d) return cur;
		else if (cur.data < d) return treeSearch(cur.left, d);
		else if (cur.data > d) return treeSearch(cur.right, d);
	}
	std::cout << "\nNOT FOUND!\n";
}

/*
template <class E>
void treeRemove(Node<E> *&r, E d) {
	if (r == nullptr) return;
	Node<E> *parent;
	bool left = true;
	if (r->data == d) {
		cout << "\nFOUND!\n";
		Node<E> *newRoot = nextCenter(r, parent, left), *oldRoot = r;
		cout << "\nGOT NEW ROOT\n";
		newRoot->left = r->left;
		newRoot->right = r->right;
		cout << "\nCONNECTED ROOT\n";
		r = newRoot;
		if (parent != oldRoot)
			parent->right = nullptr;
		delete oldRoot;
		cout << "\nDELETED!\n";
		cout << "\nFINISH!\n";
	}
}

template <class E>
void treeRemove(Node<E> *&r, E d) {
	if (r->data == d) {
		Node<E> *parent;
		Node<E> *newRoot = nextCenter(r, parent), *oldRoot = r;

		newRoot->right = oldRoot->right;
		newRoot->left = oldRoot->left;

		if (parent != oldRoot) {
			parent->right = nullptr;
		}
		else {
			delete parent;
		}
		r = newRoot;
	}
	if (d < r->data) {
		treeRemove(r->left, d);
	}
	if (d > r->data) {
		treeRemove(r->right, d);
	}

	rebalance(r);
}
*/

template <class E>
void treeInsert(Node<E> *&r, Node<E> *&d) {
	if (r == nullptr) {
		r = d;
		return;
	}

	if (d->data <= r->data) {
		if (r->left)
			treeInsert(r->left, d);
		else r->left = d;
	}

	if (d->data > r->data) {
		if (r->right)
			treeInsert(r->right, d);
		else
			r->right = d;
	}

	rebalance(r);
}

template <class E>
void binaryInsert(Node<E> *&r, E d) {
	if (r == nullptr) {
		r = new Node<E>(d);
		return;
	}
	if (d < r->data) {
		if (r->left)
			binaryInsert(r->left, d);
		else
			r->left = new Node<E>(d);
			if (r->right) r->height++;
	}
	else if (d > r->data) {
		if (r->right)
			binaryInsert(r->right, d);
		else
			r->right = new Node<E>(d);
			if (r->left) r->height++;
	}
	else { // means d == r->data
	}

	// rebalance after insert
	rebalance(r);
}

template <class E>
Node<E> *maxNode(Node<E> *r, Node<E> *&trail) {
	Node<E> *cur = r;
	for (;cur->right; trail = cur, cur = cur->right);
	return cur;
}

template <class E>
Node<E> *nextCenter(Node<E> *r, Node<E> *&parent) {
	bool first = true;
	bool notFound = true;
	Node<E> *cur = r;
	Node<E> *curnext = maxNode(r->left, cur);
	// cout << "CUR " << cur->data << "\n";
	parent = cur;
	return curnext;
}

template <class E>
void treeRemove(Node<E> *&r, E d) {
	if (d < r->data) {
		treeRemove_(r->left, d, r, -1);
	}
	else if (d > r->data) {
		treeRemove_(r->right, d, r, 1);
	}
	else {
		// if (parent != nullptr) {
		// 	if (parentDir > 0) parent->right = nullptr;
		// 	if (parentDir < 0) parent->left = nullptr;
		// }
		Node<E> *oldRoot = r;
		if (treeHeight(r)-1) {
			Node<E> *parent;
			Node<E> *newRoot = nextCenter(r, parent);

			r = newRoot;
			newRoot->right = oldRoot->right;
			if (parent != oldRoot) {
				parent->right = nullptr;
				newRoot->left = oldRoot->left;
			}
		}
		delete oldRoot;
	}
}

template <class E>
void treeRemove_(Node<E> *&r, E d, Node<E> *&parent, int parentDir) {
	std::cout << "\nchecking " << r->data;
	if (d < r->data) {
		treeRemove_(r->left, d, r, -1);
	}
	else if (d > r->data) {
		treeRemove_(r->right, d, r, 1);
	}
	else {
		std::cout << "\nvalid " << r->data << "\n";
		Node<E> *oldRoot = r;
		std::cout << "wondering if " << r->data << " is a leaf\n";
		Node<E> *newRoot = nullptr;
		if (!isLeaf(r)) {
			Node<E> *parent;
			newRoot = nextCenter(r, parent);

			r = newRoot;
			newRoot->right = oldRoot->right;
			if (parent != oldRoot) {
				parent->right = nullptr;
				newRoot->left = oldRoot->left;
			}
		}
		if (parentDir > 0) {
			std::cout << "parent at left\n";
			parent->setRight(newRoot);
		}
		if (parentDir < 0) {
			std::cout << "parent at right\n";
			parent->setLeft(newRoot);
		}
		delete oldRoot;
	}
}
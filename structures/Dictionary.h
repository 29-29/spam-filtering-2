#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "AVL1.h"
#include "Word.h"

class Dictionary {
	Node<Word*>* dict;

	void attemptAddWord(Node<Word*>*&r, const std::string& w, const bool& spamFlag) {
		if (r == nullptr) {
			r = new Node<Word*>(new Word(w, spamFlag));
			return;
		}
		if (*(r->data) > w) {
			if (r->left)
				attemptAddWord(r->left, w, spamFlag);
			else
				r->left = new Node<Word*>(new Word(w, spamFlag));
				if (r->right) r->height++;
		}
		else if (*(r->data) < w) {
			if (r->right)
				attemptAddWord(r->right, w, spamFlag);
			else
				r->right = new Node<Word*>(new Word(w, spamFlag));
				if (r->left) r->height++;
		}
		else { // means d == r->data
		 if (spamFlag) r->data->addSpam();
		 else r->data->addHam();
		}

		// rebalance after insert
		rebalance(r);
	}

	void attemptPrint(Node<Word*>* node, std::ostream& out) {
		if (node == nullptr) return;
		attemptPrint(node->left, out);
		out << *(node->data) << std::endl;
		attemptPrint(node->right, out);
	}

public:
	Dictionary() {
		this->dict = nullptr;
	}

	void addWord(const std::string& w, const bool& spamFlag) {
		attemptAddWord(this->dict, w, spamFlag);
	}

	void print(std::ostream& out) {
		attemptPrint(this->dict, out);
	}
};

#endif
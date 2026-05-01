#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
	std::string word;
	bool isHam;
	bool isSpam;
	size_t hamCount;
	size_t spamCount;
public:
	Word(std::string w, bool spamFlag) {
		this->word = w;
		this->isHam = !spamFlag;
		this->isSpam = spamFlag;
		this->hamCount = !spamFlag;
		this->spamCount = spamFlag;
	}

	void addSpam() {
		this->spamCount++;
		if (isSpam == false)
			this->isSpam = true;
		std::cout << "ADD SPAM";
	}

	void addHam() {
		this->hamCount++;
		if (isHam == false)
			this->isHam = true;
		std::cout << "ADD HAM";
	}

	friend std::ostream& operator<<(std::ostream& out, const Word& w) {
		out << w.word << " " << w.hamCount << " " << w.spamCount;
		return out;
	}

	friend std::ostream& operator<<(std::ostream& out, const Word*& w) {
		out << w->word << " " << w->hamCount << " " << w->spamCount;
		return out;
	}

	// OBJECT COMPARISON
	bool operator<(const Word& other) {
		return this->word < other.word;
	}

	bool operator<=(const Word& other) {
		return this->word <= other.word;
	}

	bool operator>(const Word& other) {
		return this->word > other.word;
	}

	bool operator>=(const Word& other) {
		return this->word >= other.word;
	}

	bool operator==(const Word& other) {
		return this->word == other.word;
	}

	bool operator!=(const Word& other) {
		return this->word != other.word;
	}

	// STRING COMPARISON
	bool operator<(const std::string& str) {
		return this->word < str;
	}

	bool operator<=(const std::string& str) {
		return this->word < str;
	}

	bool operator>(const std::string& str) {
		return this->word > str;
	}

	bool operator>=(const std::string& str) {
		return this->word >= str;
	}

	bool operator==(const std::string& str) {
		return this->word == str;
	}

	bool operator!=(const std::string& str) {
		return this->word != str;
	}
};

#endif
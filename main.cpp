#include "structures/Dictionary.h"
#include <iostream>
#include <csignal>
#include <fstream>
#include <chrono>
#include <ctime>

std::ofstream outFile;
Dictionary dict;
auto start = std::chrono::high_resolution_clock::now();
int emailsProcessed;

void handleSignal(int signal) {
	auto stop = std::chrono::high_resolution_clock::now();
	double duration = (double)(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()) / 1000000;
	outFile.open("dictionary");
	dict.print(outFile);
	outFile.close();
	std::ofstream log("log");
	log << "Processed " << emailsProcessed << " emails." << std::endl;
	log << "Time elapsed " << duration << " seconds";
	log.close();
	exit(signal);
}

bool isTime(const std::string& w) {
	if (w.length() != 8)
		return false;

	for (int i = 0; i < w.length(); ++i) {
		if (i == 2 || i == 5) {
			if (w[i] != ':')
				return false;
		} else if (!isdigit(w[i]))
			return false;
	}
}

bool isWord(const std::string& w) {
	for (char c : w) {
		if (!isalpha(c)) return false;
	}
	return true;
}

int main() {
	std::signal(SIGINT, handleSignal);
	std::ifstream index("../spam-filtering/trec06p/full/index");
	std::string currentFile;

	size_t spacePos;
	std::string flag;
	std::string location;

	std::ifstream file;
	std::string word;
	
	const int EMAILS_TO_PROCESS = 500;
	emailsProcessed = 0;
	while (std::getline(index, currentFile, '\n')) {
		spacePos = currentFile.find(' ');
		flag = currentFile.substr(0, spacePos);
		location = currentFile.substr(spacePos + 3);
		std::cout << "reading " << location << std::endl;

		file.open("../spam-filtering/trec06p" + location);
		// while (std::getline(file, word, ' ')) {
		// 	dict.addWord(word, flag == "spam");
		// }
		while (file >> word) {
			// if (isalpha(word[0]) && !isTime(word))
			if (isWord(word))
				dict.addWord(word, flag == "spam");
		}
		file.close();
		emailsProcessed++;
	}
	std::cout << "DONE!";
	handleSignal(SIGINT);
}
#include <string>
#include <sstream>
#include "../include/answer.h"

const std::string Answer::filename = "answers.txt";
const std::string Answer::indexFilename = "answers_index.txt";
std::string Answer::filePath = "";
std::string Answer::indexFilePath = "";

void Answer::extract(std::string line) {
	std::stringstream tmp(line);
	std::string tmp_ano;

	std::getline(tmp, tmp_ano, '|');
	this->answerNumber = std::stoi(tmp_ano);

	std::getline(tmp, this->answer);
}

std::string Answer::getFilePath() {
	return Answer::filePath;
}

std::string Answer::getIndexFilePath() {
	return Answer::indexFilePath;
}

int Answer::getPrimaryKey() {
	return this->answerNumber;
}

void Answer::setDifficultyLevel(int choice) {
	std::string path;
	switch (choice) {
	case 1:
		path = "./files/easy/";
		break;
	case 2:
		path = "./files/moderate/";
		break;
	case 3:
		path = "./files/hard/";
		break;
	}
	Answer::filePath = path + Answer::filename;
	Answer::indexFilePath = path + Answer::indexFilename;
}
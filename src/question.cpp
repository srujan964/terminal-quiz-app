#include <string>
#include <sstream>
#include "../include/question.h"

const std::string Question::filename = "questions.txt";
const std::string Question::indexFilename = "questions_index.txt";
std::string Question::filePath = "";
std::string Question::indexFilePath = "";

void Question::extract(std::string line) {
	std::stringstream tmp(line);
	std::string tmp_qno;

	std::getline(tmp, tmp_qno, '|');
	this->questionNumber = std::stoi(tmp_qno);

	std::getline(tmp, this->question, '|');
	std::getline(tmp, this->optionA, '|');
	std::getline(tmp, this->optionB, '|');
	std::getline(tmp, this->optionC, '|');
	std::getline(tmp, this->optionD);

}

std::string Question::getFilePath() {
	return filePath;
}

std::string Question::getIndexFilePath() {
	return indexFilePath;
}

int Question::getPrimaryKey() {
	return this->questionNumber;
}

void Question::setDifficultyLevel(int choice) {
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
	Question::filePath = path + Question::filename;
	Question::indexFilePath = path + Question::indexFilename;
}
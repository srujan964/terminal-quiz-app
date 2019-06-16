#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../include/index.h"
#include "../include/record_list.h"
#include "../include/leaderboard.h"

const std::string Leaderboard::filePath = "./files/leaderboard.txt";
const std::string Leaderboard::indexFilePath = "./files/leaderboard_index.txt";

std::vector<Leaderboard> Leaderboard::rankVector;

std::string Leaderboard::getFilePath() {
	return Leaderboard::filePath;
}

std::string Leaderboard::getIndexFilePath() {
	return Leaderboard::indexFilePath;
}

std::string Leaderboard::getPrimaryKey() {
	return this->username;
}

void Leaderboard::extract(std::string line) {
	std::stringstream tmp(line);
	std::string str_score;

	std::getline(tmp, this->username, '|');
	
	std::getline(tmp, str_score, '|');
	this->score = std::stoi(str_score);

	std::getline(tmp, this->difficulty);
}

void Leaderboard::init() {
	std::string filePath = Leaderboard::filePath;
	std::fstream file;
	file.open(filePath, std::ios::out | std::ios::app);
	file.close();
}

void Leaderboard::readIntoList() {
	RecordList<Leaderboard> recordList;
	std::string filePath = Leaderboard::filePath;
	recordList.readIntoList(filePath);

	Leaderboard::rankVector = recordList.recordVector;

	if (!Leaderboard::rankVector.empty()) {
		std::sort(std::begin(Leaderboard::rankVector), std::end(Leaderboard::rankVector), [](auto &left, auto &right) {
			return left.score > right.score;
		});
	}
}

void Leaderboard::write() {
	std::string filePath = Leaderboard::filePath;
	std::fstream file;
	file.open(filePath, std::ios::out);

	if (!file) {
		std::cerr << "File Open Fail: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!Leaderboard::rankVector.empty()) {
		std::sort(std::begin(Leaderboard::rankVector), std::end(Leaderboard::rankVector), [](auto &left, auto &right) {
			return left.score > right.score;
		});

		for (Leaderboard standing : rankVector) {
			std::stringstream buf;
			buf << standing.username << "|" << standing.score << "|" << standing.difficulty << std::endl;
			file << buf.rdbuf();
		}
	}
	
	file.close();
	Index<Leaderboard> leaderboardIndex;
	leaderboardIndex.initialize();
}


void Leaderboard::displayRankings() {
	int i = 1;
	std::cout << std::setw(35) << "RANK" 
		<< std::setw(15) << "USERNAME" 
		<< std::setw(15) << "SCORE" 
		<< std::setw(15) << "DIFFICULTY" << std::endl;
	for (auto record : Leaderboard::rankVector) {
		std::cout << std::setw(35) << i++ 
			<< std::setw(15) << record.username
			<< std::setw(15) << record.score 
			<< std::setw(15) << record.difficulty << std::endl;
	}
}


void Leaderboard::searchRankings(std::string username) {
	bool matchFound = false;
	for (Leaderboard standing : rankVector) {
		if (standing.username == username) {
			matchFound = true;
			std::cout << standing.username << "\t\t" << standing.score << "\t\t" << standing.difficulty << std::endl;
			break;
		}
	}

	if (!matchFound)
		std::cout << "Couldn't find that username in the Leaderboard." << std::endl;
}

bool Leaderboard::isUnique(std::string username) {
	std::string filePath = Leaderboard::filePath;
	std::fstream file;
	file.open(filePath, std::ios::in);

	if (!file) {
		std::cerr << "File Open Fail: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}
	Leaderboard tmp; 
	std::string line;
	while (std::getline(file, line)) {
		tmp.extract(line);
		if (tmp.username == username) {
			std::cout << "Username already exists. Choose another." << std::endl;
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}
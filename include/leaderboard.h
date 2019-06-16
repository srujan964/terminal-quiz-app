#ifndef QUIZ_APPLICATION_INCLUDE_LEADERBOARD_H_
#define QUIZ_APPLICATION_INCLUDE_LEADERBOARD_H_
#pragma once

#include <string>
#include <fstream>
#include <vector>

class Leaderboard {
public:
	int score = 0;
	std::string username;
	std::string difficulty;
	
	const static std::string filePath;
	const static std::string indexFilePath;
	static std::vector<Leaderboard> rankVector;
	
	static void init();
	static std::string getFilePath();
	static std::string getIndexFilePath();
	static bool isUnique(std::string username);
	static void searchRankings(std::string username);


	std::string getPrimaryKey();
	void extract(std::string);
	void readIntoList();
	void write();
	void displayRankings();
	
	bool operator == (const Leaderboard& l) const { return username == l.username; }
	bool operator != (const Leaderboard& l) const { return !operator==(l); }

};
#endif
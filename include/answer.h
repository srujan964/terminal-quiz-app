#ifndef QUIZ_APPLICATION_INCLUDE_ANSWER_H_
#define QUIZ_APPLICATION_INCLUDE_ANSWER_H_

#include <string>

class Answer {
private:
	static std::string filePath;
	static std::string indexFilePath;
	const static std::string filename;
	const static std::string indexFilename;

public:
	int answerNumber = 0;
	std::string answer;

	static std::string getFilePath();
	static std::string getIndexFilePath();
	static void setDifficultyLevel(int);
	void extract(std::string);
	int getPrimaryKey();
};

#endif
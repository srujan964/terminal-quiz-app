#ifndef QUIZ_APPLICATION_INCLUDE_QUESTION_H_
#define QUIZ_APPLICATION_INCLUDE_QUESTION_H_

#include <string>

class Question {
private:
	static std::string filePath;
	static std::string indexFilePath;
	const static std::string filename;
	const static std::string indexFilename;

public:
	int questionNumber = 0;
	std::string question;
	std::string optionA;
	std::string optionB;
	std::string optionC;
	std::string optionD;

	static std::string getFilePath();
	static std::string getIndexFilePath();
	static void setDifficultyLevel(int choice);
	void extract(std::string);
	int getPrimaryKey();
};

#endif
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include "../include/index.h"
#include "../include/question.h"
#include "../include/answer.h"
#include "../include/record_list.h"
#include "../include/leaderboard.h"

Leaderboard StartQuiz(std::string username) {
	std::system("cls");
	int difficulty = -1;

	do {
		std::cout << "\n1 -> Easy (1 Mark)\n2 -> Moderate (2 Marks)\n3 -> Hard (5 Marks)" << std::endl;
		std::cout << "Choose your difficulty level: ";
		std::string inp;
		std::getline(std::cin, inp);
		std::stringstream sin(inp);
		
		if (!(sin >> difficulty)) {
			std::cout << "Invalid choice. Try again." << std::endl;
			continue;
		} 
		else if (difficulty < 1 || difficulty > 3)
			std::cout << "Invalid choice. Try again." << std::endl;
	} while (difficulty < 1 || difficulty > 3);

	int step = 0;

	switch (difficulty) {
	case 1:
		step = 1;
		break;
	case 2:
		step = 2;
		break;
	case 3:
		step = 5;
		break;
	}

	Question::setDifficultyLevel(difficulty);
	Answer::setDifficultyLevel(difficulty);

	Index<Question> questionIndex;
	questionIndex.initialize();

	Index<Answer> answerIndex;
	answerIndex.initialize();

	std::string questionFilePath = Question::getFilePath();

	RecordList<Question> questionList;
	questionList.readIntoList(questionFilePath);
	std::vector<Question> questions = questionList.getRandomRecords();

	int score = 0;

	for (auto record : questions) {
		std::string userInput;
		do {
			std::cout << std::endl << record.question << std::setw(10) << "\nA: "
				<< record.optionA << std::setw(10) << "\tB: "
				<< record.optionB << std::setw(10) << "\tC: "
				<< record.optionC << std::setw(10) << "\tD: "
				<< record.optionD << std::endl;
			std::cout << "Your answer: ";
			std::cin >> userInput;

			std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

			if(!(userInput == "A" || userInput == "B" || userInput == "C" || userInput == "D"))
				std::cout << "Invalid choice. Try again." << std::endl;
		} while (!(userInput == "A" || userInput == "B" || userInput == "C" || userInput == "D"));


		int primaryKey = record.getPrimaryKey();
		Answer answer = answerIndex.readRecordFromIndex(primaryKey);

		if (userInput == answer.answer) {
			std::cout << "Correct!" << std::endl;
			score += step;
		}
		else {
			std::cout << "Incorrect :(" << std::endl;
		}
	}
	int total = step * 10;
	std::cout << std::endl << "Your score is: " << score  << " out of " << total << std::endl;

	Leaderboard standing;
	standing.username = username;
	standing.score = score;

	switch (difficulty) {
	case 1:
		standing.difficulty = "Easy";
		break;
	case 2:
		standing.difficulty = "Moderate";
		break;
	case 3:
		standing.difficulty = "Hard";
		break;
	}

	return standing;
}

int main() {
	std::cout << "\n\n\n";
	std::cout << std::setw(70) << "QUIZ APPLICATION\n\n" << std::endl;
	std::string username;
	Leaderboard::init();
	
	do {
		std::cout << "Enter player name: ";
		std::getline(std::cin, username);
	} while (Leaderboard::isUnique(username));

	Leaderboard standing = StartQuiz(username);

	standing.readIntoList();
	Leaderboard::rankVector.push_back(standing);

	std::list<Leaderboard> tempList;
	std::copy(Leaderboard::rankVector.begin(), Leaderboard::rankVector.end(), std::back_inserter(tempList));

	standing.write();

	char retry;
	std::cout << "Do you wish to retry? (Y/N): ";
	std::cin >> retry;

	if (retry == 'Y' || retry == 'y') {
		tempList.remove(standing);
		standing = StartQuiz(username);
		
		std::vector<Leaderboard> tempVector;
		std::copy(tempList.begin(), tempList.end(), std::back_inserter(tempVector));
		
		Leaderboard::rankVector = tempVector;
		Leaderboard::rankVector.push_back(standing);

		standing.write();
	}

	int choice;
	std::cout << "\n1 -> Display All Rankings\n2 -> Search Rankings\n3 -> Exit" << std::endl;
	std::cout << "\nEnter your choice: ";
	std::cin >> choice;

	switch (choice) {
		case 1: {
			standing.displayRankings();
			break;
		}
		case 2: {
			std::string name;
			std::cout << "Enter the name of the user you want to search: ";
			std::cin >> name;
			standing.searchRankings(name);
			break;
		}
		case 3: {
			exit(EXIT_SUCCESS);
		}
	}
	
	std::cout << std::endl << std::endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
#ifndef QUIZ_APPLICATION_INCLUDE_RECORD_LIST_H_
#define QUIZ_APPLICATION_INCLUDE_RECORD_LIST_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

template <class T>
class RecordList {
public:
	std::vector<T> recordVector;

	void readIntoList(std::string filename);
	std::vector<T> getRandomRecords();
};

template <class T>
void RecordList<T>::readIntoList(std::string filePath) {
	std::fstream file;
	file.open(filePath, std::ios::in);

	if (!file) {
		std::cerr << "File Open Fail: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}

	T record;

	std::string line;
	while (std::getline(file, line)) {
		record.extract(line);
		this->recordVector.push_back(record);
	}
	file.close();
}

template <class T>
std::vector<T> RecordList<T>::getRandomRecords() {
	std::vector<T> records = this->recordVector;
	auto rng = std::default_random_engine{};

	std::shuffle(std::begin(records), std::end(records), rng);

	std::vector<T> outputVector;
	std::sample(records.begin(), records.end(), std::back_inserter(outputVector), 10, std::mt19937{ std::random_device{}()});
	
	return outputVector;
}

#endif
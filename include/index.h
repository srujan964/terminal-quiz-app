#ifndef QUIZ_APPLICATION_INCLUDE_INDEX_H_
#define QUIZ_APPLICATION_INCLUDE_INDEX_H_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

template <class T>
class Index {
public:
	static std::string indexFilePath;
	std::vector<T> recordVector;

	Index<T> () {
		indexFilePath = T::getIndexFilePath();
	}

	void initialize();
	T readRecordFromIndex(int);
};

//Declare the static member indexFilename. (avoids the LNK2001 error)
template <class T> std::string Index<T>::indexFilePath;

//Indexes the records of the record file into the index file.
template <class T>
void Index<T>::initialize() {
	std::string recordFilePath = T::getFilePath();
	std::fstream recordFile, indexFile;

	recordFile.open(recordFilePath, std::ios::in);
	if (!recordFile) {
		std::cerr << "File Open Fail: " << recordFilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	indexFile.open(indexFilePath, std::ios::out);
	if (!indexFile) {
		std::cerr << "Index File Open Fail: " << indexFilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	T record;
	std::streamoff offset;

	offset = recordFile.tellg();
	while (std::getline(recordFile, line)) {
		record.extract(line);
		std::stringstream buf;
		buf << record.getPrimaryKey() << "|" << offset << std::endl;
		indexFile << buf.rdbuf();

		//This is the offset of the next record. Neglected in the case of the last record.
		offset = recordFile.tellg();
	}

	recordFile.close();
	indexFile.close();
}

/*
	Matches the primaryKey parameter with a record in the index file
	and retreives the record at the correspoding offset from the record
	file.
*/

template <class T>
T Index<T>::readRecordFromIndex(int primaryKey) {
	bool indexMatch = false;
	std::fstream indexFile, recordFile;
	std::string recordFilePath = T::getFilePath();

	recordFile.open(recordFilePath, std::ios::in);

	if (!recordFile) {
		std::cerr << "File Open Fail: " << recordFilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	indexFile.open(indexFilePath, std::ios::in);

	if (!indexFile) {
		std::cerr << "Index File Open Fail: " << indexFilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	T record;
	std::string  str_offset, str_number;
	while (std::getline(indexFile, str_number, '|')) {
		int number = std::stoi(str_number);

		if (primaryKey == number) {
			indexMatch = true;
			std::string line;
			std::getline(indexFile, str_offset);
			int offset = std::stoi(str_offset);
			
			//Seek to the offset of matched record in the corresponding record file.
			recordFile.seekg(offset);
			std::getline(recordFile, line);
			record.extract(line);
			break;
		}

		std::getline(indexFile, str_offset);
	}

	indexFile.close();
	recordFile.close();
	return record;
}
#endif
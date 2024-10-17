#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Record {
	std::string date;
	double income;
	double expense;
	Record* next;
};

class programSystem {
private:
	Record* head;
public:
	programSystem() : head(nullptr) {}
	void help();
	void record_();
	void delete_(const std::string& targetDate);
	void show(const std::string& targetdate);
};
#endif
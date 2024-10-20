#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <Windows.h>
#include <chrono>
#include <sqlite3.h>


class programSystem {
private:
	std::string date;
	double income;
	double expense;
public:
	programSystem();
	void help(const std::string& help);
	void initDatabase();
	static void setColor(int color);
	void showAll();
	void record_(const std::string& targetDate);
	void delete_(const std::string& targetDate);
	void show(const std::string& targetdate);
};
#endif
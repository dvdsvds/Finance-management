#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <Windows.h>
#include <sqlite3.h>


class programSystem {
private:
	std::string date;
	double income;
	double expense;
public:
	void initDatabase();
	programSystem();

	static void setColor(int color);
	void help(const std::string& help);
	void record_(const std::string& targetDate);

	// commands for displaying data
	void delete_(const std::string& targetDate);
	void deleteAll();
	void deleteYear();

	// commands for displaying data
	void show(const std::string& targetdate);
	void showAll();
	void showYear(const std::string& targetYear);
	void showMonth(const std::string& targetMonth);

};
#endif
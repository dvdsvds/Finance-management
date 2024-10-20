#include "system.h"
using namespace std;

void programSystem::help() {
	cout << "function : "
}

// console text color
void programSystem::setColor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

void programSystem::initDatabase() {
	sqlite3* db;
	char* errMsg = 0;

	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB : " << sqlite3_errmsg(db) << endl;
		return;
	}
	string sql = "CREATE TABLE IF NOT EXISTS records ("
		"date TET PRIMARY KEY, "
		"income REAL, "
		"expense REAL);";

	exit = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
	if (exit != SQLITE_OK) {
		cerr << "SQL error : " << errMsg << endl;
		sqlite3_free(errMsg);
	}

	sqlite3_close(db);
}

programSystem::programSystem() {
	initDatabase();
}

void programSystem::record_(const string& targetdate) {
	double income, expense;
	setColor(2);
	cout << "INCOME : ";
	cin >> income;
	setColor(7);

	setColor(4);
	cout << "EXPENSE : ";
	cin >> expense;
	setColor(7);

	cin.ignore();

	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB : " << sqlite3_errmsg(db) << endl;
		return;
	}

	string sql = "INSERT INTO records(date, income, expense)"
		"VALUES ('" + targetdate + "', " + to_string(income) + ", " + to_string(expense) + ");";

	char* errMsg = 0;
	exit = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
	if (exit != SQLITE_OK) {
		cerr << "SQL error : " << errMsg << endl;
		sqlite3_free(errMsg);
	}
	sqlite3_close(db);
}

void programSystem::delete_(const string& targetDate) {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}

	string sql = "DELETE FROM records WHERE date = '" + targetDate + "';";

	char* errMsg = 0;
	exit = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
	if (exit != SQLITE_OK) {
		cerr << "SQL error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}

	sqlite3_close(db);
}

void programSystem::show(const string& targetDate) {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}

	string sql = "SELECT date, income, expense FROM records WHERE date = '" + targetDate + "';";

	auto callback = [](void* notUsed, int argc, char** argv, char** colNames) -> int {
		for (int i = 0; i < argc; i++) {
			if (strcmp(colNames[i], "income") == 0) {
				setColor(2);
			}
			else if (strcmp(colNames[i], "expense") == 0) {
				setColor(4);
			}
			else {
				setColor(7);
			}
			cout << colNames[i] << ": " << argv[i] << endl;
		}
		setColor(7);
		return 0;
		};

	char* errMsg = 0;
	exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
	if (exit != SQLITE_OK) {
		cerr << "SQL error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}

	sqlite3_close(db);
}

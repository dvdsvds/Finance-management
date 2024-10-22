#include "system.h"
using namespace std;

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
		"date TEXT PRIMARY KEY, "
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

void programSystem::help(const string& help) {

	if (help == "funtion" || help == "f") {
		cout << "[NAME]"<< endl;
		cout << "  funtion" << endl;
		cout << "[syntax]" << endl;
		cout << "  -r(-record) : Save the data." << endl;
		cout << "  Ex) funtion -r [date], funtion -record [date], f -r [date], f -record [date]" << endl << endl;
		cout << "  -s(-show) : Display the saved data." << endl;;
		cout << "  Ex) funtion -s [date], funtion -show [date], f -s [date], f -show [date]" << endl << endl;
		cout << "  -sa(-showall) : Display all of the saved data" << endl;
		cout << "  Ex) funtion -sa, funtion -showall, f -sa, f -showall" << endl << endl;
		cout << "  -d(-delete) : Delete the saved date." << endl;
		cout << "  Ex) funtion -d [date], funtion -delete [date], f -d [date], f -delete [date]" << endl;
	}
	else if (help == "about") {
		cout << "Display program info." << endl;
	}
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

// commands for deleteing the data
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
	else {
		cout << "All data deleted successfully." << endl;
	}

	sqlite3_close(db);
}
void programSystem::deleteAll() {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB:" << sqlite3_errmsg(db) << endl;
		return;
	}

	string sql = "DELETE FROM records;";

	char* errMsg = 0;
	exit = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
	if (exit != SQLITE_OK) {
		cerr << "SQL error: " << errMsg << endl;
		sqlite3_free(errMsg);
		sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, &errMsg);
	}
	else {
		sqlite3_exec(db, "COMMIT;", nullptr, nullptr, &errMsg);
		cout << "All data deleted successfully." << endl;
	}

	sqlite3_close(db);
}
void programSystem::deleteYear() {

}
// commands for displaying the data
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
void programSystem::showAll() {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}

	string sql = "SELECT * FROM records;";

	auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
		for (int i = 0; i < argc; i++) {
			if (string(colNames[i]) == "date") {
				setColor(3);
			}
			cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
			setColor(7);
		}
		return 0;
	};

	char* errMsg = 0;
	exit = sqlite3_exec(db, sql.c_str(), callback, this, &errMsg);
	if (exit != SQLITE_OK) {
		cerr << "SQL error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}


	sqlite3_close(db);
}
void programSystem::showYear(const string& targetYear) {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}
	string sql = "SELECT date, income, expense FROM records WHERE strftime('%Y', date) = '" + targetYear + "';";
	auto callback = [](void* notUsed, int argc, char** argv, char** colNames) -> int {
		for (int i = 0; i < argc; i++) {
			if (strcmp(colNames[i], "date") == 0) {
				setColor(3);
			}
			else {
				setColor(7);
			}
			cout << colNames[i] << ": " << argv[i] << endl;
		}
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
void programSystem::showMonth(const string& targetMonth) {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}
	string sql = "SELECT date, income, expense FROM records WHERE strftime('%m', date) = '" + targetMonth + "';";
	auto callback = [](void* notUsed, int argc, char** argv, char** colNames) -> int {
		for (int i = 0; i < argc; i++) {
			if (strcmp(colNames[i], "date") == 0) {
				setColor(3);
			}
			else {
				setColor(7);
			}
			cout << colNames[i] << ": " << argv[i] << endl;
		}
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

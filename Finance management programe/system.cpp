#include "system.h"
using namespace std;
void programSystem::help() {
	//todo
}

void programSystem::record_() {
	string date;
	double income, expense;
	cout << "DATE(YYYY-MM-DD) : ";
	getline(cin, date);
	cout << "INCOME : ";
	cin >> income;
	cout << "EXPENSE : ";
	cin >> expense;

	// using getline removes the LF remaining in the buffer after cin
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

	Record* newRecord = new Record{ date, income, expense, head };
	head = newRecord;
}

void programSystem::delete_(const string& targetDate) {
	if (!head) {
		cout << "No exist." << endl;
		return;
	}

	Record* current = head;
	Record* previous = nullptr;

	while (current) {
		if (current->date == targetDate) {
			if (previous) {
				previous->next = current->next; // edit link
			}
			else {
				head = current->next;
			}
			delete current;
			cout << "Record deleted." << endl;
			return;
		}
		previous = current;
		current = current->next;
	}
	cout << "No record found for the given date." << endl;
}

void programSystem::show(const string& targetDate) {
	if (!head) {
		cout << "No records abailable." << endl;
		return;
	}
	
	Record* current = head;
	bool found = false;

	while (current) {
		if (current->date == targetDate) {
			cout << "DATE : " << current->date << endl;
			cout << "INCOME : " << current->income << endl;
			cout << "EXPENSE : " << current->expense << endl;
			found = true;
		}
		current = current->next;
	}
}
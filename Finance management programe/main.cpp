/* 
Finane management Programe
- function -
1. record and delete incomes and expenses
*/

#include "system.h"
using namespace std;

int main() {
	programSystem s;
	cout << "-Finane management Programe-" << endl;
	cout << "Author : dvdsvds" << endl;
	cout << "GitHub Address : https://github.com/dvdsvds" << endl;
	// record income and expenses
	while (true) {
		string command;
		cout << "> ";
		getline(cin, command);

		// split the sentence(command) based on whitespace
		vector<string> words;
		istringstream iss(command);
		string word;

		while (iss >> word) {
			words.push_back(word);
		}

		if (!words.empty()) {
			transform(words[0].begin(), words[0].end(), words[0].begin(), ::tolower);
			if (words[0] == "help" || words[0] == "h") { // command : help
				s.help();
			}
			else if (words[0] == "function" || words[0] == "f") {
				if (words.size() > 2) {
					string opt = words[1];
					string targetdate = words[2];

					if (opt == "-record" || opt == "-r") {
						s.record_();
					}
					else if (opt == "-delete" || opt == "-d") {
						s.delete_(targetdate);
					}
					else if (opt == "-show" || opt == "-s") {
						s.show(targetdate);
					}
					else {
						cout << "Unknown Command : "<< opt << "" << endl;
					}
				}
			}
			else if (words[0] == "exit") { // command : exit
				return 0;
			}
			else { // when a wrong command was typed by the user
				cout << "This is not a correct command." << endl << "Please type again." << endl;
			}

		}
	}
	return 0;
}
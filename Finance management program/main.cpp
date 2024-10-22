/*
Finane management Programe
- function -
1. record and delete incomes and expenses
*/

#include "system.h"
using namespace std;

int main() {
	programSystem s;
	cout << "Finane management Program [Version 0.1]" << endl;
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
				if (words.size() > 1) {
					string howToUseCommand = words[1];
					s.help(howToUseCommand);

				}
			}
			else if (words[0] == "function" || words[0] == "f") {
				if (words.size() == 1) {
					cout << "No command provided." << endl;
				}
				else if (words.size() >= 2) {
					string opt = words[1];

					if (opt == "-showall" || opt == "-sa") {
						s.showAll();
					}
					
					if (opt == "-record" || opt == "-r") {
						if (words.size() == 3) {
							string targetdate = words[2];
							s.record_(targetdate);
						}
					}

					else if (opt == "-delete" || opt == "-d") {
						if(words.size() == 3) {
							string answer;
							string targetdate = words[2];
							s.show(targetdate);
							cout << "Are you sure you want to delete?" << endl;
							cout << "> ";
							getline(cin, answer);
							if (answer == "yes" || answer == "y") {
								s.delete_(targetdate);
							}
							else if (answer == "No" || answer == "n") {
								cout << "Cancle." << endl;
							}

						}
					}
					else if (opt == "-deleteall" || opt == "-da") {
						string answer;
						cout << "Are you sure you want to delete all data?" << endl;
						cout << "> ";
						getline(cin, answer);
						if (answer == "yes" || answer == "y") {
							s.deleteAll();
						}
						else if (answer == "No" || answer == "n") {
							cout << "Cancle." << endl;
						}
						
					}
					else if (opt == "-show" || opt == "-showyear" || opt == "-showmonth" || opt == "-s" || opt == "-sy" || opt == "-sm") {
						if (words.size() >= 3) {
							string targetdate = words[2];
							if (opt == "-sy") {
								s.showYear(targetdate);
							}
							else if (opt == "-sm") {
								s.showMonth(targetdate);
							}
							else if(opt == "-s") {
								s.show(targetdate);
							}
							else {
								cout << "Unknown Command : " << opt << endl;
							}
						}
					}
					else if (opt == "-showall" || opt == "-sa") {
						s.showAll();
					}
					else {
						cout << "Unknown Command : " << opt << endl;
					}
				}
			}
			else if (words[0] == "exit") { // command : exit
				return 0;
			}
			else if (words[0] == "about") {
				cout << "Author : dvdsvds" << endl;
				cout << "GitHub Address : https://github.com/dvdsvds" << endl;
			}

			else { // when a wrong command was typed by the user
				cout << "This is not a correct command." << endl << "Please type again." << endl;
			}

		}
	}
	return 0;
}
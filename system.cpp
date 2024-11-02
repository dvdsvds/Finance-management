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

// commands to show help
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
		cout << "  -da(-deleteall) : Delete all of the saved date." << endl;
		cout << "  Ex) funtion -da [date], funtion -deleteall [date], f -da [date], f -deleteall [date]" << endl;
	}
	else if (help == "about") {
		cout << "Display the program's info." << endl;
	}
}

// commands to save the data
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

// commands to delete the save data
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
void programSystem::deleteYear(const string& targetYear) {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}
	string sql = "DELETE FROM records WHERE strftime('%Y', date) = '" + targetYear + "';";


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
void programSystem::deleteMonth(const string& targetMonth) {
	sqlite3* db;
	int exit = sqlite3_open("finance.db", &db);
	if (exit) {
		cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
		return;
	}
	string sql = "DELETE FROM records WHERE strftime('%m', date) = '" + targetMonth + "';";


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

// commands display the save data
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

// commands for network
void Server::connectServer(const string& serverIP, int port) {
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		cerr << "WSAStartup failed : " << WSAGetLastError() << endl;
		return;
	}
	else {
		cout << "Testing..." << endl;
		cout << "WSAStartup success" << endl;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		cerr << "socket failed : " << WSAGetLastError() << endl;
	}
	else {
		cout << "socket success" << endl;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, serverIP.c_str(), &server_addr.sin_addr) <= 0) {
		cerr << "Invalid address/ Address not supported : " << serverIP.c_str() << endl;
		return;
	}
	
	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		cerr << "connect failed : " << WSAGetLastError() << endl;
		return ;
	}
	else {
		cout << "connect success" << endl;
	}

	const char* message = "hi, server";
	send(sock, message, strlen(message), 0);
	cout << "Sent to server : " << message << endl;

	char buffer[1024] = { 0 };
	recv(sock, buffer, sizeof(buffer), 0);
	cout << "Receved to server : " << buffer << endl;

	closesocket(sock);
	WSACleanup();
}
void Server::handleClient(SOCKET client_fd) {
	char buffer[1024];
	string nickname;

	int recv_size = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (recv_size > 0) {
		buffer[recv_size] = '\0';
		nickname = string(buffer);
		cout << nickname << " has joined the chat." << endl;

		for (const auto& client : clients) {
			if (client != client_fd) {
				programSystem::setColor(3);
				string welcomeMessage = nickname + " has joined the chat\n";
				programSystem::setColor(7);
				send(client, welcomeMessage.c_str(), welcomeMessage.size(), 0);
			}
		}
	}


	while (true) {
		recv_size = recv(client_fd, buffer, sizeof(buffer), 0);
		if (recv_size <= 0) {
			cerr << "client disconnected" << endl;
			break;
		}
		buffer[recv_size] = '\0';

		string msg = "\r[" + nickname + "]< " + string(buffer);
		
		for (const auto& client : clients) {
			if (client != client_fd) {
				send(client, msg.c_str(), msg.size(), 0);
			}
		}
	}
	closesocket(client_fd);
	clients.erase(remove(clients.begin(), clients.end(), client_fd), clients.end());
	cout << nickname << " has left the chat." << endl;
}
void Server::openServer(const string& serverIP, int port) {
	int server_fd, client_fd;
	struct sockaddr_in server_addr;
	char buffer[1024] = { 0 };

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
		cerr << "WSAStartup failed : " << WSAGetLastError() << endl;
		return;
	}
	else {
		cout << "WSAStartup success" << endl;
	}
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		cerr << "Socket failed : " << WSAGetLastError() << endl;
		return;
	}
	else {
		cout << "Socket success" << endl;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, serverIP.c_str(), &server_addr.sin_addr) < 0) {
		cerr << "wrong address" << endl;
		return;
	}

	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		cerr << "bind failed :" << WSAGetLastError() << endl;
		return;
	}
	else {
		cout << "bind success" << endl;
	}

	if (listen(server_fd, 3) < 0) {
		cerr << "listen failed : " << WSAGetLastError() << endl;
		closesocket(server_fd);
		return;
	}
	else {
		cout << "listen success" << endl;
	}

	cout << "server is listening on port " << port << "..." << endl;

	while (true) {
		client_fd = accept(server_fd, nullptr, nullptr);
		if (client_fd == INVALID_SOCKET) {
			cerr << "accept failed : " << WSAGetLastError() << endl;
			closesocket(server_fd);
			return;
		}
		else {
			cout << "client connected" << endl;
			clients.push_back(client_fd);

			thread(&Server::handleClient, this, client_fd).detach();
		}
	
	}
	closesocket(client_fd);
	closesocket(server_fd);
}


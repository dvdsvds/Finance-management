#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
// winsock2, ws2tcpip는 항상 windows.h보다 위에 include
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <sqlite3.h>
#include <cstring>
#include <thread>


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
	void deleteYear(const std::string& targetYear);
	void deleteMonth(const std::string& targetMonth);

	// commands for displaying data
	void show(const std::string& targetDate);
	void showAll();
	void showYear(const std::string& targetYear);
	void showMonth(const std::string& targetMonth);

	// etc

};


#pragma comment(lib, "ws2_32.lib")
class Server {
private:
	std::string server_addr;
	int port;
	std::vector<SOCKET> clients;
	std::vector<std::string> nicknames;
public:
	// command for connection server
	void connectServer(const std::string& server_addr, int port);
	void openServer(const std::string& server_addr, int port);
	void handleClient(SOCKET client_fd);

};
#endif
#ifndef USER_H
#define USER_H

#include <string>

class Database; // declaration

class User {
	protected:
		std::string username;
		std::string password;

	public:
		User(std::string u, std::string p) : username(u), password(p) {}

		virtual ~User() = default;

		std::string getUsername() { return username; }

		std::string getPassword() { return password; }

		bool checkPassword(std::string p) { return password == p; }

		virtual void menu(Database& db) = 0;
};

#endif
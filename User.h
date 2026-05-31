#ifndef USER_H
#define USER_H

#include <string>

class Database; // declaration

class User 
{
	protected:
		std::string username;
		std::string password;

	public:
		User(std::string username, std::string password) : username(username), password(password) {}

		virtual void menu(Database& db) = 0;
		virtual std::string getRole() = 0;
		std::string getUsername();
		std::string getPassword();
		void viewMovies(Database& db);
};
#endif
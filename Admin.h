#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

class Database;

class Admin : public User
{
	public:
		Admin(std::string username, std::string password) : User(username, password) {}

		void menu(Database& db);
		void addMovie(Database& db);
		void deleteMovie(Database& db);
		std::string getRole();
};

#endif
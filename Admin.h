#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

class Database;

class Admin : public User
{
	public:
		Admin(std::string u, std::string p) : User(u, p) {}

		void menu(Database& db) override;

		void addMovie(Database& db);
};

#endif
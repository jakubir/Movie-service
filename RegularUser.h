#ifndef REGULARUSER_H
#define REGULARUSER_H

#include "User.h"
#include <string>

class Database;

class RegularUser : public User
{
	public:
		RegularUser(std::string u, std::string p) : User(u, p) {}

		void menu(Database& db) override;

		void rateMovie(Database& db);

		void addReview(Database& db);
};

#endif
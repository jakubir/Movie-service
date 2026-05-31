#ifndef REGULARUSER_H
#define REGULARUSER_H

#include "User.h"
#include <string>

class Database;

class RegularUser : public User
{
	public:
		RegularUser(std::string username, std::string password) : User(username, password) {}

        void menu(Database &db);
        void rateMovie(Database& db);
        void viewMovieReviews(Database& db);
		void addReview(Database& db);
};

#endif
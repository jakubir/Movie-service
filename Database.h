#ifndef DATABASE_H
#define DATABASE_H

#include "User.h"
#include "Movie.h"
#include <vector>
#include <string>

class Database {
	private:
		std::vector<User*> users;
		std::vector<Movie> movies;

	public:
		~Database();

		void loadUsers();

		void saveUsers();

		void loadMovies();

		void saveMovies();

		void addUser(User* u);

		void addMovie(Movie m);

		User* authenticate(std::string u, std::string p);

		std::vector<Movie>& getMovies();
};

#endif
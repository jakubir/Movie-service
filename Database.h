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
		bool addUser(User* user);
		void addMovie(Movie movie);
		User* authenticate(std::string username, std::string password);
		std::vector<Movie>& getMovies();

};

#endif
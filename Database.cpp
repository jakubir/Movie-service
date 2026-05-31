#include "Database.h"
#include "Admin.h"
#include "RegularUser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <typeinfo>

Database::~Database()
{
	for (auto u : users) delete u;
}

void Database::loadUsers()
{
	std::ifstream file("users.txt");
	std::string line;
	while (std::getline(file, line)) 
	{
		std::stringstream ss(line);
		std::string type, username, password;
		ss >> type >> username >> password;
		if (type == "admin")
			users.push_back(new Admin(username, password));
		else if (type == "user")
			users.push_back(new RegularUser(username, password));
	}
}

void Database::saveUsers()
{
	std::ofstream file("users.txt");
	for (auto u : users) 
	{
		std::string type = dynamic_cast<Admin*>(u) ? "admin" : "user";
		file << type << " " << u->getUsername() << " " << u->getPassword() << std::endl;
	}
}

void Database::loadMovies()
{
	std::ifstream file("movies.txt");
	std::string line;
	while (std::getline(file, line)) 
	{
		size_t pos1 = line.find('|');
		size_t pos2 = line.find('|', pos1 + 1);
		if (pos1 != std::string::npos && pos2 != std::string::npos) 
		{
			std::string title = line.substr(0, pos1);
			std::string director = line.substr(pos1 + 1, pos2 - pos1 - 1);
			int year = std::stoi(line.substr(pos2 + 1));
			movies.push_back(Movie(title, director, year));
		}
	}
	// Load ratings and reviews separately if needed, but for simplicity, assume movies.txt has basic info
}

void Database::saveMovies()
{
	std::ofstream file("movies.txt");
	for (auto& m : movies) {
		file << m.getTitle() << "|" << m.getDirector() << "|" << m.getYear() << std::endl;
	}
	// Save ratings and reviews to separate files if needed
	// check for | in strings
}

void Database::addUser(User* u)
{
	users.push_back(u);
	saveUsers();
}

void Database::addMovie(Movie m)
{
	movies.push_back(m);
	saveMovies();
}

User* Database::authenticate(std::string u, std::string p)
{
	for (auto user : users)
		if (user->getUsername() == u && user->checkPassword(p)) 
			return user;

	return nullptr;
}

std::vector<Movie>& Database::getMovies()
{
	return movies;
}
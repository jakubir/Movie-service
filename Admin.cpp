#include "Admin.h"
#include "Database.h"
#include "Movie.h"
#include <iostream>
#include <string>

void Admin::menu(Database& db)
{
	int choice;
	do {
		std::cout << "\nAdmin Menu:\n";
		std::cout << "1. Add Movie\n";
		std::cout << "2. View Movies\n";
		std::cout << "3. Logout\n";
		std::cout << "Choice: ";
		std::cin >> choice;
		switch (choice) {
			case 1:
				addMovie(db);
				break;
			case 2:
				if (db.getMovies().size() == 0)
					std::cout << "No movies in database\n";
				else
					for (auto& m : db.getMovies())
						std::cout << m.getTitle() << " by " << m.getDirector() << " (" << m.getYear() << ")\n";
				break;
			case 3:
				break;
			default:
				std::cout << "Invalid choice\n";
		}
	} while (choice != 3);
}

void Admin::addMovie(Database& db)
{
	std::string title, director;
	int year;
	std::cout << "Enter title: ";
	std::cin.ignore();
	std::getline(std::cin, title);
	std::cout << "Enter director: ";
	std::getline(std::cin, director);
	std::cout << "Enter year: ";
	std::cin >> year;
	db.addMovie(Movie(title, director, year));
	std::cout << "Movie added.\n";
}
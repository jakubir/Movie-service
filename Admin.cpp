#include "Admin.h"
#include "Database.h"
#include "Movie.h"
#include "InputUtils.h"
#include <iostream>
#include <string>

void Admin::menu(Database& db)
{
	int choice;
	do 
	{
		std::cout << "\nAdmin Menu:\n";
		std::cout << "1. Add Movie\n";
		std::cout << "2. View Movies\n";
		std::cout << "3. Delete Movie\n";
		std::cout << "4. Logout\n";
		std::cout << "Choice: ";
		if (!readInt(choice)) {
			std::cout << "Invalid choice\n";
			continue;
		}
		switch (choice) {
			case 1:
				addMovie(db);
				break;
			case 2:
				viewMovies(db);
				break;
			case 3:
				deleteMovie(db);
				break;
			case 4:
				break;
			default:
				std::cout << "Invalid choice\n";
		}
	} while (choice != 4);
}

void Admin::addMovie(Database& db)
{
	std::string title, director;
	int year;
	std::cout << "Enter title: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, title);
	std::cout << "Enter director: ";
	std::getline(std::cin, director);
	std::cout << "Enter year: ";
	std::cin >> year;
	db.addMovie(Movie(title, director, year));
	std::cout << "Movie added.\n";
}

void Admin::deleteMovie(Database& db)
{
	std::cout << "Enter movie index to delete: ";
	int index;
	if (!readInt(index)) {
		std::cout << "Invalid index.\n";
		return;
	}
	if (index > 0 && index <= db.getMovies().size()) 
	{
		db.getMovies().erase(db.getMovies().begin() + index - 1);
		db.saveMovies();
		std::cout << "Movie deleted.\n";
	} else
		std::cout << "Invalid index.\n";
}

std::string Admin::getRole()
{
	return "Admin";
}
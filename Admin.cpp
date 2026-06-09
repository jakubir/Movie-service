#include "Admin.h"
#include "Database.h"
#include "Movie.h"
#include "Utils.h"
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

		if (!readIndex(choice)) 
		{
			std::cout << "Invalid choice\n";
			continue;
		}

		switch (choice) 
		{
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

	// check if title or director does not contain |, used as a delimiter in file storage
	if (title.find('|') != std::string::npos || director.find('|') != std::string::npos) 
	{
		std::cout << "Title and director cannot contain '|'\n";
		return;
	}

	std::cout << "Enter year: ";
	if (!readIndex(year))
	{
		std::cout << "Invalid year.\n";
		return;
	}

	db.addMovie(Movie(title, director, year));
	std::cout << "Movie added.\n";
}

void Admin::deleteMovie(Database& db)
{
	int index;
	std::cout << "Enter movie index to delete: ";

	if (!readIndex(index)) // allow only integers for index
	{
		std::cout << "Invalid index.\n";
		return;
	}

	if (index > 0 && index <= db.getMovies().size())  // validate index range
	{
		db.removeMovie(index - 1);
		std::cout << "Movie deleted.\n";
	}
	else
		std::cout << "Invalid index.\n";
}

std::string Admin::getRole()
{
    return "admin";
}
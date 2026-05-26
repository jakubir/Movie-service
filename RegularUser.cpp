#include "RegularUser.h"
#include "Database.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <limits>

void RegularUser::menu(Database& db)
{
	int choice;
	do {
		std::cout << "User Menu:\n";
		std::cout << "1. View Movies\n";
		std::cout << "2. Rate Movie\n";
		std::cout << "3. Add Review\n";
		std::cout << "4. Logout\n";
		std::cout << "Choice: ";
		std::cin >> choice;
		switch (choice) {
			case 1:
				for (size_t i = 0; i < db.getMovies().size(); ++i) {
					auto& m = db.getMovies()[i];
					std::cout << i+1 << ". " << m.getTitle() << " by " << m.getDirector() << " (" << m.getYear() << ") Avg Rating: " << m.getAverageRating() << std::endl;
					m.displayReviews();
				}
				break;
			case 2:
				rateMovie(db);
				break;
			case 3:
				addReview(db);
				break;
			case 4:
				break;
			default:
				std::cout << "Invalid choice\n";
		}
	} while (choice != 4);
}

void RegularUser::rateMovie(Database& db)
{
	std::cout << "Enter movie index to rate: ";
	size_t index;
	std::cin >> index;
	if (index > 0 && index <= db.getMovies().size()) {
		int rating;
		std::cout << "Enter rating (1-10): ";
		std::cin >> rating;
		db.getMovies()[index-1].addRating(username, rating);
		std::cout << "Rating added.\n";
	} else {
		std::cout << "Invalid index.\n";
	}
}

void RegularUser::addReview(Database& db)
{
	std::cout << "Enter movie index to review: ";
	size_t index;
	std::cin >> index;
	if (index > 0 && index <= db.getMovies().size()) {
		std::string review;
		std::cout << "Enter review: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, review);
		db.getMovies()[index-1].addReview(username, review);
		std::cout << "Review added.\n";
	} else {
		std::cout << "Invalid index.\n";
	}
}
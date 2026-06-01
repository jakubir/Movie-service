#include "RegularUser.h"
#include "Database.h"
#include "Movie.h"
#include "Utils.h"
#include <iostream>
#include <string>

void RegularUser::menu(Database& db)
{
	int choice;
	
	do 
	{
		std::cout << "\nUser Menu:\n";
		std::cout << "1. View Movies\n";
		std::cout << "2. Rate Movie (change / remove existing)\n";
		std::cout << "3. Add Review (change / remove existing)\n";
		std::cout << "4. Check Movie Reviews\n";
		std::cout << "5. Logout\n";
		std::cout << "Choice: ";

		if (!readIndex(choice)) 
		{
			std::cout << "Invalid choice\n";
			continue;
		}

		switch (choice) 
		{
			case 1:
				viewMovies(db);
				break;
			case 2:
				rateMovie(db);
				break;
			case 3:
				addReview(db);
				break;
			case 4:
				viewMovieReviews(db);
				break;
			case 5:
				break;
			default:
				std::cout << "Invalid choice\n";
		}
	} while (choice != 5);
}

void RegularUser::rateMovie(Database& db)
{
	int index;
	std::cout << "Enter movie index to rate: ";

	if (!readIndex(index)) 
	{
		std::cout << "Invalid index.\n";
		return;
	}

	if (index > 0 && index <= db.getMovies().size()) 
	{
		int rating;
		std::cout << "Enter rating (1-10, or 0 to remove): ";

		if (!readIndex(rating)) // allow only integers for rating
		{
			std::cout << "Invalid rating.\n";
			return;
		}

		if (rating < 0 || rating > 10) // validate rating range
		{
			std::cout << "Invalid rating.\n";
			return;
		}

		db.getMovies()[index-1].setRating(username, rating);
		db.saveMovies();

		if (rating == 0)
			std::cout << "Rating removed.\n";
		else
			std::cout << "Rating saved.\n";
	} 
	else
		std::cout << "Invalid index.\n";
}

void RegularUser::viewMovieReviews(Database& db)
{
	int index;
	std::cout << "Enter movie index to view reviews: ";

	if (!readIndex(index)) // allow only integers for index
	{
		std::cout << "Invalid index.\n";
		return;
	}

	if (index > 0 && index <= db.getMovies().size()) // validate index range
	{
		auto& movie = db.getMovies()[index-1];
		std::cout << movie.getTitle() << " by " << movie.getDirector() << " (" << movie.getYear() << ")\n";

		if (movie.getReviews().empty())
			std::cout << "No reviews for this movie.\n";
		else
			movie.displayReviews();
	} 
	else
		std::cout << "Invalid index.\n";
}

void RegularUser::addReview(Database& db)
{
	int index;
	std::cout << "Enter movie index to review: ";

	if (!readIndex(index)) // allow only integers for index
	{
		std::cout << "Invalid index.\n";
		return;
	}

	if (index > 0 && index <= db.getMovies().size()) // validate index range
	{
		std::string review;

		std::cout << "Enter review (leave empty to remove your review): ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, review);
		
		db.getMovies()[index-1].setReview(username, review);
		db.saveMovies();

		if (review.empty())
			std::cout << "Review removed.\n";
		else
			std::cout << "Review saved.\n";
	} 
	else
		std::cout << "Invalid index.\n";
}

std::string RegularUser::getRole()
{
	return "Regular";
}
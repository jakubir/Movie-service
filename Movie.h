#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

struct Rating {
    std::string user;
    int rating;
};

struct Review {
    std::string user;
    std::string review;
};

class Movie {
	private:
		std::string title;
		std::string director;
		int year;
		std::vector<Rating> ratings;
		std::vector<Review> reviews;

	public:
		Movie(std::string title, std::string director, int year);

		std::string getTitle();
		std::string getDirector();
		int getYear();
		void addRating(std::string user, int rating);
		void addReview(std::string user, std::string review);
		void setRating(std::string user, int rating);
		void setReview(std::string user, std::string review);
		bool removeRating(std::string user);
		bool removeReview(std::string user);
		std::vector<Rating> getRatings();
		std::vector<Review> getReviews();
		double getAverageRating();
		void displayReviews();
};

#endif
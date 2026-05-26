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
		Movie(std::string t, std::string d, int y) : title(t), director(d), year(y) {}

		std::string getTitle() { return title; }

		std::string getDirector() { return director; }

		int getYear() { return year; }

		void addRating(std::string user, int r) { ratings.push_back({user, r}); }

		void addReview(std::string user, std::string rev) { reviews.push_back({user, rev}); }

		double getAverageRating();

		void displayReviews();
};

#endif
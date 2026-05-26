#include "Movie.h"
#include <iostream>

double Movie::getAverageRating()
{
	if (ratings.empty()) return 0.0;
	double sum = 0;
	for (auto& r : ratings) sum += r.rating;
	return sum / ratings.size();
}

void Movie::displayReviews()
{
	for (auto& rev : reviews) {
		std::cout << rev.user << ": " << rev.review << std::endl;
	}
}
#include "Movie.h"
#include <iostream>

Movie::Movie(std::string title, std::string director, int year) : title(title), director(director), year(year) {}

std::string Movie::getTitle()
{
    return title;
}

std::string Movie::getDirector()
{
    return director;
}

int Movie::getYear()
{
    return year;
}

void Movie::addRating(std::string user, int rating)
{
    ratings.push_back({user, rating});
}

void Movie::addReview(std::string user, std::string review)
{
    reviews.push_back({user, review});
}

void Movie::setRating(std::string user, int rating)
{
    for (auto& r : ratings)
        if (r.user == user) 
        {
            if (rating == 0) // remove rating if 0
                removeRating(user);
            else
                r.rating = rating;
            
            return;
        }

    if (rating != 0)
        ratings.push_back({user, rating});
}

void Movie::setReview(std::string user, std::string review)
{
    for (auto& r : reviews)
        if (r.user == user) 
        {
            if (review.empty()) // remove review if empty
                removeReview(user);
            else
                r.review = review;
        
            return;
        }

    if (!review.empty())
        reviews.push_back({user, review});
}

bool Movie::removeRating(std::string user)
{
    for (auto it = ratings.begin(); it != ratings.end(); ++it)
        if (it->user == user) 
        {
            ratings.erase(it);
            return true;
        }
    
    return false;
}

bool Movie::removeReview(std::string user)
{
    for (auto it = reviews.begin(); it != reviews.end(); ++it)
        if (it->user == user) 
        {
            reviews.erase(it);
            return true;
        }
        
    return false;
}

std::vector<Rating> Movie::getRatings()
{
    return ratings;
}

std::vector<Review> Movie::getReviews()
{
    return reviews;
}

double Movie::getAverageRating()
{
    if (ratings.empty())
        return 0;

    double sum = 0;

    for (auto& r : ratings)
        sum += r.rating;

    return sum / ratings.size();
}

void Movie::displayReviews()
{
    for (auto& r : reviews)
        std::cout << r.user << ": " << r.review << std::endl;
}
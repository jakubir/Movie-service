#include "Database.h"
#include "Admin.h"
#include "RegularUser.h"
#include <fstream>
#include <iostream>
#include <string>

Movie* Database::findMovie(std::vector<Movie>& movies, std::string title, std::string director, int year)
{
    for (auto& movie : movies) 
    {
        if (movie.getTitle() == title && movie.getDirector() == director && movie.getYear() == year)
            return &movie;
    }

    return nullptr;
}

Database::~Database()
{
    for (auto u : users) 
        delete u;
}

void Database::loadUsers()
{
    users.clear();

    std::ifstream file("users.txt");
    std::string type, username, password;

    while (file >> type >> username >> password) 
    {
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
        file << type << " " << u->getUsername() << " " << u->getPassword() << "\n";
    }
}

void Database::loadMovies()
{
    movies.clear();

    std::ifstream moviesFile("movies.txt");
    std::string title, director, yearStr;
    
    while (
        std::getline(moviesFile, title, '|') && 
        std::getline(moviesFile, director, '|') && 
        std::getline(moviesFile, yearStr)
        ) 
    {
        movies.push_back(Movie(title, director, std::stoi(yearStr)));
    }

    std::ifstream ratingsFile("ratings.txt");
    std::string user, ratingStr;

    while (
        std::getline(ratingsFile, title, '|') && 
        std::getline(ratingsFile, director, '|') && 
        std::getline(ratingsFile, yearStr, '|') && 
        std::getline(ratingsFile, user, '|') && 
        std::getline(ratingsFile, ratingStr)
        ) 
    {
        int year = std::stoi(yearStr);
        int rating = std::stoi(ratingStr);

        if (auto movie = findMovie(movies, title, director, year))
            movie->addRating(user, rating);
    }

    std::ifstream reviewsFile("reviews.txt");
    std::string review;

    while (
        std::getline(reviewsFile, title, '|') && 
        std::getline(reviewsFile, director, '|') && 
        std::getline(reviewsFile, yearStr, '|') && 
        std::getline(reviewsFile, user, '|') && 
        std::getline(reviewsFile, review)
        ) 
    {
        int year = std::stoi(yearStr);

        if (auto movie = findMovie(movies, title, director, year))
            movie->addReview(user, review);
    }
}

void Database::saveMovies()
{
    std::ofstream moviesFile("movies.txt");
    for (auto& m : movies) {
        moviesFile << m.getTitle() << "|" << m.getDirector() << "|" << m.getYear() << "\n";
    }

    std::ofstream ratingsFile("ratings.txt");
    for (auto& m : movies)
        for (auto& r : m.getRatings()) 
            ratingsFile << m.getTitle() << "|" << m.getDirector() << "|" << m.getYear() << "|" << r.user << "|" << r.rating << "\n";

    std::ofstream reviewsFile("reviews.txt");
    for (auto& m : movies)
        for (auto& rev : m.getReviews()) 
            reviewsFile << m.getTitle() << "|" << m.getDirector() << "|" << m.getYear() << "|" << rev.user << "|" << rev.review << "\n";
}

bool Database::addUser(User* u)
{
    for (auto user : users)
        if (user->getUsername() == u->getUsername())
            return false;

    users.push_back(u);
    saveUsers();
    return true;
}

void Database::addMovie(Movie m)
{
    movies.push_back(m);
    saveMovies();
}

User* Database::authenticate(std::string u, std::string p)
{
    for (auto user : users)
        if (user->getUsername() == u && user->getPassword() == p)
            return user;

    return nullptr;
}

std::vector<Movie>& Database::getMovies()
{
    return movies;
}
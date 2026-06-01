#include "Database.h"
#include "Admin.h"
#include "RegularUser.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

Database::~Database()
{
    for (auto u : users) 
        delete u;
}

void Database::loadUsers()
{
    users.clear();

    std::ifstream file("users.txt");
    
    if (!file.is_open()) 
    {
        std::cout << "Could not open users.txt\n";
        return;
    }

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

    if (!file.is_open()) 
    {
        std::cout << "Could not open users.txt\n";
        return;
    }

    for (auto u : users) 
        file << u->getRole() << " " << u->getUsername() << " " << u->getPassword() << "\n";
}

void Database::loadMovies()
{
    movies.clear();

    std::ifstream moviesFile("movies.txt");

    if (!moviesFile.is_open()) 
    {
        std::cout << "Could not open movies.txt\n";
        return;
    }

    std::string title, director, yearStr;
    
    while (
        std::getline(moviesFile, title, '|') && 
        std::getline(moviesFile, director, '|') && 
        std::getline(moviesFile, yearStr)
        ) 
    {
        movies.push_back(Movie(title, director, std::stoi(yearStr)));
    }

    std::ifstream userdataFile("userdata.txt");

    if (!userdataFile.is_open()) 
    {
        std::cout << "Could not open userdata.txt\n";
        return;
    }

    std::string indexStr, user, ratingStr, review;

    while (
        std::getline(userdataFile, indexStr, '|') && 
        std::getline(userdataFile, user, '|') && 
        std::getline(userdataFile, ratingStr, '|') && 
        std::getline(userdataFile, review)
        ) 
    {
        int index = std::stoi(indexStr);
        int rating = std::stoi(ratingStr);

        if (index >= 0 && index < movies.size())
        {
            if (rating > 0)
                movies[index].addRating(user, rating);
            
            if (!review.empty())
                movies[index].addReview(user, review);
        }
    }
}

void Database::saveMovies()
{
    std::ofstream moviesFile("movies.txt");

    if (!moviesFile.is_open()) 
    {
        std::cout << "Could not open movies.txt\n";
        return;
    }

    for (auto& m : movies) {
        moviesFile << m.getTitle() << "|" << m.getDirector() << "|" << m.getYear() << "\n";
    }

    std::ofstream userdataFile("userdata.txt");

    if (!userdataFile.is_open()) 
    {
        std::cout << "Could not open userdata.txt\n";
        return;
    }

    for (int i = 0; i < movies.size(); ++i)
    {
        auto& m = movies[i];
        
        // Combine ratings and reviews by username
        std::map<std::string, std::pair<int, std::string>> userdata; // username -> (rating, review)
        
        for (auto& r : m.getRatings())
            userdata[r.user].first = r.rating;
        
        for (auto& rev : m.getReviews())
            userdata[rev.user].second = rev.review;
        
        // Write combined userdata
        for (auto& entry : userdata)
            userdataFile << i << "|" << entry.first << "|" << entry.second.first << "|" << entry.second.second << "\n";
    }
}

bool Database::addUser(User* u)
{
    // check if username already exists
    for (auto user : users)
        if (user->getUsername() == u->getUsername()) 
        {
            delete u;
            return false;
        }

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
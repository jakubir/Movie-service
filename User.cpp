#include "User.h"
#include "Database.h"
#include <iostream>

void User::viewMovies(Database& db)
{
    if (db.getMovies().empty()) 
    {
        std::cout << "No movies in database\n";
        return;
    }

    for (int i = 0; i < db.getMovies().size(); ++i) 
    {
        auto& m = db.getMovies()[i];
        std::cout << i + 1 << ". " << m.getTitle() << " by " << m.getDirector() << " (" << m.getYear() << ") ";
        m.getAverageRating() ? std::cout << "Avg Rating: " << m.getAverageRating() : std::cout << "No ratings";
        std::cout << "\n";
    }
}

std::string User::getUsername() 
{ 
    return username; 
}

std::string User::getPassword() 
{ 
    return password; 
}

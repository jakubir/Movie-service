# Movie Service

A C++ program that simulates a movie service similar to Filmweb or IMDb. It uses object-oriented programming principles and stores data in text files.

## Features

- User registration and login with password protection
- Administrator and regular user accounts
- Administrators can add movies to the database
- Users can rate movies (1-10) and add reviews
- Data persistence through text files

## Classes

- `User`: Base class for users
- `Admin`: Inherits from User, can add movies
- `RegularUser`: Inherits from User, can rate and review movies
- `Movie`: Represents a movie with ratings and reviews
- `Database`: Handles data loading and saving

## Building and Running

Compile with:
```
g++ main.cpp User.cpp Admin.cpp RegularUser.cpp Movie.cpp Database.cpp -o movie_service -std=c++11
```

Or use the provided Makefile:
```
make
```

Then run:
```
./movie_service
```

Default admin account: username `admin`, password `admin`



report in pdf format

title page - my name and teacher name, title, polsl logo

intro -

external spec - how user can use the program - with screenshots

internal spec - describe my implementation, the most important parts, architecture, what class does what

testing - 

conclusion - what i think about the project after i finished it

together with source code in .zip

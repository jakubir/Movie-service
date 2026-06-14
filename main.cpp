#include "Database.h"
#include "Admin.h"
#include "RegularUser.h"
#include "Utils.h"
#include <iostream>
#include <string>

int main()
{
	Database db;
	db.loadUsers();
	db.loadMovies();

	if (!db.authenticate("admin", "admin"))
		db.addUser(new Admin("admin", "admin")); // Add default admin if not exists

	User* currentUser;
	int choice;

	std::cout << "=== Movie service ===";
	do 
	{
		std::cout << "\n1. Login\n";
		std::cout << "2. Register\n";
		std::cout << "3. Exit\n";
		std::cout << "Choice: ";

		if (!readInt(choice)) {
			std::cout << "Invalid choice\n";
			continue;
		}

		std::string username, password;

		switch (choice)
		{
			case 1: // login
				std::cout << "Username: ";
				std::cin >> username;
				std::cout << "Password: ";
				std::cin >> password;
				
				currentUser = db.authenticate(username, password);
				if (currentUser) 
					currentUser->menu(db);
				else
					std::cout << "Invalid credentials.\n";

				break;

			case 2: // register
				std::cout << "Username: ";
				std::cin >> username;
				std::cout << "Password: ";
				std::cin >> password;

				if (db.addUser(new RegularUser(username, password))) // check if username already exists
					std::cout << "User registered.\n";
				else
					std::cout << "User already exists.\n";

				break;

			case 3: // exit
				break;

			default:
				std::cout << "Invalid choice\n";
		}

	} while (choice != 3);

	return 0;
}
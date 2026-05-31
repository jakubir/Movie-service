#include "Database.h"
#include "Admin.h"
#include "RegularUser.h"
#include <iostream>
#include <string>

int main()
{
	Database db;
	db.loadUsers();
	db.loadMovies();

	// Add default admin if not exists
	if (!db.authenticate("admin", "admin"))
		db.addUser(new Admin("admin", "admin"));

	User* currentUser = nullptr;
	int choice;

	std::cout << "=== Movie service ===";
	do 
	{
		std::cout << "\n1. Login\n";
		std::cout << "2. Register\n";
		std::cout << "3. Exit\n";
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == 1) 
		{
			std::string username, password;
			std::cout << "Username: ";
			std::cin >> username;
			std::cout << "Password: ";
			std::cin >> password;
			currentUser = db.authenticate(username, password);
			if (currentUser) 
			{
				currentUser->menu(db);
				currentUser = nullptr;
			} 
			else
				std::cout << "Invalid credentials.\n";
		} 
		else if (choice == 2) 
		{
			std::string username, password;
			std::cout << "Username: ";
			std::cin >> username;
			std::cout << "Password: ";
			std::cin >> password;
			// check for existing users
			db.addUser(new RegularUser(username, password));
			std::cout << "User registered.\n";
		}
	} while (choice != 3);

	return 0;
}
#include "Book.hpp"
#include "sqlite3.h"

int main()
{
	std::string tableCreationInstructions = "CREATE TABLE library (\
		ID INTEGER PRIMARY KEY AUTOINCREMENT,\
		name NOT NULL UNIQUE,\
		)";
	sqlite3 *db;
	char *ErrMsg;
	int returnValue;

	returnValue = sqlite3_open_v2("librarydb.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
	if (returnValue)
	{
		std::cerr << "Error creating and/or opening the database." << std::endl;
		return (1);
	}
	returnValue = sqlite3_exec(db, "DROP TABLE IF EXISTS library", 0, 0, &ErrMsg);
	returnValue = sqlite3_exec(db, tableCreationInstructions.c_str(), 0, 0, &ErrMsg);
	if (returnValue)
	{
		std::cerr << "There was an error creating the table: " << ErrMsg << std::endl;
		return (1);
	}
	
}

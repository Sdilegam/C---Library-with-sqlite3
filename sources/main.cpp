#include "Book.hpp"
#include "sqlite3.h"

int main()
{
	std::string tableCreationInstructions = "CREATE TABLE library (\
		ID INTEGER PRIMARY KEY AUTOINCREMENT,\
		name VARCHAR (200) NOT NULL UNIQUE,\
		date TEXT DEFAULT (2000-01-01-12-00-00.00),\
		total_pages INTEGER NOT NULL,\
		currrent_pages INTEGER,\
		note INTEGER,\
		finished BOOL DEFAULT (0),\
		synopsis TEXT\
		)";
	sqlite3 *db;
	char *errMsg;
	int returnValue;

	returnValue = sqlite3_open_v2("librarydb.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
	if (returnValue)
	{
		std::cerr << "Error creating and/or opening the database." << std::endl;
		return (1);
	}
	returnValue = sqlite3_exec(db, "DROP TABLE IF EXISTS library", 0, 0, &errMsg);
	returnValue = sqlite3_exec(db, tableCreationInstructions.c_str(), 0, 0, &errMsg);
	if (returnValue)
	{
		std::cerr << "There was an error creating the table: " << errMsg << std::endl;
		return (1);
	}
	Book book;
	book.input_pages();
}

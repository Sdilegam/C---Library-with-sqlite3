#include "Book.hpp"
#include "sqlite3.h"

void database_init (sqlite3 *database, const char *filename, int flags)
{
	char *errMsg;
	int returnValue;
	std::string tableCreationInstructions = "CREATE TABLE IF NOT EXISTS library (\
		ID INTEGER PRIMARY KEY AUTOINCREMENT,\
		name VARCHAR (200) NOT NULL UNIQUE,\
		date TEXT DEFAULT (2000-01-01-12-00-00.00),\
		total_pages INTEGER NOT NULL,\
		currrent_pages INTEGER,\
		note INTEGER,\
		finished BOOL DEFAULT (0),\
		synopsis TEXT)";
	returnValue = sqlite3_open_v2(filename, &database, flags, 0);
	if (returnValue)
	{
		std::cerr << "Error creating and/or opening the database." << std::endl;
		exit (1);
	}
	if (sqlite3_exec(database, "DROP TABLE IF EXISTS library", 0, 0, &errMsg))
	{
		std::cerr << "There was an error deleting the existing table: " << errMsg << std::endl;
		sqlite3_close(database);
		exit (1);
	}
	if (sqlite3_exec(database, tableCreationInstructions.c_str(), 0, 0, &errMsg))
	{
		std::cerr << "There was an error creating the table: " << errMsg << std::endl;
		sqlite3_close(database);
		exit (1);
	}

}

int main()
{
	sqlite3 *database;
	database_init(database, "librarydb.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	/*
	Check ctrl+z behaviour on windows when there's some input in the line /!2\
	*/
	std::string buffer;
	Book book;
	book.input_title();
	book.input_synopsis();
	book.input_pages();
	book.input_finished();
	book.input_note();

	book.print_info();
}

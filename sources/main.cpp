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

	std::cout << "Display test: " << std::endl;
	std::cout << "Title: " << book.get_title() << "\n";
	std::cout << "Synopsis: " << book.get_synopsis() << "\n";
	std::cout << "Pages: " << book.get_read_pages() << "/" << book.get_total_pages() << "\n";
	std::cout << "Finished: " << (book.get_finished() ? "yes":"no") << "\n";
	std::cout << "Note: " << book.get_note() / 20 << "/5\n";
}

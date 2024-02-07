#include "main.h"

void database_init (sqlite3 **database, const char *filename, int flags)
{
	char *errMsg;
	int returnValue;
	std::string tableCreationInstructions = "CREATE TABLE IF NOT EXISTS library (\
		ID INTEGER PRIMARY KEY AUTOINCREMENT,\
		name VARCHAR (200) NOT NULL UNIQUE,\
		date TEXT DEFAULT (2000-01-01-12-00-00.00),\
		total_pages INTEGER NOT NULL,\
		current_pages INTEGER,\
		note INTEGER,\
		finished BOOL DEFAULT (0),\
		synopsis TEXT)";
	returnValue = sqlite3_open_v2(filename, database, flags, 0);
	if (returnValue)
	{
		std::cerr << "Error creating and/or opening the database." << std::endl;
		exit (1);
	}
	// if (sqlite3_exec(*database, "DROP TABLE IF EXISTS library", 0, 0, &errMsg))
	// {
	// 	std::cerr << "There was an error deleting the existing table: " << errMsg << std::endl;
	// 	sqlite3_close(*database);
	// 	exit (1);
	// }
	returnValue = sqlite3_exec(*database, tableCreationInstructions.c_str(), 0, 0, &errMsg);
	if (returnValue)
	{
		std::cerr << returnValue << "There was an error creating the table: " << errMsg <<  std::endl;
		sqlite3_close(*database);
		exit (1);
	}

}

void	add_to_db(sqlite3 **db, Book &book)
{
	sqlite3_stmt	*statement;
	const char		*query = "INSERT OR REPLACE INTO library (name, date, total_pages, current_pages, note, finished, synopsis) VALUES (?, ?, ?, ?, ?, ?, ?);";

	sqlite3_prepare_v2(*db, query, -1, &statement, NULL);
	sqlite3_bind_text(statement, 1, book.get_title().c_str(), -1, 0);
	sqlite3_bind_text(statement, 2, "2024-02-07-04-14-00.00", -1, 0);
	sqlite3_bind_int(statement, 3, book.get_total_pages());
	sqlite3_bind_int(statement, 4, book.get_read_pages());
	sqlite3_bind_int(statement, 5, book.get_note());
	sqlite3_bind_int(statement, 6, book.get_finished());
	char *test book.get_synopsis().pointer;
	std::cout << "Test: " << test << std::endl;
	sqlite3_bind_text(statement, 7, test, book.get_synopsis().length() * sizeof(char), 0);
	sqlite3_step(statement);
	sqlite3_finalize(statement);
}
Book	retrieve_book(sqlite3 **db, const char *name)
{
	Book			result_book;
	sqlite3_stmt	*statement;
	const char		*query = "SELECT * from library WHERE name = ?;";

	sqlite3_prepare_v2(*db, query, -1, &statement, NULL);
	sqlite3_bind_text(statement, 1, name, -1, 0);
	int result = sqlite3_step(statement);
	if (result == SQLITE_ROW)
	{
		result_book.set_title((char *)sqlite3_column_text(statement, 1));
		result_book.set_total_pages(sqlite3_column_int(statement, 3));
		result_book.set_read_pages(sqlite3_column_int(statement, 4));
		result_book.set_note(sqlite3_column_int(statement, 5));
		result_book.set_finished(sqlite3_column_int(statement, 6));
		result_book.set_synopsis((char *)sqlite3_column_text(statement, 7));
		sqlite3_finalize(statement);
		return (result_book);
	}
	return (Book());
}


int main()
{
	sqlite3 *database;
	Book book;
	database_init(&database, "librarydb.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	/*
	Check ctrl+z behaviour on windows when there's some input in the line /!2\
	*/
	std::string buffer;
	// book.input_title();
	// book.input_synopsis();
	// book.input_pages();
	// book.input_finished();
	// book.input_note();
	book.set_title("title3");
	book.set_synopsis("Ceci est un synopsis tout a fait normal\n N'est ce pas ??\n\n\n THE END");
	book.set_total_pages(648);
	book.set_read_pages(173);
	book.set_finished(0);
	book.set_note(100);
	add_to_db(&database, book);
	book = retrieve_book(&database, "test1");
	if (book.get_title() == "")
		std::cout << "no book has been found :(" << std::endl;
	else
		book.print_info();
	book = retrieve_book(&database, "test2");
	if (book.get_title() == "")
		std::cout << "no book has been found :(" << std::endl;
	else
		book.print_info();
}

#include "main.h"

void	create_table(sqlite3 **database, const std::string &table_name, std::string_view instruction)
{
	int returnValue;
	char *errMsg;
	char *instruction_str;
	instruction_str = strdup(std::vformat(instruction, std::make_format_args(table_name)).c_str());
	// if (sqlite3_exec(*database, "DROP TABLE IF EXISTS library", 0, 0, &errMsg))
	// {
	// 	std::cerr << "There was an error deleting the existing table: " << errMsg << std::endl;
	// 	sqlite3_close(*database);
	// 	exit (1);
	// }
	returnValue = sqlite3_exec(*database, instruction_str, 0, 0, &errMsg);
	if (returnValue)
	{
		std::cerr << returnValue << "There was an error creating the table: " << table_name << ": " << errMsg <<  std::endl;
		sqlite3_close(*database);
		exit (1);
	}
}

void database_init (sqlite3 **database, const char *filename, int flags)
{
	char *errMsg;
	int returnValue;
	std::string bookshelf_creation_instructions = "CREATE TABLE IF NOT EXISTS {} (\
		ID INTEGER PRIMARY KEY AUTOINCREMENT,\
		name VARCHAR (200) NOT NULL,\
		date TEXT DEFAULT (2000-01-01-12-00-00.00),\
		total_pages INTEGER NOT NULL,\
		current_pages INTEGER,\
		note INTEGER,\
		finished BOOL DEFAULT (0),\
		synopsis TEXT\
		)";
	std::string author_list_creation_instructions = "CREATE TABLE IF NOT EXISTS {} (\
		ID INTEGER PRIMARY KEY AUTOINCREMENT,\
		name VARCHAR (200) NOT NULL UNIQUE)";
	std::string book_author_creation_instructions = "CREATE TABLE IF NOT EXISTS {} (\
		book_ID INTEGER NOT NULL,\
		author_ID INTEGER NOT NULL,\
		FOREIGN KEY (book_ID) REFERENCES bookshelf(ID) ON DELETE CASCADE,\
		FOREIGN KEY (author_ID) REFERENCES authors(ID) ON DELETE CASCADE\
		)";
	returnValue = sqlite3_open_v2(filename, database, flags, 0);
	if (returnValue)
	{
		std::cerr << "Error creating and/or opening the database." << std::endl;
		exit (1);
	}
	create_table(database, "bookshelf", bookshelf_creation_instructions);
	create_table(database, "authors", author_list_creation_instructions);
	create_table(database, "book_author_link", book_author_creation_instructions);
}

void	add_to_db(sqlite3 **db, Book &book)
{
	sqlite3_stmt	*statement;
	const char		*query = "INSERT OR REPLACE INTO library (name, date, total_pages, current_pages, note, finished, synopsis) VALUES (?, ?, ?, ?, ?, ?, ?);";
	// std::unique_ptr<char, decltype(std::free) *> synopsis = strdup(book.get_synopsis().c_str());

	sqlite3_prepare_v2(*db, query, -1, &statement, NULL);
	sqlite3_bind_text(statement, 1, book.get_title(), -1, 0);
	sqlite3_bind_text(statement, 2, "2024-02-07-04-14-00.00", -1, 0);
	sqlite3_bind_int(statement, 3, book.get_total_pages());
	sqlite3_bind_int(statement, 4, book.get_read_pages());
	sqlite3_bind_int(statement, 5, book.get_note());
	sqlite3_bind_int(statement, 6, book.get_finished());
	sqlite3_bind_text(statement, 7, book.get_synopsis(), -1, 0);
	sqlite3_step(statement);
	sqlite3_finalize(statement);
}

Book	retrieve_book(sqlite3 **db, const char *name)
{
	Book			result_book;
	sqlite3_stmt	*statement;
	const char		*query = "SELECT * from library WHERE name = ?;";
	char			*title;
	char			*synopsis;

	sqlite3_prepare_v2(*db, query, -1, &statement, NULL);
	sqlite3_bind_text(statement, 1, name, -1, 0);
	int result = sqlite3_step(statement);
	if (result == SQLITE_ROW)
	{
		title = (char *)sqlite3_column_text(statement, 1);
		result_book.set_title((char *)sqlite3_column_text(statement, 1));
		result_book.set_total_pages(sqlite3_column_int(statement, 3));
		result_book.set_read_pages(sqlite3_column_int(statement, 4));
		result_book.set_note(sqlite3_column_int(statement, 5));
		result_book.set_finished(sqlite3_column_int(statement, 6));
		synopsis = (char *)sqlite3_column_text(statement, 7);
		result_book.set_synopsis(synopsis);
		sqlite3_finalize(statement);
		return (result_book);
	}
	return (Book());
}

std::vector<std::string> get_booklist(sqlite3 **db)
{
	std::vector<std::string> list;
	sqlite3_stmt	*statement;
	const char		*query = "SELECT name from library";

	sqlite3_prepare_v2(*db, query, -1, &statement, NULL);
	while (sqlite3_step(statement) == SQLITE_ROW)
	{
		list.push_back((char *)sqlite3_column_text(statement, 0));
	}
	return (list);
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
	book.set_title((char *)"Ceci est le dernier");
	book.set_synopsis((char *)"Ceci est un synopsis tout a fait normal\n N'est ce pas ??\n\n\n THE END");
	book.set_total_pages(648);
	book.set_read_pages(173);
	book.set_finished(0);
	book.set_note(100);
	add_to_db(&database, book);
	std::vector<std::string> test = get_booklist(&database);
	for (std::string &i: test)
	{
		std::cout << i << std::endl;
	}
	
}

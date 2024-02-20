#include "Book.hpp"
#include "utils.h"

Book::Book(void): title(0), synopsis(0), read_pages(0), total_pages(0), is_finished(0), note(0)
{
}

Book::Book(char *init_title, char *init_synopsis, int init_read_pages, int init_total_pages, bool init_finished, int init_note): title(strdup(init_title)), synopsis(strdup(init_synopsis)), read_pages(init_read_pages), total_pages(init_total_pages), is_finished(init_finished), note(init_note)
{
}

Book::Book(char *init_title, char *init_synopsis): title(strdup(init_title)), synopsis(strdup(init_synopsis)), read_pages(0), total_pages(0), is_finished(0), note(0)
{
}

Book::Book(const Book &other): title(strdup(other.title)), synopsis(strdup(other.synopsis)), read_pages(other.read_pages), total_pages(other.get_total_pages()), is_finished(other.is_finished), note(other.note)
{
}

Book &Book::operator=(const Book &other)
{
	if (title)
		delete[] title;
	title = strdup(other.title);
	if (synopsis)
		delete[] synopsis;
	synopsis = strdup(other.synopsis);
	read_pages = other.read_pages;
	total_pages = other.total_pages;
	is_finished = other.is_finished;
	note = other.note;
	return (*this);
}

Book::~Book()
{
	if (title)
		delete[] title;
	if (synopsis)
		delete[] synopsis;
}

void Book::print_info() const
{
	std::cout << "Title is: " << title << ".\n";
	std::cout << "Synopsis is: \n"
			  << synopsis << "\n";
	std::cout << "Page: " << read_pages << "/" << total_pages << ".\n";
	std::cout << "The book is" << (is_finished ? " " : " not ") << "finished.\n";
	std::cout << "The note is " << note / 20 << "/5." << std::endl;
}

void Book::input_title(void)
{
	std::string input_buff = "";
	while (input_buff == "" || !std::cin)
	{
		std::cin.clear();
		std::cout << "Please write the title of the book" << std::endl;
		std::getline(std::cin, input_buff);
		std::cout << input_buff << std::endl;
		input_buff = trim_spaces(input_buff, " \n \t");
		if (input_buff.size() >= 200)
		{
			std::cout << "Title is too big! Please use less than 200 chars" << std::endl;
			input_buff = "";
		}
	}
	if (title)
		delete[] title;
	title = strdup(input_buff.c_str());
}

void Book::input_author(void)
{
	std::string input_buff = "";
	while (input_buff == "" || !std::cin)
	{
		std::cin.clear();
		std::cout << "Please write the author(s) name(s) of the book" << std::endl;
		std::getline(std::cin, input_buff);
		std::cout << input_buff << std::endl;
		input_buff = trim_spaces(input_buff, " \n \t");
		if (input_buff.size() >= 200)
		{
			std::cout << "author name is too big! Please use less than 200 chars" << std::endl;
			input_buff = "";
		}
	}
	if (author)
		delete[] author;
	author = strdup(input_buff.c_str());
}

void Book::input_synopsis(void)
{
	std::string input_buff = "";
	std::string synopsis_buff = "";
	while (synopsis_buff == "")
	{
		std::cout << "Please write the synopsis of the book (finish typing with EOF)" << std::endl;
		while (std::getline(std::cin, input_buff))
		{
			input_buff = trim_spaces(input_buff, " \n \t");
			synopsis_buff += input_buff + "\n";
		}
		if (!std::cin.eof() && std::cin.fail())
		{
			std::cerr << "Input of the book's synopsis failed." << std::endl;
		}
		std::cin.clear();
	}
	synopsis_buff.pop_back();
	if (synopsis)
		delete[] synopsis;
	synopsis = strdup(synopsis_buff.c_str());
}

void Book::input_pages(void)
{
	const char *input_msg = "Please input the number of pages this book has (positive integer): ";
	std::string input_buff = "";
	int number_buff = -1;
	while (number_buff <= 0)
	{
		std::cout << input_msg;
		std::cin >> number_buff;
		if (!std::cin.eof() && std::cin.peek() != '\n')
        {
			number_buff = -1;
			std::cin.clear();
            ignore_line();
            continue;
        }
	}
	if (!std::cin.eof() && std::cin.fail())
	{
		std::cerr << "Input of the book's pages failed." << std::endl;
		exit(1);
	}
	input_msg = "Please input the number of pages you have read from this book (positive integer): ";
	total_pages = number_buff;
	number_buff = -1;
	while (number_buff < 0 || number_buff > total_pages)
	{
		std::cout << input_msg;
		std::cin >> number_buff;
		if (!std::cin.eof() && std::cin.peek() != '\n')
        {
			number_buff = -1;
			std::cin.clear();
            ignore_line();
            continue;
        }
	}
	if (!std::cin.eof() && std::cin.fail())
	{
		std::cerr << "Input of the book's read pages failed." << std::endl;
		exit(1);
	}
	read_pages = number_buff;
}

void Book::input_finished(void)
{
	char toggle = 1;
	std::string input_buff = "";
	while (toggle)
	{
		reset_cin();
		std::cout << "Did you finish the book (Y/N)? ";
		std::getline(std::cin, input_buff);
		input_buff = trim_spaces(input_buff, " \n \t");
		if (input_buff == "Y" || input_buff == "yes" || input_buff == "y")
		{
			toggle = 0;
			is_finished = 1;
		}
		else if (input_buff == "N" || input_buff == "no" || input_buff == "n")
		{
			toggle = 0;
			is_finished = 0;
		}
		if (!std::cin)
			std::cin.clear();
	}
}

void Book::input_note(void)
{
	const char *note_message = "Please input the note out of 100 you would give to this book. (positive integer): ";
	std::string input_buff = "";
	int number_buff = -1;
	while (number_buff < 0 || number_buff > 100)
	{
		std::cout << note_message;
		std::cin >> number_buff;
		if (!std::cin.eof() && std::cin.peek() != '\n')
        {
			number_buff = -1;
			std::cin.clear();
            ignore_line();
            continue;
        }
	}
	if (!std::cin.eof() && std::cin.fail())
	{
		std::cerr << "Input of the book's note failed." << std::endl;
		exit(1);
	}
	note = number_buff;
}

void Book::set_title(char *str)
{
	if (title)
		delete[] title;
	title = strdup(str);
}

void Book::set_author(char *str)
{
	if (author)
		delete[] author;
	author = strdup(str);
}

void Book::set_synopsis(char *str)
{
	if (synopsis)
		delete[] synopsis;
	synopsis = strdup(str);
}

void Book::set_total_pages(int number)
{
	total_pages = number;
}
void Book::set_read_pages(int number)
{
	read_pages = number;
}

void Book::set_finished(bool input)
{
	is_finished = input;
}

void Book::set_note(short input_note)
{
	note = input_note;
}

const char	*Book::get_title(void) const
{
	return (title);
}

const char	*Book::get_author(void) const
{
	return (author);
}

const char	*Book::get_synopsis(void) const
{
	return (synopsis);
}

int	Book::get_total_pages(void) const
{
	return (total_pages);
}

int	Book::get_read_pages(void) const
{
	return (read_pages);
}

bool Book::get_finished(void) const
{
	return (is_finished);
}

short Book::get_note(void) const
{
	return (note);
}


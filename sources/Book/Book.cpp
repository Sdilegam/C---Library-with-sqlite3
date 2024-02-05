#include "Book.hpp"
#include "utils.h"

Book::Book(void)
{
	page_number = 0;
	finished = true;
	read_page = 0;
	note = 0;
}

Book::Book(std::string &init_title, bool is_finished) : title(init_title), finished(is_finished)
{
	page_number = 0;
	read_page = 0;
	note = 0;
}

Book::Book(Book &other) : title(other.title), synopsis(other.synopsis), page_number(other.page_number), finished(other.finished), read_page(other.read_page), note(other.note)
{
}

Book &Book::operator=(Book &other)
{
	title = other.title;
	synopsis = other.synopsis;
	page_number = other.page_number;
	finished = other.finished;
	read_page = other.read_page;
	note = other.note;
}

Book::~Book()
{
}

void Book::print_info() const
{
	std::cout << "Title is: " << title << ".\n";
	std::cout << "Synopsis is: \n"
			  << synopsis << "\n";
	std::cout << "Page: " << read_page << "/" << page_number << ".\n";
	std::cout << "The book is" << (finished ? " " : " not ") << "finished.\n";
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
	title = input_buff;
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
	synopsis = synopsis_buff;
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
	page_number = number_buff;
	number_buff = -1;
	while (number_buff < 0 || number_buff > page_number)
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
	read_page = number_buff;
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
			finished = 1;
		}
		else if (input_buff == "N" || input_buff == "no" || input_buff == "n")
		{
			toggle = 0;
			finished = 0;
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

void Book::set_title(std::string str)
{
	title = str;
}

void Book::set_synopsis(std::string str)
{
	synopsis = str;
}

void Book::set_total_pages(int number)
{
	page_number = number;
}
void Book::set_read_pages(int number)
{
	read_page = number;
}

void Book::set_finished(bool input)
{
	finished = input;
}

void Book::set_note(short input_note)
{
	note = input_note;
}

std::string Book::get_title(void) const
{
	return (title);
}

std::string	Book::get_synopsis(void) const
{
	return (synopsis);
}

int	Book::get_total_pages(void) const
{
	return (page_number);
}

int	Book::get_read_pages(void) const
{
	return (read_page);
}

bool Book::get_finished(void) const
{
	return (finished);
}

short Book::get_note(void) const
{
	return (note);
}


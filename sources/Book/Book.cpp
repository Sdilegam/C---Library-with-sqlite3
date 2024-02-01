#include "Book.hpp"

Book::Book(void)
{
	page_number = 0;
	finished = true;
	current_page = 0;
	note = 0;
}

Book::Book(std::string &init_title, bool is_finished): title(init_title), finished(is_finished)
{
	page_number = 0;
	current_page = 0;
	note = 0;
}

Book::Book(Book &other): title(other.title), synopsis(other.synopsis), page_number(other.page_number), finished(other.finished), current_page(other.current_page), note(other.note)
{
}

Book &Book::operator=(Book &other)
{
	title = other.title;
	synopsis = other.synopsis;
	page_number = other.page_number;
	finished = other.finished;
	current_page = other.current_page;
	note = other.note;
}

Book::~Book()
{

}

void	Book::get_info() const
{
	std::cout << "Title is: " << title << ".\n";
	std::cout << "Synopsis is: \n" << synopsis << "\n";
	std::cout << "Page: " << current_page << "/"  << page_number << ".\n";
	std::cout << "The book is" << (finished ? " " : " not ") << "finished.\n";
	std::cout << "The note is " << note / 20 << "/5." << std::endl;
}

void	Book::set_info()
{
	std::string	str_buff;
	unsigned	unsigned_buff;

		std::cout << "Please write the title of the book" << std::endl;
		std::getline (std::cin, str_buff);
		if (str_buff != "")
			title = str_buff;
		str_buff.clear();
		std::cin.clear();
		std::cout << "Please write the synopsis of the book" << std::endl;
		std::getline (std::cin, str_buff);
		if (str_buff != "")
			synopsis = str_buff;
		str_buff.clear();
		std::cin.clear();
		std::cout << "How many pages does the book have ?" << std::endl;
		std::cin >> unsigned_buff;
		if (unsigned_buff != 0)
			page_number = unsigned_buff;
		std::cout << "Have you finished this book ?" << std::endl;
		std::cin >> unsigned_buff;
		std::cin.clear();
		if (unsigned_buff != 0)
		{
			finished = unsigned_buff;
			current_page = page_number;
		}
		else 
		{
			std::cout << "At which page are you ?" << std::endl;
			std::cin >> unsigned_buff;
			std::cin.clear();
			current_page = unsigned_buff;
		}
		unsigned_buff = 101;
		while (unsigned_buff > 100)
		{
			std::cout << "Please give it a note out of 100" << std::endl;
			std::cin >> unsigned_buff;
			std::cin.clear();
		}
		note = unsigned_buff;
}


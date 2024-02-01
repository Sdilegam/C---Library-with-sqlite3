#ifndef BOOK_CPP
# define BOOK_CPP
# include <string>
# include <iostream>

class Book
{
private:
	std::string	title;
	std::string	synopsis;
	unsigned	page_number;
	bool		finished;
	unsigned	current_page;
	short		note;
public :
	Book(void);
	Book(std::string &, bool);
	Book(Book &other);
	Book &operator=(Book &other);
	~Book();
	void	get_info(void) const;
	void	set_info(void);
};

#endif

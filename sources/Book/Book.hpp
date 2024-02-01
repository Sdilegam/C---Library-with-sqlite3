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
	void	input_title(void);
	void	input_synopsis(void);
	void	input_pages(void);
	/*
	void	input_finished(void);
	void	input_note(void);
	void	set_title(void);
	void	set_synopsis(void);
	void	set_pages(void);
	void	set_finished(void);
	void	set_note(void);
	void	get_title(void);
	void	get_synopsis(void);
	void	get_pages(void);
	void	get_finished(void);
	void	get_note(void);*/
};

#endif

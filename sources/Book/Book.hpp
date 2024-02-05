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
	unsigned	read_page;
	short		note;
public :
	Book(void);
	Book(std::string &, bool);
	Book(Book &other);
	Book &operator=(Book &other);
	~Book();
	void		get_info(void) const;
	void		input_title(void);
	void		input_synopsis(void);
	void		input_pages(void);
	void		input_finished(void);
	void		input_note(void);
	void		set_title(std::string);
	void		set_synopsis(std::string);
	void		set_total_pages(int);
	void		set_read_pages(int);
	void		set_finished(bool);
	void		set_note(short);
	std::string	get_title(void) const;
	std::string	get_synopsis(void) const;
	int			get_total_pages(void) const;
	int			get_read_pages(void) const;
	bool		get_finished(void) const;
	short		get_note(void) const;
};

#endif

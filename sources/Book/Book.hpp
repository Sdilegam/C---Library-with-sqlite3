#ifndef BOOK_CPP
# define BOOK_CPP
# include <string>
# include <string.h>
# include <iostream>

class Book
{
private:
	char		*title;
	char		*author;
	char		*synopsis;
	unsigned	read_pages;
	unsigned	total_pages;
	bool		is_finished;
	short		note;
public :
	Book(void);
	Book(char *init_title, char *init_synopsis, int init_read_pages, int init_total_pages, bool init_finished, int init_note);
	Book(char *init_title, char *init_synopsis);
	Book(const Book &other);
	Book &operator=(const Book &other);
	~Book();
	void	print_info(void) const;
	void	input_title(void);
	void	input_author(void);
	void	input_synopsis(void);
	void	input_pages(void);
	void	input_finished(void);
	void	input_note(void);
	void	set_title(char *str);
	void	set_author(char *str);
	void	set_synopsis(char *str);
	void	set_total_pages(int);
	void	set_read_pages(int);
	void	set_finished(bool);
	void	set_note(short);
	const char	*get_title(void) const;
	const char	*get_author(void) const;
	const char	*get_synopsis(void) const;
	int		get_total_pages(void) const;
	int		get_read_pages(void) const;
	bool	get_finished(void) const;
	short	get_note(void) const;
};

#endif

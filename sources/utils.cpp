#include "utils.h"

std::string	trim_spaces(std::string &input, const char *trimed_char)
{
	size_t	first_correct_char;
	size_t	last_correct_char;
	size_t	range;


	first_correct_char = input.find_first_not_of(trimed_char);
	if (first_correct_char == input.npos)
		return ("");
	last_correct_char = input.find_last_not_of(trimed_char);
	range = last_correct_char - first_correct_char + 1;
	return (input.substr(first_correct_char, range));
}

void ignore_line(void)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void reset_cin(void)
{
	std::cin.clear();
	ignore_line();
}

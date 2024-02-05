#if !defined(UTILS_H)
# define UTILS_H
# include <string>
# include <iostream>
# include <limits>

std::string	trim_spaces(std::string &input, const char *trimed_char);

void ignore_line(void);

void reset_cin(void);
#endif // UTILS_H

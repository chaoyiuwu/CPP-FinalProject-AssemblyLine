//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 14th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities
{
	size_t m_widthField = 1;
	static char m_delimiter;

public:
	void setFieldWidth(size_t);
	size_t getFieldWidth() const;
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char);
	const char getDelimiter() const;
};

#endif
//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 14th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include <algorithm>
#include "Utilities.h"

char Utilities::m_delimiter;

void Utilities::setDelimiter(const char c) {
	m_delimiter = c;
}

const char Utilities::getDelimiter() const {
	return m_delimiter;
}

void Utilities::setFieldWidth(size_t wf) {
	m_widthField = wf;
}

size_t Utilities::getFieldWidth() const {
	return m_widthField;
}

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	
	if(str.at(next_pos) == m_delimiter){
		throw std::string("Two Delimiters With No Token Between Them");
	}
	std::string token = str.substr(next_pos);
	auto dIndex = token.find(m_delimiter);

	if (token.find(m_delimiter) == std::string::npos) {
		next_pos = -1;
		more = false;
	}
	else {
		next_pos = str.find(token.substr(dIndex+1));
		more = true;
		token = token.substr(0, dIndex);
	}

	m_widthField = std::max(m_widthField, token.length());
	return token;

}
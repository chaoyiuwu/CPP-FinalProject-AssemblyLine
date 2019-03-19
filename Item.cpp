//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 14th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Item.h"
#include "Utilities.h"

size_t Item::m_widthField = 0;

Item::Item(const std::string& record) {
	Utilities utility;
	size_t next_pos = 0;
	bool more = true;
	
	m_name = utility.extractToken(record, next_pos, more);
	
	std::stringstream ss(utility.extractToken(record, next_pos, more));
	ss >> m_serialNumber;
	ss = std::stringstream(utility.extractToken(record, next_pos, more));
	ss >> m_quantity;
	
	m_widthField = std::max(m_widthField, utility.getFieldWidth());

	m_description = utility.extractToken(record, next_pos, more);

	
}

const std::string& Item::getName() const {
	return m_name;
}

const unsigned int Item::getSerialNumber() {
	return m_serialNumber++;
}

const unsigned int Item::getQuantity() {
	return m_quantity;
}

void Item::updateQuantity(){
	m_quantity = m_quantity - 1 < 0 ? 0 : m_quantity - 1;
}

void Item::display(std::ostream& os, bool full) const {
	os << std::left << std::setw(m_widthField) << m_name;
	os << " [" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << "]";
	os << std::setfill(' ');
	if (full) {
		os << std::left << " Quantity: " << std::setw(m_widthField) << m_quantity << " Description: " << m_description;
	}
	os << std::endl;
}
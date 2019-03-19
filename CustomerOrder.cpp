//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 29th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include <algorithm>
#include <vector>
#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 1;

CustomerOrder::CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& record) {
	Utilities utility;
	size_t next_pos = 0;
	bool more = true;

	m_name = utility.extractToken(record, next_pos, more); // customer name
	m_product = utility.extractToken(record, next_pos, more); // order name

	// list of items making up the order
	std::vector<std::string> items;
	while (more) {
		items.push_back(utility.extractToken(record, next_pos, more));
	}
	
	m_widthField = std::max(m_widthField, utility.getFieldWidth()); // update CustomerOrder::m_widthField

	m_cntItem = items.size();

	m_lstItem = new ItemInfo*[m_cntItem];

	for (size_t i = 0; i < m_cntItem; i++) {
		m_lstItem[i] = new ItemInfo(items[i]);
	}
}

CustomerOrder::~CustomerOrder() {

	for (size_t i = 0; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}

	delete[] m_lstItem;
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
	m_lstItem = nullptr;
	m_cntItem = 0;
	*this = std::move(other);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) {
	if (this != &other) {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;

		m_name = other.m_name;
		m_product = other.m_product;
		m_cntItem = other.m_cntItem;
		m_lstItem = other.m_lstItem;

		other.m_cntItem = 0;
		other.m_lstItem = nullptr;
	}

	return *this;
}

bool CustomerOrder::getItemFillState(std::string item) const {
	bool state = true;

	for (size_t i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == item) {
			state = m_lstItem[i]->m_fillState;
			break;
		}
	}

	return state;
}

bool CustomerOrder::getOrderFillState() const {
	bool state = true;

	for (size_t i = 0; i < m_cntItem; i++) {
		if (!m_lstItem[i]->m_fillState) {
			state = false;
		}
	}

	return state;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {

	// if item cannot be found in the current order
	for (size_t i = 0; i < m_cntItem; i++) {

		if (m_lstItem[i]->m_itemName == item.getName()) {
			
			if (item.getQuantity() > 0) {
				item.updateQuantity(); // update inventory
				m_lstItem[i]->m_serialNumber = item.getSerialNumber(); // update ItemInfo::m_serialNumber
				m_lstItem[i]->m_fillState = true; // update ItemInfo::m_fillState
				os << "Filled ";
			}
			// inventory is empty
			else {
				os << "Unable to fill ";
			}
			os << m_name << ", ";
			os << m_product;
			os << "[" << item.getName() << "]" << std::endl;
		
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++) {
		
		os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] ";
		os << std::setw(m_widthField) << std::setfill(' ') << std:: left << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_fillState) {
			os << "FILLED";
		}
		else {
			os << "MISSING";
		}
		os << std::endl;
 	}
}
//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 25th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include "Item.h"
#include <string>

struct ItemInfo {
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;
public:
	CustomerOrder();

	CustomerOrder(std::string&);

	CustomerOrder(const CustomerOrder&) { throw std::string("Copy constructor prohibited!"); };
	CustomerOrder& operator=(const CustomerOrder&) = delete;

	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&);

	~CustomerOrder();

	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream&);
	void display(std::ostream&) const;
};

#endif
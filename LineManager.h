//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 29th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <string>
#include <deque>
#include "CustomerOrder.h"
#include "Task.h"

class LineManager
{
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;

public:
	LineManager(std::string, std::vector<Task*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};

#endif
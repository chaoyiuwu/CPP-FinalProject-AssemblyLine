//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 29th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include <iostream>
#include "Task.h"

Task::Task(const std::string& record) : Item(record){
	m_pNextTask = nullptr;
}

void Task::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		
		if (!m_orders.back().getItemFillState(Item::getName())) {
			m_orders.back().fillItem(*this, os);
		}
	}
}

bool Task::moveTask() {

	if (!m_orders.empty()) {
		if (m_orders.back().getItemFillState(Item::getName())) {
			// moves the last CustomerOrder in the queue to the next task
			if (m_pNextTask != nullptr) {
				*m_pNextTask += (std::move(m_orders.back()));
				m_orders.pop_back();
			}
			else {
				return true;
			}
		}
	}

	return false;
}

void Task::setNextTask(Task& task) {
	m_pNextTask = &task;
}

bool Task::getCompleted(CustomerOrder& co) {
	bool result = false;

	if (!m_orders.empty()) {
		co = std::move(m_orders.back());
		m_orders.pop_back();
		result = true;
	}

	return result;
}

void Task::validate(std::ostream& os) {
	os << Item::getName();
	if (m_pNextTask != nullptr) {
		os << " --> " << m_pNextTask->getName();
	}
	else {
		os << " --> END OF LINE";
	}
	os << std::endl;
}

Task& Task::operator+=(CustomerOrder&& co) {
	m_orders.push_front(std::move(co));
	return *this;
}
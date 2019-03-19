//Name: Chaoyi Wu
// Seneca Student ID: 154330179
// Seneca email: cwu79@myseneca.ca
// Date of completion: Nov. 29th
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include <fstream>
#include <iostream>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(std::string filename, std::vector<Task*>& allTasks, std::vector<CustomerOrder>& allOrders) {
	std::ifstream f (filename);
	Utilities utility;
	utility.setDelimiter('|');
	while (f.good()) {
		bool more = true;
		size_t nextPos = 0;

		std::string line;
		std::getline(f, line);

		std::string token1 = utility.extractToken(line, nextPos, more);
		if (more) {
			std::string token2 = utility.extractToken(line, nextPos, more);
			for (size_t i = 0; i < allTasks.size(); i++) {
				if (allTasks[i]->getName() == token1) {
					for (size_t j = 0; j < allTasks.size(); j++) {
						if (allTasks[j]->getName() == token2) {
							allTasks[i]->setNextTask(*allTasks[j]);
							break;
						}
					}
				}
			}
		}
	}

	for (size_t i = 0; i < allOrders.size(); i++) {
		ToBeFilled.push_front(std::move(allOrders[i]));
	}
	m_cntCustomerOrder = ToBeFilled.size();
	for (size_t i = 0; i < allTasks.size(); i++) {
		AssemblyLine.push_back(allTasks[i]);
	}

}

bool LineManager::run(std::ostream& os) {

	if (!ToBeFilled.empty()) {
		// beginning of AssemblyLine (PowerSupply)
		*AssemblyLine[4] += std::move(ToBeFilled.back());
		ToBeFilled.pop_back();
	}

	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		if (AssemblyLine[i]->moveTask()) {
			
			CustomerOrder temp;
			AssemblyLine[i]->getCompleted(temp);
			Completed.push_front(std::move(temp));
		}
		
	}

	return m_cntCustomerOrder == Completed.size();
}

void LineManager::displayCompleted(std::ostream& os) const {
	for (int i = Completed.size()-1; i >= 0; i--) {
		Completed[i].display(os);
	}
}

void LineManager::validateTasks() const {
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->validate(std::cout);
	}
}
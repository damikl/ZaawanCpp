#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <string>
#include "todos.hpp"

class DataManager
{
public:
	DataManager();
	bool loadFile(std::string name);
private:
	std::string name;
	std::string passcode;
	Todos todo_list;
	
};

#endif

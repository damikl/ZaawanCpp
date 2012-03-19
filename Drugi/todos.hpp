#ifndef TODOS_H
#define TODOS_H

#include <list>
#include "task.hpp"

class Todos
{
public:
	Todos();
	void addTask(Task);
	Task getTask(int id) const;
	void removeTask(int id);
	void getTaskList() const;
	int length() const;
private:
	typedef std::list<Task> TasksGroup;
	TasksGroup tasks;
};

#endif

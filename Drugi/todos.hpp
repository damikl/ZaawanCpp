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
	bool existTask(int id) const;
	void removeTask(int id);
	void getTaskList() const;
	int nextId() const;
	int size() const;
	
	typedef std::list<Task>::iterator iterator;
	typedef std::list<Task>::const_iterator const_iterator;
	iterator begin() { return tasks.begin(); }
	iterator end() { return tasks.end(); }
	const_iterator begin() const { return tasks.begin(); }
	const_iterator end() const { return tasks.end(); }
	iterator find(int id);
	const_iterator find(int id) const;
	
private:
	
	typedef std::list<Task> TasksGroup;
	TasksGroup tasks;
};

#endif

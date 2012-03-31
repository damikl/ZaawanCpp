#ifndef TODOS_H
#define TODOS_H

#include <list>
#include "task.hpp"

bool compareByTime (const Task& t1, const Task& t2 );

bool compareById (const Task& t1, const Task& t2 );

bool equalById (const Task& t1, const Task& t2 );

class Todos
{
public:
	Todos();
	bool addTask(const Task& task);
	Task getTask(int id) const;
	bool existTask(int id) const;
	void removeTask(int id);
	void getTaskList() const;
	int nextId() const;
	int size() const;
	
	template<class Compare>
	void sort(Compare comp) { tasks.sort(comp); }
	
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

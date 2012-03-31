#include <iostream>
#include <algorithm>
#include "todos.hpp"
using namespace std;

struct TaskPrinter {
  void operator() (const Task& i) const { i.print();}
} task_printer;

struct TaskChecker {
	int id;
	bool operator()(const Task& task) const {
			return task.getId() == id;
		}
};

bool compareByTime (const Task& t1, const Task& t2 ) {
	return t1.timeOrder(t2);
}

bool compareById (const Task& t1, const Task& t2 ) {
	return t1.getId() < t2.getId();
}

bool equalById (const Task& t1, const Task& t2 ) {
	return t1.getId() == t2.getId();
}

Todos::Todos() 
{
	tasks = list<Task>();
}
	
list<Task>::const_iterator Todos::find(int id) const
{
	TasksGroup::const_iterator it;
	TaskChecker checker;
	checker.id = id;
	it = find_if(tasks.begin(),tasks.end(),checker);
	return it;
}

list<Task>::iterator Todos::find(int id)
{
	TasksGroup::iterator it;
	TaskChecker checker;
	checker.id = id;
	it = find_if(tasks.begin(),tasks.end(),checker);
	return it;
}

bool Todos::existTask(int id) const
{
	return !tasks.empty() && find(id) != tasks.end();	
}

Task Todos::getTask(int id) const {
	TasksGroup::const_iterator it = find(id);
	if(it != end())
		return *it;
	
	return Task(-1,"");
}

void Todos::removeTask(int id) {
		TaskChecker checker;
		checker.id = id;
		tasks.remove_if(checker);
	}

bool Todos::addTask(const Task& task){
		if(existTask(task.getId()))
			return false;
		tasks.push_front(task);
		return true;
	}

int Todos::nextId() const
{
	int result = 1;
	
	do{
		result = (result*rand()) % (7*size() + 1);
	}while( existTask(result) );
	return result;
	
}

void Todos::getTaskList() const {
	//	tasks.sort(compareByTime);
		for_each (tasks.begin(), tasks.end(), task_printer);
	}
int Todos::size() const {
		return tasks.size();
	}



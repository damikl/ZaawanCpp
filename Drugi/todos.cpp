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

bool compareByTime (Task t1, Task t2 ) {
	return t1.timeOrder(t2);
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
	return find_if(tasks.begin(),tasks.end(),checker);	
}

list<Task>::iterator Todos::find(int id)
{
	TasksGroup::iterator it;
	TaskChecker checker;
	checker.id = id;
	return find_if(tasks.begin(),tasks.end(),checker);	
}

bool Todos::existTask(int id) const
{
	return !tasks.empty() && find(id) != tasks.end();	
}

Task Todos::getTask(int id) const {
	
	return *find(id);
}

void Todos::removeTask(int id) {
		TaskChecker checker;
		checker.id = id;
		tasks.remove_if(checker);
	}

void Todos::addTask(Task task){
		tasks.push_front(task);
	}

int Todos::nextId() const
{
	int result = 1;
	
	do{
		result = (result*rand()) % (7*size() + 1);
	}while( existTask(result) );
	
}

void Todos::getTaskList() const {
	//	tasks.sort(compareByTime);
		for_each (tasks.begin(), tasks.end(), task_printer);
	}
int Todos::size() const {
		return tasks.size();
	}



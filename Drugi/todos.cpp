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

Todos::Todos() {
		tasks = list<Task>();
	}

Task Todos::getTask(int id) const {
	TasksGroup::const_iterator it;
	TaskChecker checker;
	checker.id = id;
	it = find_if(tasks.begin(),tasks.end(),checker);
	return *it;
}

void Todos::removeTask(int id) {
		TaskChecker checker;
		checker.id = id;
		tasks.remove_if(checker);
	}

void Todos::addTask(Task task){
		tasks.push_front(task);
	}
	
void Todos::getTaskList() const {
		for_each (tasks.begin(), tasks.end(), task_printer);
	}
int Todos::length() const {
		return tasks.size();
	}
	
int main(int argc, char** argv)
{
	Todos todolist;
	Task t = Task(2,string("Wycieczka"),string("Wycieczka w bieszczady"),string("Higth"),string("Serious"));
	t.setDate(2,7,2000);
	t.setTime(14,12);
	t.getTime();
	todolist.addTask(t);
	t.setTime(16,2);
	todolist.getTaskList();
	
	Task t2 = Task::convert( t.convert() );
	
	cout << t2.getTime() << endl;
	todolist.addTask( t2 );
	todolist.getTaskList();
	
}

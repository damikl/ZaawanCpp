#ifndef TASK_H
#define TASK_H
#include <string>
#include <ctime>

class Task
{
public:
	typedef std::string string;
	Task(	int id, string title, 
					string description,
					string priority, 
					string severity
		);
	
	void print() const;
	int getId() const;
	std::string getTitle() const;
	bool operator ==(const Task& b) const;
	bool timeOrder(const Task& task) const;
	string getTime() const;
	bool setDate(int day, int month, int year);
	bool setTime(int hour = 0, int minutes = 0, int seconds = 0);
	static Task convert(const string& printedtask);
	string convert() const;
	
private:
	Task(){}
	int id;
	string title;
	string description;
	struct tm timeinfo;
	string priority;
	string severity;
	
};

#endif

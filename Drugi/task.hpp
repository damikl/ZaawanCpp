#ifndef TASK_H
#define TASK_H
#include <string>
#include <ctime>

class Task
{
public:
	typedef std::string string;
	Task(	int id, string title, 
					string description = "",
					string priority = "", 
					string severity = ""
		);
	
	void print() const;
	int getId() const;
	std::string getTitle() const;
	string getTime() const;
	string getPriority() const {return priority;}
	string getSeverity() const {return severity;}
	string getDescription() const {return description;}
	
	void setTitle(string title);
	bool setDate(int day, int month, int year);
	bool setTime(int hour = 0, int minutes = 0, int seconds = 0);
	void setDescription(string description );
	void setPriority(string priority);
	void setSeverity(string severity);
	
	bool operator ==(const Task& b) const;
	
	//sorting 
	bool timeOrder(const Task& task) const;
	
	//conversion
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

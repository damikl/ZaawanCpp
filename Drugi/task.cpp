#include "task.hpp"
#include <iostream>
#include <sstream>
#include <memory.h>
#include <list>

using namespace std;

Task::Task(	int id, string title, 
					string desc,
					string priority, 
					string severity) : 	id(id),
										title(title), 
										description(desc),
										priority(priority), 
										severity(severity) 
{	 
		time_t ltime=time(NULL);
		timeinfo=*localtime(&ltime);
	}

Task Task::convert(const string& printedtask) {
		enum Elem {ID, TITLE, DESC,PRIORITY,SEVERITY,DATETIME};
		string buf;
		stringstream ss(printedtask);
		
		Elem el;
		Task result;
		while (ss >> buf)
		{
			if(buf == "id:")
			{
				el = ID;
				continue;
			}
			if(buf == "title:")
			{
				el = TITLE;
				continue;	
			}
			if(buf == "priority:")
			{
				el = PRIORITY;
				continue;	
			}
			if(buf == "severity:")
			{
				el = SEVERITY;
				continue;	
			}
			if(buf == "desc:")
			{
				el = DESC;
				continue;	
			}
			if(buf == "dt:")
			{
				el = DATETIME;
				continue;	
			}
			
			switch(el)
			{
				case ID:
				{
					stringstream tmp(buf);
					tmp >> result.id;
					break;
				}
				case TITLE:
				{
					if(!result.title.empty())
						result.title += " ";
					result.title = buf;
					break;
				}
				case PRIORITY:
				{
					result.priority = buf;
					break;
				}
				case SEVERITY:
				{
					result.severity = buf;
					break;
				}
				case DESC:
				{
					if(!result.description.empty())
						result.description += " ";
					result.description += buf;
					break;
				}
				case DATETIME:
				{
					stringstream tmp(buf);
					tmp >> result.timeinfo.tm_mday;
					ss >> result.timeinfo.tm_mon;
					ss >> result.timeinfo.tm_year;
					ss >> result.timeinfo.tm_hour;
					ss >> result.timeinfo.tm_min;
					ss >> result.timeinfo.tm_sec;
					break;
				}
			}
		}
			
		return result;
		
	}
string Task::convert() const {
		stringstream result;
		result << "id: " << id << endl;
		result << "title: " << title << endl;
		result << "priority: " << priority << endl;
		result << "severity: " << severity << endl;
		result << "desc: " << description << endl;
		result << "dt: " << 	timeinfo.tm_mday << " " << 
							timeinfo.tm_mon << " "<< 
							timeinfo.tm_year << " "<< 
							timeinfo.tm_hour << " "<<
							timeinfo.tm_min << " "<<
							timeinfo.tm_sec << endl;
		return result.str();
	
	}

string Task::getTitle() const {
		return title;
	}
void Task::print() const {
		cout << id << ": " << title + " " << priority << " " << severity << " " << getTime() << " " << description << endl;
	}
	
bool Task::timeOrder(const Task& task) const {
		struct tm me_tm = timeinfo;
		struct tm other_tm = task.timeinfo;
		
		time_t me = mktime(&me_tm);
		time_t other = mktime(&other_tm);
		
		double dif = difftime (me,other);
		
		return dif >= 0;
	}
bool Task::setDate(int day, int month, int year ) {
		if(day > 31 || day < 1 || month > 12 || month < 1)
		{
			cout << "odrzucono1" << endl;
			return false;
		}
		struct tm tmp;
		memset(&tmp, 0, sizeof(tmp));
		tmp.tm_year = year - 1900;
		tmp.tm_mon = month - 1;
		tmp.tm_mday = day;
		
		if(mktime(&tmp) < 0) {
				cout << "odrzucono2" << endl;
				return false;
			}
		timeinfo = tmp;
		return true;
	}
bool Task::setTime(int hour, int minutes, int seconds) {
		if(	hour > 23 || hour < 0 || 
					minutes > 59 || minutes < 0 || 
					seconds > 59 || seconds < 0)
		{	return false;	}
		
		timeinfo.tm_hour = hour;
		timeinfo.tm_min = minutes;
		timeinfo.tm_sec = seconds;
		
		return true;
	}
	
string Task::getTime() const {
		return string( asctime(&timeinfo) );
	}
	
int Task::getId() const {
		return id;
	}

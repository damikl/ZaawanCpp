#include "task.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory.h>
#include <list>

using namespace std;

string trim(const string& str)
{
	string buf, result;
	stringstream tmp(str);
	while(tmp >> buf)
	{
		if(!result.empty())
		{
			result += " ";
		}
		result += buf;
	}
	return result;
}

Task::Task(	int id, string title, 
					string desc,
					string priority, 
					string severity) : 	id(id),
										title(trim(title)), 
										description(trim(desc)),
										priority(trim(priority)), 
										severity(trim(severity)) 
{	 
		time_t ltime=time(NULL);
		timeinfo=*localtime(&ltime);
	}


Task Task::convert(const string& printedtask) {
		enum Elem {ID, TITLE, DESC,PRIORITY,SEVERITY,DATETIME};
		string buf;
		stringstream ss(printedtask);
		bool prevready = true;
		Elem el;
		Task result;
		while (ss >> buf)
		{
			if(prevready)
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
			}
			int length;
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
					if(result.title.empty()  && prevready)
					{
						stringstream tmp(buf);
						tmp >> length;
						if(length > 0)
							prevready = false;
						break;
					}
					else
					{
						result.title += " ";
					}
					result.title = buf;
					if(length >= result.title.size())
						prevready = true;
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
					if(result.description.empty() && prevready)
					{
						stringstream tmp(buf);
						tmp >> length;
						if(length > 0)
							prevready = false;
						break;
					}
					else
					if(!result.description.empty())
					{
						result.description += " ";
					}
					result.description += buf;
					if(length >= result.description.size())
						prevready = true;
					break;
				}
				case DATETIME:
				{
					stringstream tmp(buf);
					memset(&result.timeinfo, 0, sizeof(result.timeinfo));
					tmp >> result.timeinfo.tm_mday;
					ss >> result.timeinfo.tm_mon;
					ss >> result.timeinfo.tm_year;
					ss >> result.timeinfo.tm_hour;
					--result.timeinfo.tm_hour;
					ss >> result.timeinfo.tm_min;
					ss >> result.timeinfo.tm_sec;
					mktime(&(result.timeinfo));
					break;
				}
			}
		}
			
		return result;
		
	}
string Task::convert() const {
		stringstream result;
		result << "id: " << id << endl;
		result << "title: " << title.size() << " " << title << endl;
		result << "priority: " << priority << endl;
		result << "desc: " << description.size() << " " << description << endl;
		result << "severity: " << severity << endl;
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
		stringstream ss;
		ss << day << " " << month << " " << year << endl;
		throw invalid_argument(ss.str());
		return false;
	}
	struct tm tmp;
	memset(&tmp, 0, sizeof(tmp));
	tmp.tm_year = year - 1900;
	tmp.tm_mon = month - 1;
	tmp.tm_mday = day;
	
	tmp.tm_hour = timeinfo.tm_hour - 1;
	tmp.tm_min = timeinfo.tm_min;
	tmp.tm_sec = timeinfo.tm_sec;
	
	if(mktime(&tmp) < 0) {
		stringstream ss;
		ss << day << " " << month << " " << year << endl;
		throw invalid_argument("mktime() failed to accept: " + ss.str());
		return false;
	}
	if(tmp.tm_mday != day)
	{
		stringstream ss;
		ss << tmp.tm_mday << " " << tmp.tm_mon+1 << " " << tmp.tm_year +1900 << endl;
		throw invalid_argument("day shifted to: " + ss.str());
		return false;
	}

	timeinfo = tmp;
	return true;
}

bool Task::setTime(int hour, int minutes, int seconds) 
{
	if(	hour > 23 || hour < 0 || 
				minutes > 59 || minutes < 0 || 
				seconds > 59 || seconds < 0)
	{
		stringstream ss;
		ss << hour << " " << minutes << " " << seconds << endl;
		throw invalid_argument("invalid time: " + ss.str());
		return false;	
	}
	
	timeinfo.tm_hour = hour;
	timeinfo.tm_min = minutes;
	timeinfo.tm_sec = seconds;
	
	return true;
}

void Task::setTitle(string title)
{
	this->title = trim(title);
}

void Task::setDescription(string description)
{
	this->description = trim(description);
}

void Task::setPriority(string priority)
{
	this->priority = trim(priority);
}

void Task::setSeverity(string severity)
{
	this->severity = trim(severity);
}
	
string Task::getTime() const {
	return string( asctime(&timeinfo) );
}
	
int Task::getId() const {
		return id;
	}

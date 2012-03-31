#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cstring>
#include "datamanager.hpp"
using namespace std;

DataManager* DataManager::onlyInstance = NULL;

DataManager::DataManager() : auth_done(false), passcode(), name()
{
	srand ( time(NULL) );
}

DataManager* DataManager::instanceOf()
{
		if(onlyInstance == NULL)
			onlyInstance = new DataManager();
		return onlyInstance;
}

bool DataManager::isAuthDone() const 
{
	return auth_done;
}

bool DataManager::loadFile(const string& name)
{
	ifstream myfile;
	myfile.open(name.c_str());
	if (myfile.is_open())
	{
		bool task_found = false;
		string line;
		string task;
		while ( myfile.good() )
		{
			
			getline (myfile,line);
			
			if(passcode.empty())
			{
				size_t pos = line.find("passcode:");
				if(pos < line.npos)
					passcode = line.substr (pos+8);
			}
			
			if(task_found)
			{
				size_t pos = line.find("}");
				if(pos < line.npos && line.length() == 1)
				{
					todo_list.addTask(Task::convert(task));
					task_found = false;
				}
				else
				{
					task += line;
				}
			}
			else
			{
				size_t pos = line.find("{");
				if(pos < line.npos && line.length() == 1)
				{
					task_found = true;
					
				}
			}
		}
		myfile.close();
		this->name = name;
	}
}

bool DataManager::saveToFile(string name) const
{
	ofstream myfile;
	myfile.open(name.c_str());
	if(myfile.is_open())
	{
		Todos::const_iterator it;
		myfile << "passcode:" << passcode << endl;
		for(it = todo_list.begin() ; it != todo_list.end(); it++)
		{
			myfile << "{" << endl;
			myfile << it->convert() << endl;;
			myfile << "}" << endl;
		}
	}
	
	myfile.close();
}

bool DataManager::auth(const string& pass)
{
	if(pass == passcode)
	{
		this->auth_done = true;
		return true;
	}
	return false;
}
bool DataManager::auth_required() const
{
	return !this->passcode.empty();
}

void DataManager::setPasscode(const string& oldPass,const string& newPass)
{
	if(auth(oldPass))
	{
		this->passcode = newPass;
	}
	else
	{
		cerr << "old passcode incorrcet" << endl;
	}
}
int DataManager::addTask(string title)
{
	int id = todo_list.nextId();
	this->todo_list.addTask( Task(id, title) );
	return id;
}

Todos::iterator DataManager::find(int id)
{
	return todo_list.find(id);
}

Todos::const_iterator DataManager::find(int id) const
{
	return todo_list.find(id);
}

Todos& DataManager::getList() 
{
	return todo_list;
}

const Todos& DataManager::getList() const 
{
	return todo_list;
}



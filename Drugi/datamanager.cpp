#include <iostream>
#include <fstream>
#include "datamanager.hpp"
using namespace std;

bool DataManager::loadFile(string name)
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
	}
}

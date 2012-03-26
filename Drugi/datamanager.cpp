#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cstring>
#include "datamanager.hpp"
using namespace std;

DataManager::DataManager() : auth_done(false)
{
	srand ( time(NULL) );
}

DataManager* DataManager::instanceOf()
{
		if(onlyInstance == NULL)
			onlyInstance = new DataManager();
		return onlyInstance;
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

bool set_date(int id)
{
	DataManager* data = DataManager::instanceOf();
	for(int i = 0; i < 3; ++i)
	{
		string tmp;
		int day, month, year;
		cout << "podaj date" << endl;
		cout << "teraz podaj: dzien" << endl;
		cin >> day;
		cout << "podaj: miesiac" << endl;
		cin >> month;
		cout << "podaj: rok" << endl;
		cin >> year;
		if( data->getList().find(id)->setDate(day,month,year) )
		{
			return true;
		}
		else
			cerr << "bledna data" << endl;
	}
	return false;
}

bool set_time(int id)
{
	DataManager* data = DataManager::instanceOf();
	for(int i = 0; i < 3; ++i)
	{
		string tmp;
		int hour, min, sec;
		cout << "podaj dokladny czas" << endl;
		
		cout << "teraz podaj: godzine" << endl;
		cin >> hour;
		cout << "podaj: minute" << endl;
		cin >> min;
		cout << "podaj: sekunde" << endl;
		cin >> sec;
		if( data->getList().find(id)->setTime(hour,min,sec) )
		{
			return true;
		}
		else
			cerr << "bledny czas" << endl;
	}
	return false;
}

int main(int argc, char** argv)
{
	DataManager* data = DataManager::instanceOf();
	if(argc >=2)
	{
		if(strcmp(argv[1],"-o")==0)
		{
			string file_name(argv[2]);
			data->loadFile(file_name);
		}
	}
	string input;
	
	do
	{
		cout << endl;
		if(data->getList().size() > 0)
		{
			data->getList().getTaskList(); 
			cout << endl;
		}
		cout << "opcje do wyboru:" << endl;
		cout << "open" << endl;
		cout << "create" << endl;
		if(data->getList().size() > 0)
		{
			cout << "save" << endl;
			cout << "setdate" << endl;
			cout << "settime" << endl;
			cout << "setdescription" << endl;
			cout << "settitle" << endl;
			cout << "setpriority" << endl;
			cout << "setseverity" << endl;
		}
		cin >> input;
		if(input == "open")
		{
			cin >> input;
			data->loadFile(input);
			if(data->auth_required())
			{
				for(int i = 0; i < 3; ++i)
				{
					cout << "password:" << endl;
					cin >> input;
					if(data->auth(input))
						cout << "Welcome" << endl;
					else
						cout << "access danied" << endl;
					input = "";
				}
				continue;
			}
		}
		int i = 0;
		if(input == "save")
		{
			cout << "Podaj nazwe pliku:" << endl;
			cin >> input;
				
			if( data->saveToFile(input) )
			{
				cout << "Zapisano" << endl;
			}
			else
			{
				cerr << "Nie udało się zapisać" << endl;
			}
		}
		string tmp; 
		if(input == "create")
		{
			cout << "podaj tytul" << endl;
			cin >> tmp;
			int id = data->addTask(tmp);
			data->getList();
			set_date(id);
			set_time(id);
		}
		if(input == "setpass")
		{
			bool fine = true;
			string opass, npass;
			if(data->auth_required())
			{
				cout << "podaj aktualne haslo:" << endl;
				
				cin >> opass;
				fine = data->auth(opass);
				if(!fine)
					cout << "haslo nieprawidlowe" << endl;
			}
			if(fine)
			{
				cout << "podaj nowe haslo" << endl;
				cin >> npass;
				data->setPasscode(opass,npass);
			}
		}
		if(input == "setdate")
		{
			cout << "podaj id" << endl;
			cin >> i;
			set_date(i);
		}
		if(input == "settime")
		{
			cout << "podaj id" << endl;
			cin >> i;
			set_time(i);
		}
		if(input == "setdescription")
		{
			cout << "podaj id" << endl;
			cin >> i;
			Todos::iterator it = data->find(i);
			if(it != data->getList().end())
			{
				cout << "podaj opis" << endl;
				cin >> tmp;
				it->setDescription(tmp);
			}
		}
		if(input == "settitle")
		{
			cout << "podaj id" << endl;
			cin >> i;
			Todos::iterator it = data->find(i);
			if(it != data->getList().end())
			{
				cout << "podaj tytul" << endl;
				cin >> tmp;
				it->setTitle(tmp);
			}
		}
		if(input == "setpriority")
		{
			cout << "podaj id" << endl;
			cin >> i;
			Todos::iterator it = data->find(i);
			if(it != data->getList().end())
			{
				cout << "podaj priorytet" << endl;
				cin >> tmp;
				it->setPriority(tmp);
			}
		}
		if(input == "setseverity")
		{
			cout << "podaj id" << endl;
			cin >> i;
			Todos::iterator it = data->find(i);
			if(it != data->getList().end())
			{
				cout << "podaj severity" << endl;
				cin >> tmp;
				it->setSeverity(tmp);
			}
		}
		
	}
	while(input != "exit" && input != "quit");
	
	Todos todolist;
	Task t = Task(2,string("Wycieczka            "),string("Wycieczka   w   bieszczady  "),string("Higth"),string("Serious"));
	t.setTime(14,12);
	t.setDate(2,7,2000);
	
	t.getTime();
	todolist.addTask(t);
	t.setTime(16,13);
	t.setDate(22,6,1989);
	todolist.getTaskList();
	
	Task t2 = Task::convert( t.convert() );
	
	cout << t.getTime() << endl;
	todolist.addTask( t2 );
	todolist.getTaskList();
	
}


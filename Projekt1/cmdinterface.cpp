#include <iostream>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include "datamanager.hpp"
using namespace std;

int get_from_stdin()
{
	int i;
    string input;
	   
    getline(cin, input);
    stringstream my_string(input);
    if(!(my_string >> i))
    {
		cerr << "blad: to nie jest liczba" << endl;
		return -1;
	}
	return i;
}

bool set_date(int id)
{
	if(id < 0)
		return false;
	DataManager* data = DataManager::instanceOf();
	for(int i = 0; i < 3; ++i)
	{
		string tmp;
		int day, month, year;
		cout << "podaj date" << endl;
		cout << "teraz podaj: dzien" << endl;
		day = get_from_stdin();
	
		cout << "podaj: miesiac" << endl;
		month = get_from_stdin();
		
		cout << "podaj: rok" << endl;
		year = get_from_stdin();
		try{
			if( data->getList().find(id)->setDate(day,month,year) )
			{
				return true;
			}
		}
		catch(invalid_argument e)
		{
			cerr << "bledna data" << endl;
		}

	}
	return false;
}

bool set_time(int id)
{
	if(id < 0)
		return false;
	DataManager* data = DataManager::instanceOf();
	for(int i = 0; i < 3; ++i)
	{
		string tmp;
		int hour, min, sec;
		cout << "podaj dokladny czas" << endl;
		
		cout << "teraz podaj: godzine" << endl;
		hour = get_from_stdin();

		cout << "podaj: minute" << endl;
		min = get_from_stdin();
		
		cout << "podaj: sekunde" << endl;
		sec = get_from_stdin();
		try{
		if( data->getList().find(id)->setTime(hour,min,sec) )
		{
			return true;
		}
		}
		catch(invalid_argument e)
		{
			cerr << "bledny czas" << endl;
		}
			
	}
	return false;
}

Todos::iterator get_task_by_id()
{
	int i;
    string input;
    Todos::iterator it;
    DataManager* data = DataManager::instanceOf();
	cout << "podaj id" << endl;
	i = get_from_stdin();   
   
    if(i < 0)
    {
		it = data->getList().end();
		cerr << "blad: nie ma takiego id" << endl;
	}
	else
	{
		it = data->find(i);
		if(it == data->getList().end())
		{
			cerr << "blad: Zadanie o podanym id nie istnieje" << endl;
		}
	}
	return it;
}

int get_task_id()
{
	Todos::iterator it = get_task_by_id();
	if(it == DataManager::instanceOf()->getList().end())
		return -1;
	return it->getId();
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
		cout << "exit" << endl;
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
		cout << endl << "->";
		getline(cin,input);
		if(input == "open")
		{
			getline(cin,input);
			data->loadFile(input);
			if(data->auth_required())
			{
				for(int i = 0; i < 3; ++i)
				{
					cout << "password:" << endl;
					getline(cin,input);
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
			getline(cin,input);
				
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
			getline(cin,tmp);
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
				
				getline(cin,opass);
				fine = data->auth(opass);
				if(!fine)
					cout << "haslo nieprawidlowe" << endl;
			}
			if(fine)
			{
				cout << "podaj nowe haslo" << endl;
				getline(cin,npass);
				data->setPasscode(opass,npass);
			}
		}
		if(input == "setdate")
		{
			i = get_task_id();
			set_date(i);
		}
		if(input == "settime")
		{
			i = get_task_id();
			set_time(i);
		}
		if(input == "setdescription")
		{
			Todos::iterator it = get_task_by_id();
			if(it != data->getList().end())
			{
				cout << "podaj opis" << endl;
				getline(cin,tmp);
				it->setDescription(tmp);
			}
		}
		if(input == "settitle")
		{
			Todos::iterator it = get_task_by_id();
			if(it != data->getList().end())
			{
				cout << "podaj tytul" << endl;
				getline (cin,tmp);
				it->setTitle(tmp);
			}
		}
		if(input == "setpriority")
		{
			Todos::iterator it = get_task_by_id();
			if(it != data->getList().end())
			{
				cout << "podaj priorytet" << endl;
				getline (cin,tmp);
				it->setPriority(tmp);
			}
		}
		if(input == "setseverity")
		{
			Todos::iterator it = get_task_by_id();
			if(it != data->getList().end())
			{
				cout << "podaj severity" << endl;
				getline (cin,tmp);
				it->setSeverity(tmp);
			}
		}
		
	}
	while(input != "exit" && input != "quit");

}

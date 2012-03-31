#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <string>
#include "todos.hpp"

class DataManager
{
public:
	static DataManager* instanceOf();
	bool loadFile(const std::string& name);
	bool saveToFile(std::string name) const;
	bool auth(const std::string& pass);
	bool auth_required() const;
	bool isAuthDone() const;
	void setPasscode(const std::string& oldPass, const std::string& newPass);
	int addTask(std::string title);
	Todos::iterator find(int id);
	Todos::const_iterator find(int id) const;
	const Todos& getList() const;
	Todos& getList();
	
private:
	DataManager();
	DataManager(DataManager const&);
	DataManager& operator=(DataManager const&);
	~DataManager(){}
	static DataManager* onlyInstance;
	std::string name;
	std::string passcode;
	Todos todo_list;
	bool auth_done;
	
};

#endif

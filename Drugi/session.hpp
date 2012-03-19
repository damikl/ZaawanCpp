#ifndef SESSION_H
#define SESSION_H
#include <string>

class Session
{
public:
	static Session* instanceOf();
	bool loadFile(std::string name);
	bool auth(std::string pass);
	
private:
	Session(){};
	Session(Session const&){};
	Session& operator=(Session const&){};
	static Session* onlyInstance;
};

#endif

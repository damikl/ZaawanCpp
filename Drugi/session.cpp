#include "session.hpp"
using namespace std;

Session* Session::onlyInstance = new Session;  

Session* Session::instanceOf() {
		return onlyInstance;
	}


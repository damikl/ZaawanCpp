#ifndef NUMBER_H
#define NUMBER_H

class Number
{
public:
	Number(long num = 0);
	long getValue();
	long putDigit(long num);
	Number nwd(long num);
	Number nww(long num);
private: 
	long number;
};

#endif



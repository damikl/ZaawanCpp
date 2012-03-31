#ifndef NUMBER_H
#define NUMBER_H

class Number
{
public:
	Number(long num = 0);
	long getValue() const;
	long putDigit(long num);
	long nwd(long num);
	long nww(long num);
private: 
	long number;
};

#endif



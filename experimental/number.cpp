#include <cstdlib>
#include "number.h"

Number::Number(long num) : number(num) {}

long Number::getValue() const { return number; }

long Number::putDigit(long num)
{
	num = labs(num);
	number = 10*number+num;
	return number;
}

long Number::nwd(long num)
{
	num = labs(num);
	if(num==0)
		return number;
	Number b = Number(num);
	return b.nwd(number % b.getValue());	
}

long Number::nww(long num)
{
	num = labs(num);
	return number*num/nwd(num);
}


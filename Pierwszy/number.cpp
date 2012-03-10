#include "number.h"
#include <gtest/gtest.h>

Number::Number(long num) : number(num) {}

inline long Number::getValue(){ return number; }

inline long Number::putDigit(long num)
{
	number = 10*number+num;
	return number;
}

Number Number::nwd(long num)
{
	if(num==0)
		return number;
	Number b = Number(num);
	return b.nwd(number % b.getValue());	
}

Number Number::nww(long num)
{
	return number*num/nwd(num).getValue();
}

int main(int argc, char **argv)
{
//	::testing::InitGoogleTest(&argc, argv);
//  	return RUN_ALL_TESTS();

}

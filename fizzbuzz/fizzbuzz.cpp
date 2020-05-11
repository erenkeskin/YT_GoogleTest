//============================================================================
// Name        : fizzbuzz.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

string fizzBuzz(int value);
bool isMultiple(int value, int base);

int main()
{

	for(int i = 1; i < 101; i++) {
		cout << i << ": " << fizzBuzz(i) << endl;
	}
	return 0;
}

string fizzBuzz(int value)
{
	if(isMultiple(value, 3)) {
		return "Fizz";
	}
	if(isMultiple(value, 5)) {
		return "Buzz";
	}
	if(isMultiple(value, 3) && (isMultiple(value, 5))) {
		return "FizzBuzz";
	}

	return to_string(value);
}

//
bool isMultiple(int value, int base)
{
	return (0 == (value % base));
}

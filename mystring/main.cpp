//
//  main.cpp
//  mystring
//
//  Created by hongjinwoo on 17/12/2018.
//  Copyright © 2018 hongjinwoo. All rights reserved.
//

#include <iostream>

using namespace std;

class myString {
	char *str;				// 문자열(동적배열)222
	unsigned long len;		// 문자열의 길이
	unsigned long capacity; // 동적배열이 차지하는 공간을 표시
	
public:
	myString(char c);
	myString(const char* _str);
	myString(const myString &s);
	
	unsigned long myStrlen();			//문자열 길이를 구하는 함수
	unsigned long memCapacity();		//동적배열이 차지하는 메모리 공간을 표시
	
	void reserve(int size);
	
	void myStrAdd(int loc, const myString &s);	//문자열 뒤에 다른 문자열 붙이기
	
	void Assign(const myString &s); 	//문자열을 재설정하는 함수
	
	void print();
	char at(int i);
	
	~myString();
};

myString::myString(char c)
{
	str = new char[1];
	str[0] = c;
	len = capacity = 1;
}

myString::myString(const char* _str)
{
	len = capacity = strlen(_str);
	str = new char[len + 1];
	
	for(int i = 0; i < len; i++)
	{
		str[i] = _str[i];
	}
}

myString::myString(const myString &s)
{
	str = new char[s.len + 1];
	len = s.len;
	for(int i = 0; i < len; i++)
	{
		str[i] = s.str[i];
	}
}

unsigned long myString::myStrlen()
{
	for (len = 0; str[len]; len++);
	return len;
}

unsigned long myString::memCapacity()
{
	return capacity;
}

void myString::reserve(int size)
{
	if(capacity < size)
	{
		char *prevStr = str;
		
		str = new char[size];
		capacity = size;
		
		for (int i = 0; i < len; i++)
		{
			str[i] = prevStr[i];
		}
		
		delete [] prevStr;
	}
}

void myString::myStrAdd(int loc, const myString &s) //문자열 뒤에 다른 문자열 붙이기
{
	if(loc + s.len > capacity)
	{
		
	}
}

void myString::Assign(const myString &s)
{
	if(s.len > capacity)
	{
		delete [] str;
		str = new char[s.len];
		
		capacity = s.len;
	}
	
	for (int i = 0; i < s.len; i++)
	{
		str[i] = s.str[i];
	}
	
	len = s.len;
}

void myString::print()
{
	for (int i = 0; i < len; i++)
	{
		cout << str[i];
	}
	cout << endl;
}

char myString::at(int i)
{
	if(i >= len || i < 0)
	{
		return NULL;
	}
	else
	{
		return str[i];
	}
}

myString::~myString()
{
	delete [] str;
}

int main(int argc, const char * argv[]) {
	myString str1("Hello world");
	myString str2 = str1;
	myString str3("Bye & Hello world");
	
	str1.print();
	str2.print();
	
	
	str1.print();
	
	str1.Assign(str3);
	str2.reserve(13);
	
	str2.myStrAdd(3, str3);
	str1.print();
	str2.print();
	cout << str1.at(7) << endl;
	
	return 0;
}
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
	
	myString& myStrIns(int loc, const myString &s);	//문자열 뒤에 다른 문자열 붙이기
	myString& myStrIns(int loc, const char* _str);
	myString& myStrIns(int loc, char c);
	
	myString& myStrErase(int loc, int num);
	
	int find(int find_from, myString& str);
	int find(int find_from, const char* str);
	int find(int find_from, char c);
	
	int compare(myString& cmpStr);
	
	
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
	//메모리를 미리 할당
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

myString& myString::myStrIns(int loc, const myString &s)
{
	//문자열 속에 입력
	if(loc < 0 || loc > len) return *this;
	
	if(len + s.len > capacity)
	{
		
		
		if (capacity * 2 > len + s.len)
		{
			capacity *= 2;
		}
		else
		{
			capacity = len + s.len;
		}
		
		char* prevStr = str;
		str = new char[capacity];
		
		int i;
		for(i = 0; i < loc; i++ )
		{
			str[i] = prevStr[i];
		}
		for(int j = 0; j < s.len; j++)
		{
			str[i + j] = s.str[j];
		}
		for(;i < len; i++)
		{
			str[s.len + i] = prevStr[i];
		}
		delete [] prevStr;
		
		len += s.len;
		
		return *this;
	}
	
	for(unsigned long i = len - 1; i>= loc; i--)
	{
		str[i + s.len] = str[i];
	}
	
	for(int i = 0; i < s.len; i++)
	{
		str[i + loc] = s.str[i];
	}
	
	len += s.len;
	return *this;
}

myString& myString::myStrIns(int loc, const char* _str)
{
	myString temp(_str);
	return myStrIns(loc, temp);
}

myString& myString::myStrIns(int loc, char c)
{
	myString temp(c);
	return myStrIns(loc, temp);
}

myString& myString::myStrErase(int loc, int num)
{
	if(num < 0 || loc < 0 || loc > len) return *this;
	
	for(int i = loc + num; i < len; i++)
	{
		str[i - num] = str[i];
	}
	
	len -= num;
	
	return *this;
}

int myString::find(int find_from, myString &tarStr)
{
	int i, j;
	
	if(tarStr.len == 0) return -1;
	
	for(i = find_from; i < len - tarStr.len; i++)
	{
		for(j = 0; j < tarStr.len; j++)
		{
			if(str[i + j] != tarStr.str[j])
			{
				break;
			}
		}
		
		if(j == tarStr.len) return i;
	}
	
	return -1;
}

int myString::find(int find_from, const char *str)
{
	myString temp(str);
	return find(find_from, temp);
}

int myString::find(int find_from, char c)
{
	myString temp(c);
	return find(find_from, temp);
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

int myString::compare(myString &cmpStr)
{
	//*this - str 을 수행 해서 그 1. 0, -1로 그결과를 리턴한다
	//1은 (*this) 가 사전식으로 더뒤에 온다는 의미. 0은 두문자열이 같다는 의미
	//-1은 (*this)가 사전식으로 더 앞에 온다는 의미이다.
	
	for(int i = 0; i < min(len, cmpStr.len); i++)
	{
		if(str[i] > cmpStr.str[i])
		{
			return 1;
		}
		else if (str[i] < cmpStr.str[i])
		{
			return -1;
		}
		
	}
	
	if(len == cmpStr.len)
	{
		return 0;
	}
	else if (len > cmpStr.len)
	{
		return 1;
	}
	
	return -1;
}
myString::~myString()
{
	delete [] str;
}

int main(int argc, const char * argv[]) {
	myString str1("Hello world");
	myString str2 = str1;
	myString str3("Bye & Hello world");
	myString str4("rld");
	
	str1.print();
	str2.print();
	
	
	str1.print();
	
	str1.Assign(str3);
	str2.reserve(13);
	str2.memCapacity();
	
	str1.myStrIns(5, "Good bye");
	str2.myStrIns(3, str3);
	str3.myStrIns(8, 'A');
	
	str1.print();
	str2.print();
	str3.print();
	str3.myStrErase(8, 2);
	
	cout << str2.find(0, str4) << endl;
	

	str3.print();
	
	return 0;
}

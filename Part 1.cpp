#include "stdafx.h"
#include "string"
#include "iostream"
int _tmain(int argc, _TCHAR* argv[])
{
	std::string str;
	std::cout << "Vvod stroki:";
	std::cin >> str;
	int check = 0;
	for (int i = 0; i < (int)(str.size())/2; i++)
	{
		
		if (str[i] == str[str.size()-i-1])
		{
			check++;
		}
	}
	if (check == (int)(str.size()) / 2)
	{
		std::cout << "Palindrom" << std::endl;
	}
	else
	{
		std::cout << "Ne palindrom" << std::endl;
	}
	system("pause");
	return 0;
}

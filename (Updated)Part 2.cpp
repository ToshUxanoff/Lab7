#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"
void Context(std::string* buf, int * position, int check, int cont, int n)
{
	if (check != 0)
	{
		for (int j = 0; j < check; j++)
		{
			for (int i = 0; i < (cont * 2 + 1); i++)  //cont*2 + 1 - означает количество контекстных слов с обоих сторон + само слово.
			{
				if (position[j] - cont + i < 0)		//Если ищется контекст для первого элемента слева
				{
					continue;
				}
				if (position[j] == position[j] - cont + i)
				{
					std::cout << " |_" << buf[position[j]] << "_| ";  //Для красоты :D  (выделение искомого слова)
					continue;
				}
				std::cout << buf[position[j] - cont + i] << ' ';
				if (buf[position[j] - cont + i] == buf[n - 1]) //Если ищется контекст для последнего элемента справа 
				{
					break;
				}
			}
			std::cout << "\n\n\n";
		}
	}
	else
	{
		std::cout << "This word was not founded. Context does not exist" << std::endl;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int n = 0;				//Счетчик количества слов
	std::ifstream File("FileTest.txt");
	std::string endfile;
	while (std::getline(File, endfile, ' '))
	{
		n++;
	}
	File.clear();
	File.seekg(0);
	std::string *buf = new std::string[n];
	std::string str;
	std::cout << "Keyword : ";
	std::cin >> str;


	int check = 0;
	for (int i = 0; i < n; i++)
	{
		std::getline(File, buf[i], ' ');
		if (buf[i] == str)
		{
			check++;
		}
	}
	int* position = new int[check];
	int j = 0;
	for (int i = 0; i < n; i++)
	{										//Пришлось сделать второй такой же цикл для забивания массива, содержащего позиции искомых слов
		if (buf[i] == str)					//т.к. памяти под него требовалось выделять столько, сколько конкретных найдено слов.
		{
			position[j] = i;
			j++;
		}
	}


	std::cout << "This word was founded in this text " <<check << " times" << std::endl;
	std::cout << "\n Number of context words: ";
	int cont = 0;
	std::cin >> cont;
	Context(buf, position, check, cont, n);


	delete[]buf;
	delete[]position;
	system("pause");
	return 0;
}

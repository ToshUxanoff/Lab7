#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"
void Context(std::string* buf, int * position, int founded, int context_words, int words)
{
	for (int j = 0; j < founded; j++)	
	{
		for (int i = 0; i < (context_words * 2 + 1); i++)  //context_words*2 + 1 - означает количество контекстных слов с обоих сторон + само слово.
		{
			if (position[j] - context_words + i < 0)		//Если ищется контекст для первого элемента слева - пропускаем
			{
				continue;
			}
			std::cout << buf[position[j] - context_words + i] << ' ';
			if (buf[position[j] - context_words + i] == buf[words - 1]) //Если ищется контекст для последнего элемента справа - брейк
			{
				break;
			}
		}
		std::cout << "\n\n\n";
	}
}
int Search(std::ifstream& File, std::string *buf, std::string str, int words)
{
	int founded = 0;
	for (int i = 0; i < words; i++)
	{
		std::getline(File, buf[i], ' ');
		if (buf[i] == str)
		{
			founded++;
		}
	}
	return founded;
}
int FileSize(std::ifstream& File)
{
	int words = 0;
	std::string endfile;
	while (std::getline(File, endfile, ' '))
	{
		words++;
	}
	File.clear();
	File.seekg(0);
	return words;
}
int _tmain(int argc, _TCHAR* argv[])
{
	std::ifstream File("FileTest.txt");
	int words = FileSize(File); //Количество слов
	std::string *buf = new std::string[words];
	std::string str;
	std::cout << "Keyword : ";
	std::cin >> str;
	int founded = Search(File, buf, str, words);
	int* position = new int[founded];
	int j = 0;
	for (int i = 0; i < words; i++)
	{										
		if (buf[i] == str)		
		{
			position[j] = i;
			j++;
		}
	}
	if (founded != 0)
	{	
		std::cout << "This word was founded in this text " << founded << " times" << std::endl;
		std::cout << "\n Number of context words: ";
		int context_words = 0;
		std::cin >> context_words;
		Context(buf, position, founded, context_words, words);
	}
	else
	{
		std::cout << "Word was not founded. Context does not exist!" <<std::endl;
	}
	delete[]buf;
	delete[]position;
	system("pause");
	return 0;
}


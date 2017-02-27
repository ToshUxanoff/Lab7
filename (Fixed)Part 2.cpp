#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"
#include "cctype"

void Context(std::string* word, int * position, int founded, int context_words, int words)
{
	for (int j = 0; j < founded; j++)	
	{
		for (int i = 0; i < (context_words * 2 + 1); i++)  //context_words*2 + 1 - означает количество контекстных слов с обоих сторон + само слово.
		{
			if (position[j] - context_words + i < 0)		//Если ищется контекст для первого элемента слева - пропускаем
			{
				continue;
			}
			else if (word[position[j] - context_words + i] == word[words - 1]) //Если ищется контекст для последнего элемента справа - брейк
			{
				break;
			}
			else
			{
				std::cout << word[(position[j] - context_words) + i] << " ";
			}
		}
		std::cout << std::endl;
	}
}
int Search(std::ifstream& File, std::string *word, std::string str, int words)
{
	int founded = 0;
	for (int i = 0; i < words; i++)
	{
		if (word[i] == str)
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
	while (!File.eof())
	{
		File >> endfile;
		words++;
	}
	File.clear();
	File.seekg(0);
	return words+1;
}
std::string* Read(std::ifstream& File, std::string* word, int words)
{
	char ch = 0;
	std::string buffer;
	for (int i = 0; i < words; i++)
	{
		while (!File.eof())
		{
			File.get(ch);
			if (std::isalnum(ch) == false)
			{
				do
				{
					File.get(ch);
				} while (std::isalnum(ch) == false);
				File.unget();
				break;
			}
			else
			{
				buffer += ch;
			}
		}
		word[i] = buffer;	
		buffer.erase(buffer.begin(), buffer.end());
	}
	return word;
}
int _tmain(int argc, _TCHAR* argv[])
{
	std::ifstream File("FileTest.txt");
	int words = FileSize(File); //Количество слов
	std::string *word = new std::string[words];
	std::string str;
	Read(File, word, words);
	std::cout << "Keyword : ";
	std::cin >> str;
	int founded = Search(File, word, str, words);
	int* position = new int[founded];
	int j = 0;
	for (int i = 0; i < words; i++)
	{										
		if (word[i] == str)		
		{
			position[j] = i;
			j++;
			std::cout << i << ' ';
		}
	}
	if (founded != 0)
	{	
		std::cout << "This word was founded in this text " << founded << " times" << std::endl;
		std::cout << "\n Number of context words: ";
		int context_words = 0;
		std::cin >> context_words;
		Context(word, position, founded, context_words, words);
	}
	else
	{
		std::cout << "Word was not founded. Context does not exist!" <<std::endl;
	}
	delete[]word;
	delete[]position;
	system("pause");
	return 0;
}


}


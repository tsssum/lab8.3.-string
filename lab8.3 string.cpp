#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Файл inp.txt содержит текст, состоящий из нескольких строк.
// Каждая строка состоит из слов, разделенных любым количеством разделителей 
// (разделители могут стоять в начале и в конце строки), количество слов не более 35. 
// Слово – последовательность латинских букв (количество букв в слове не превышает 15).
// Другие символы, отличные от латинских букв и пробелов, в файле отсутствуют.
// Требуется создать файл out.txt, в который записать сначала слова, в которых гласных букв больше, чем согласных, 
// затем все остальные(каждое слово расположить на отдельной строке).
// В каждой группе слова необходимо вывести в том же порядке, в каком они определены в исходном файле.
// Гласные буквы латинского алфавита – a, e, i, o, u y.

const int n = 35;

int check_file(std::ifstream& file);
void fill_word(std::ofstream& file, std::string word);
void fill_file(std::ofstream& file, std::string word[n], int& row);
bool what_more(std::string word);
void task(std::ifstream& file_inp, std::ofstream& file_out);

std::string token(" ,.:;-\n");

int main()
{
	std::ifstream file_inp("inp.txt");
	switch (check_file(file_inp))
	{
	case 0:
		std::cout << "file is empty\n";
		break;
	case -1:
		std::cout << "file isnt exist\n";
		break;
	default:
		std::ofstream file_out("out.txt");
		task(file_inp, file_out);
		std::cout << "check out.txt :)";
		break;
	}
	file_inp.close();
	std::cin.get();
}

int check_file(std::ifstream& file)
{
	int res{ 1 };
	if (!file) res = -1;
	else if (file.peek() == EOF) res = 0;
	return res;
}

void fill_word(std::ofstream& file, std::string word)
{
	size_t len = word.length();
	for (size_t i{}; i < len; ++i)
		file << word[i];
	file << '\n';
}

void fill_file(std::ofstream& file, std::string word[n], int& row)
{
	for (int i{}; i < row; ++i)
		fill_word(file, word[i]);
}


bool what_more(std::string word)
{
	int vowels{};
	size_t len = word.length();
	std::string vow("aAeEiIoOuUyY");
	for (size_t i{}; i < len; ++i)
	{
		if (vow.find(word[i]) != std::string::npos)
			++vowels;
	}
	return 2 * vowels > len;
}

void task(std::ifstream& file_inp, std::ofstream& file_out)
{
	std::string matr[n], line;
	int i{};
	while (getline(file_inp, line) && i < n)
	{
		size_t start, end{};
		while ((start = line.find_first_not_of(token, end)) != std::string::npos && i < n)
		{
			end = line.find_first_of(token, start);
			std::string word = line.substr(start, end - start);
			size_t len = word.length();
			if (what_more(word))
				fill_word(file_out, word);
			else
			{
				matr[i] = word;
				++i;
			}
		}
	}
	fill_file(file_out, matr, i);
}
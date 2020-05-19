/*
* ЮФУ ИКТИБ МОП ЭВМ.
* Неприн Михаил Андреевич, КТбо1-1.
* Машина Тьюринга
* 19.05.2020
*/


#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <array>




using namespace std;

class TuringMachine
{
	public:

		//Конструктор класса. Считывание входных параметров.
		TuringMachine()
		{
			//Считывание начальной ленты.
			cout << "Введите название файла.расширение, содержащего начальную ленту и инструкции" << endl;
			string filename;
			cin >> filename;
			ifstream fin;
			fin.open(filename, ios::in);
			if (!fin)
			{
				cout << "Невозможно открыть файл."<< endl;
				exit(1);
			}
			string buff;
			fin >> buff;

			for (int i = 0; i < buff.length(); i++ )
			{
				tape.push_back(buff[i]);
			}

			//двумерный массив в котором строки - состояние
			//а столбцы - алфавит.
			buff.clear();
			int tablestart = fin.tellg();
			{
			int i = 0;
			do
			fin >> buff;
			while(buff[i] != '\n');
			}
			for (int i = 0; i < buff.length(); i++)
			{
				alphabet.push_back(buff[i]);
			}

			fin.seekg(tablestart);
			for (int i = 0; !fin.eof(); i++)
			{
				buff.clear();
				fin >> buff;
				states.push_back(buff);
				for (int j = 0; j < alphabet.size(); j++)
				{
					buff.clear();
					fin >> buff;
					rules[i][j] = buff;
				}
			}
			
		}


		void displayTape()
		{	
			for (auto i = tape.begin(); i != tape.end(); i++)
			{
				cout << *i;
			}
			return;
		}


	private:
		list<char> tape;
		vector<char> alphabet;
		vector<string> states;
		array<array<string, 100>, 50> rules;


};



int main(int argc, char const *argv[])
{

	TuringMachine tm;
	return 0;
}
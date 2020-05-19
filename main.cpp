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
			//cout << "Введите название файла.расширение, содержащего начальную ленту и инструкции" << endl;
			//string filename;
			//cin >> filename;
			//ifstream fin(filename);
			ifstream fin("tm.txt");

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
			fin.seekg((int)fin.tellg() + 1 );
			int tablestart = fin.tellg();
			getline(fin,buff);
			int statesstart = fin.tellg();
			for (int i = 0; i < buff.length(); i++)
			{
				if (buff[i] != ' ' && buff[i] != '\t')
					alphabet.push_back(buff[i]);
			}

			fin.seekg(statesstart);
			for (int i = 0;; i++)
			{
				buff.clear();
				fin >> buff;
				if (buff.empty())
					break;
				states.push_back(buff);
				for (int j = 0; j < alphabet.size(); j++)
				{
					buff.clear();
					fin >> buff;
					rules[i][j] = buff;
				}
			}
			fin.close();
			
		}


		void showTape()
		{	
			for (auto i = tape.begin(); i != tape.end(); i++)
			{
				cout << *i;
			}
			cout <<endl;
			return;
		}

		void showAlphabet()
		{
			for (int i = 0; i < alphabet.size(); i++)
			{
				cout << alphabet[i]<< " ";
			}	
			cout <<endl;
			return;
		}

		void showStates()
		{
			for (int i = 0; i < states.size(); i++)
			{
				cout << states[i] << " ";
			}
			cout << endl;
			return;
		}

		void showRules()
		{
			for (auto i = 0; i < states.size(); i++)
				{
					for (int j = 0; j < alphabet.size();j++)
					{
						
							cout << rules[i][j] << " ";
					}
					cout << endl;
				}
			return;
		}




	private:
		list<char> tape;
		vector<char> alphabet;
		vector<string> states;
		array<array<string, 100>, 50> rules {};


};



int main(int argc, char const *argv[])
{
	TuringMachine tm;
	tm.showRules();
	return 0;
}
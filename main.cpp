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
#include <map>
#include <cstdlib>
#include <array>
#include <unistd.h>


#define RWH_MOV "LNR"
#define MAX_ALPHABET 50
#define MAX_STATES 100



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
				cout << "ОШИБКА!" << endl;
				cout << "Невозможно открыть файл."<< endl;
				exit(-1);
			}
			string buff;
			fin >> buff;

			for (size_t i = 0; i < buff.length(); i++ )
			{
				tape.push_back(buff[i]);
			}

			//двумерный массив в котором строки - состояние
			//а столбцы - алфавит.
			buff.clear();
			fin.seekg((int)fin.tellg() + 1 );
			getline(fin,buff);
			int statesstart = fin.tellg();
			for (size_t i = 0; i < buff.length(); i++)
			{
				if (buff[i] != ' ' && buff[i] != '\t')
					alphabet.emplace(buff[i],buff[i]);
			}

			fin.seekg(statesstart);
			for (size_t i = 0;; i++)
			{
				buff.clear();
				fin >> buff;
				if (buff.empty())
					break;

				states.emplace(stoi(buff.substr(1)),buff);
				for (size_t j = 0; j < alphabet.size(); j++)
				{
					buff.clear();
					fin >> buff;
					rules[i][j] = buff;
				}
			}
			fin.close();
			
		}







		void start()
		{
			checkTape();
			checkRules();
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
			for (size_t i = 0; i < alphabet.size(); i++)
			{
				cout << alphabet[i]<< " ";
			}	
			cout <<endl;
			return;
		}

		void showStates()
		{
			for (size_t i = 0; i < states.size(); i++)
			{
				cout << states[i] << " ";
			}
			cout << endl;
			return;
		}

		void showRules()
		{
			for (size_t i = 0; i < states.size(); i++)
				{
					for (size_t j = 0; j < alphabet.size();j++)
					{
						
							cout << rules[i][j] << " ";
					}
					cout << endl;
				}
			return;
		}




	private:

		list<char> tape;
		list<char>::pointer RWH;
		map<char, char> alphabet;
		map<unsigned int, string> states;
		array<array<string, MAX_STATES>, MAX_ALPHABET> rules {};


		void checkTape()
		{
			for (list<char>::iterator it = tape.begin(); it != tape.end(); it++ )
			{
				bool isDeclarated = false;

					if (*it == alphabet[*it])
						isDeclarated = true;
				if (!isDeclarated){
					cout << "ОШИБКА!" << endl; 
					cout << "В ленте использован символ, не описанный в алфавите." << endl;
					exit(-1);
				}

			}
		}


		void checkRules()
		{
			for (size_t i = 0; i < states.size(); i++)
				{
					for (size_t j = 0; j < alphabet.size();j++)
					{
						
						string temp = rules[i][j];
						if (rules[i][j].compare("-") != 0)	// Обработка искючения. Разрешенный символ '-' для пустых правил.
						{



							//Проверка правильности указанных  состояний
							string temp2 = temp.substr(1,(temp.length() - 2)-1);	//Номер состояния записан между символом RWH и первым символом 'q'.	
							unsigned int state = stoul(temp2);
							if (states.find(state) -> first != state)
							{
								cout << "ОШИБКА!" << endl; 	
								cout << "В правиле "<< temp << " использовано неописанное состояние Машины Тьюринга." << endl;
								exit(-1);
							}



							//Проверка правильности указанного символа перемещения RWH.
							string mov = RWH_MOV;
							string::size_type isCorrectMov = mov.find(temp[temp.length() - 2]);     // Символ перемещения RWH всегда находится на предпоследнем месте, поэтому мы отнимаем -2 (\0 и последний символ)
							if (isCorrectMov == string::npos){
								cout << "ОШИБКА!" << endl; 
								cout << "В правиле "<< temp << " использован посторонний символ перемещения головки." << endl;
								cout << "Разрешенные символы \"" << RWH_MOV <<"\"." << endl;
								exit(-1);
							}



							char c = temp[temp.length() - 1];
							if (alphabet.find(c) -> first != c)
							{
								cout << "ОШИБКА!" << endl; 	
								cout << "В правиле "<< temp << " использован не описанный в алфавите символ." << endl;
								exit(-1);
							}













						}
						
					}
			}
		}
};



int main(int argc, char const *argv[])
{
	TuringMachine tm;
	tm.start();
	return 0;
}
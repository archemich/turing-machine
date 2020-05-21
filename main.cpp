/*
* ЮФУ ИКТИБ МОП ЭВМ
* Неприн Михаил Андреевич, КТбо1-1
* https://github.com/archemich/turing-machine
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
#define OUTPUTSPEED 300000

std::string filename;



using namespace std;

class TuringMachine
{
	public:
		//Конструктор класса. Считывание входных параметров.
		TuringMachine()
		{
			//Считывание начальной ленты.
			cout << "Введите \"название файла.расширение\", содержащего начальную ленту и инструкции" << endl;

			cin >> filename;
			ifstream fin(filename);
		

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

			buff.clear();
			fin.seekg((int)fin.tellg() + 1 );
			getline(fin,buff);
			long int statesstart = fin.tellg();
			int counter = 0;
			for (size_t i = 0; i < buff.length(); i++)
			{

				if (buff[i] != ' ' && buff[i] != '\t'){
					alphabet.emplace(buff[i], counter);
					counter++;
				}
			}
			
			states.emplace(0,"q0");
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
			RWH = tape.begin();
			string state = "q1";
			string nextstate;
			char mov;
			char newsym;
			string rule;
			displayTape(state);
	
			while (state != "q0")
			{
				rule = rules[stoul(state.substr(1, state.length() - 1)) - 1][alphabet.find(*RWH) -> second]; 	//rules[][]	 В первой скобке (int)номер состояния, во второй скобке номер буквы алфавита(map<char><unsigned int>) 
				if (rule != "-"){
				state = rule.substr(0, (rule.length() - 2));
				mov = rule[rule.length() - 2];
				newsym = rule[rule.length() - 1];
				*RWH = newsym;
				switch (mov) {
					case 'L': if (RWH == tape.begin()) {
						tape.push_front('_'); 
					}
					RWH--;
					break;
					
					case 'R': if (RWH==tape.end()){
						tape.push_back('_');
					}
					RWH++;
					break;
				}
			} else {
				cout << "ОШИБКА!" << endl; 
				cout << "Команда не задана." << endl;
				exit(-1);
				}
				displayTape(state);
			}
		}


		void displayTape(string state)
		{
			system("clear");
			cout << "Turing Machine Simulator made by archemich"<<endl;
			printTable();
			for (list<char>::iterator i = tape.begin(); i != tape.end(); i++)
			{
				cout << *i;
			}
			cout <<endl;
			for (list<char>::iterator temp = tape.begin(); temp != RWH; temp++)
			{
				cout << " ";
			}
			cout << "^(" << state << ")";
			cout << flush;
			usleep(OUTPUTSPEED);
			return;
		}





	private:

		list<char> tape;
		list<char>::iterator RWH;
		map<char, unsigned int> alphabet;
		map<unsigned int, string> states;
		array<array<string, MAX_STATES>, MAX_ALPHABET> rules {}; //двумерный массив в котором строки - состояние, а столбцы - алфавит.

		void checkTape()
		{
			for (list<char>::iterator it = tape.begin(); it != tape.end(); it++ )
			{
				bool isDeclarated = false;

					if (*it == (alphabet.find(*it) -> first))
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
						if ((rules[i][j].compare("-")) != 0 && (rules[i][j].compare("") != 0))	// Обработка искючения. Разрешенный символ '-' для пустых правил.
						{

							//Проверка правильности указанных  состояний
							string temp2 = temp.substr(1,(temp.length() - 2)-1);	//Номер состояния записан между символом RWH и первым символом 'q'.	
							long unsigned int state = stoul(temp2);
							if (states.find((unsigned int)state) -> first != state)
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

		void printTable()
		{
			system(("cat " + filename).c_str());
			return;
		}
};




int main(int argc, char const *argv[])
{
	TuringMachine tm;
	tm.start();
	return 0;
}
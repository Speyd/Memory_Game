#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <chrono>
#include "windows.h"
#include <algorithm>
using namespace std;
#pragma region SpecialFunctions
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\t\tПамять" << endl;
}
void Enter() {
	string enter;
	cin.ignore();
	do {
		cout << "Нажмите enter что-бы продолжить: "; getline(cin, enter);
	} while (enter.empty() == false);
}
#pragma endregion
#pragma region ActionsSymbol
void InputInfoSymbol(vector<vector<string>>& symbol) {
	char symbol_variation[] = "@@!!##$$%%&&**++--00";
	int line, column;
	for (int i = 0; i != symbol.size()*symbol[0].size(); i++) {
		//int index_sym = rand() % (9 - 0 + 1) + 0;
		do {
			line = rand() % ((symbol.size() - 1) - 0 + 1) + 0;
			column = rand() % ((symbol[0].size() - 1) - 0 + 1) + 0;
		} while (!symbol[line][column].empty());
		symbol[line][column] = 'X';
		symbol[line][column] += symbol_variation[i];
	}
}
void OutInfoSymbol(vector<vector<string>> symbol) {
	for (int i = 0; i != symbol.size(); i++) {
		for (int l = 0; l != symbol[i].size(); l++) {
			cout << symbol[i][l][0]<<' ';
		}
		cout << endl;
	}
}
#pragma endregion
#pragma region Actions
void CheckAmountTure(vector<vector<string>> symbol, int& amount_true) {
	for (int i = 0; i != symbol.size(); i++) {
		for (int l = 0; l != symbol[i].size(); l++) {
			if (symbol[i][l][0] != 'X')amount_true++;
		}
	}
}
void Hints(vector<vector<string>>& symbol,int& amount_hints) {
	if (amount_hints != 0) {
		amount_hints--;
		cout << "У вас осталось " << amount_hints << " попыток!" << endl;
		Enter();
		ClearScrean();
		for (int i = 0; i != symbol.size(); i++) {
			for (int l = 0; l != symbol[i].size(); l++) {
				if (symbol[i][l][0] == 'X')cout << symbol[i][l][1] << ' ';
				else cout << symbol[i][l][0] << ' ';
			}
			cout << endl;
		}
		Sleep(250);
	}
	else {
		cout << "Вы не можете использовать подсказку, У вас осталось 0 подсказок!"<<endl;
		Enter();
	}
}
void CheckSymbol(vector<vector<string>>& symbol,int& amount_hints,int& attempts) {
	float index[2] = { 1,1 };
	for (int i = 0; i != 2; i++) {
		do {
			ClearScrean();
			OutInfoSymbol(symbol);
			if (index[i] >= 1 && index[i] <= symbol.size() * symbol[0].size())cout << "Введите номер "<<i+1<<"-ой ячейки которую хотите открыть(0 что-бы использывать подсказку): ";
			else cout << "Такой ячейки нету в табличке!\nВведите номер " << i + 1 << "-ой ячейки которую хотите открыть снова(0 что-бы использывать подсказку): ";
			cin >> index[i];
			if (index[i] == 0) { Hints(symbol, amount_hints); return; }
			if (index[i] >= 1 && index[i] <= symbol.size() * symbol[0].size() && symbol[int(ceil(index[i] / symbol.size())) - 1][(symbol[0].size() - 1) + index[i] - int(ceil(index[i] / symbol.size())) * symbol[0].size()][0] != 'X') {
				ClearScrean();
				OutInfoSymbol(symbol);
				cout << "Вы уже вводили эту ячейку!\nВведите другую ячейку(0 что-бы использывать подсказку): ";
				cin >> index[i];
			}
		} while (index[i]<1 || index[i]>symbol.size() * symbol[0].size() && symbol[int(ceil(index[i] / symbol.size())) - 1][(symbol[0].size() - 1) + index[i] - int(ceil(index[i] / symbol.size())) * symbol[0].size()][0] == 'X');
		swap(symbol[int(ceil(index[i] / symbol.size()))-1][(symbol[0].size() - 1) +index[i]-int(ceil(index[i] / symbol.size()))*symbol[0].size()][0], symbol[int(ceil(index[i] / symbol.size())) - 1][(symbol[0].size() - 1) + index[i] - int(ceil(index[i] / symbol.size())) * symbol[0].size()][1]);
	}
	attempts ++;
	ClearScrean();
	OutInfoSymbol(symbol);
	Sleep(1000);
	if (symbol[int(ceil(index[0] / symbol.size())) - 1][(symbol[0].size() - 1) + index[0] - int(ceil(index[0] / symbol.size())) * symbol[0].size()][0] != symbol[int(ceil(index[1] / symbol.size())) - 1][(symbol[0].size() - 1) + index[1] - int(ceil(index[1] / symbol.size())) * symbol[0].size()][0]) {
		swap(symbol[int(ceil(index[0] / symbol.size())) - 1][(symbol[0].size() - 1) + index[0] - int(ceil(index[0] / symbol.size())) * symbol[0].size()][0], symbol[int(ceil(index[0] / symbol.size())) - 1][(symbol[0].size() - 1) + index[0] - int(ceil(index[0] / symbol.size())) * symbol[0].size()][1]);
		swap(symbol[int(ceil(index[1] / symbol.size())) - 1][(symbol[0].size() - 1) + index[1] - int(ceil(index[1] / symbol.size())) * symbol[0].size()][0], symbol[int(ceil(index[1] / symbol.size())) - 1][(symbol[0].size() - 1) + index[1] - int(ceil(index[1] / symbol.size())) * symbol[0].size()][1]);
		ClearScrean();
		OutInfoSymbol(symbol);
		cout << "Символы разные!\n";
	}
	else cout << "Вы угадали!\n";
	Sleep(1500);
}
#pragma endregion
int main() {
	srand(time(0));
	setlocale(LC_ALL, "Rus");
	int line=1, column=2, amount_true = 0,amount_hints = 3, attempts = 0;
	ClearScrean();
	do {
		if (column > 0 && column % 2 == 0)cout << "Введите ширина поля: ";
		else if (column <= 0)cout << "Ширина поля должна быть больше нуля!\nВведите ширина поля снова: ";
		else if (column % 2 != 0)cout << "Ширина поля должна быть четной !\nВведите ширина поля снова: ";
		cin >> column;
		if (column > 0 && column % 2 == 0)break;
	} while (true);
	ClearScrean();
	do {
		if (line > 0 )cout << "Введите длину поля: ";
		else if (line <= 0)cout << "Ширина поля должна быть больше нуля!\nВведите дину поля снова: ";
		cin >> line;
		if (line > 0 )break;
	} while (true);
	vector<vector<string>> symbol;
	symbol.resize(line);
	for (int i = 0; i != line; i++)symbol[i].resize(column);
	InputInfoSymbol(symbol);
	do {
		OutInfoSymbol(symbol);
		CheckAmountTure(symbol, amount_true);
		if (amount_true == symbol.size() * symbol[0].size())break;
		else amount_true = 0;
		ClearScrean();
		CheckSymbol(symbol, amount_hints, attempts);
	} while (true);
	ClearScrean();
	OutInfoSymbol(symbol);
	cout << "Вы угадали разположение всех символов!\nУ вас это заняло "<< attempts <<" попытки!";
	return 0;
}
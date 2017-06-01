/* Zadanie 3, C++, GCC 4.7.1 */

/*
Program umo¿liwia sprawdzanie dowolnego diagramu sudoku. W przypadku niestandardowych wymiarów (za wymiary niestandardowe przyjmujemy takie 
których pierwiastek nie daje liczby naturalnej tj. np. 5x5 ; 14x14 itd.) program ustala dostêpne wymiary mniejszych boxów i umo¿liwia u¿ytkownikowi dokonanie wyboru. 
W przypadku standardowych wymiarów, program wybiera klasyczn¹ opcje gdzie box ma wymiar pierwiastka rozmiaru planszy(dla sudoku 9x9, box ma wymiary 3x3).
Takie rozwi¹zania umo¿liwiaj¹ elastyczn¹ mo¿liwosæ sprawdzania plansz o dowolnych rozmiarach.

*/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Funkcja wczytuj¹ca diagram Sudoku
void getPuzzle(int &size, string fileName, vector <int> &puzzle ){
	ifstream filePuzzle;
	filePuzzle.open(fileName.c_str());
	int tmp;
	while(filePuzzle >> tmp){
		puzzle.push_back(tmp);
	}
	size = puzzle.size();
	double sqrtSize = sqrt(size);
	if (sqrtSize== (int)sqrtSize) size = sqrtSize; else size = -1;
	filePuzzle.close();
}

//Funkcja sprawdzaj¹ca diagram
bool checkPuzzle(int size, vector <int> puzzle){
	int ** tab = new int * [size];
	int * numbers = new int[size];
	bool flag = false;
	
	//Vector do tablicy
	
	for(int i = 0; i < size; i++){
		tab[i] = new int [size];
	}
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			tab[i][j] = puzzle[i*size+j];
		}
	}
	
	for(int i = 0; i < size; i++) numbers[i] = 0;
	
	
	/*************** Sprawdzanie w poziomie ********************/
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			int index = tab[i][j];
			if(index > 0 && index <= size) numbers[index-1]++; else { flag = true; break; }
		}
		if(flag) break;
		for(int j = 0; j < size; j++){
			if(numbers[j] != 1){ flag = true; break; }
			numbers[j] = 0;
		}	
		if(flag) break;
	}
	
	/**********************************************************/
	
	if(flag) return false;
	
	/*************** Sprawdzanie w pionie ********************/
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			int index = tab[j][i];
			if(index > 0 && index <= size) numbers[index-1]++; else { flag = true; break; }
		}
		if(flag) break;
		for(int j = 0; j < size; j++){
			if(numbers[j] != 1){ flag = true; break; }
			numbers[j] = 0;
		}	
		if(flag) break;
	}
	
	/**********************************************************/
	
	if(flag) return false;
	
	/*************** Sprawdzanie w boxie ********************/
	
	int boxW; // szerokosc
	int boxH; // wysokosc
	
	double sqrtSize = sqrt(size);
	if (sqrtSize== (int)sqrtSize){
		//Dla plansz np. 4x4, 9x9 16x16 ma³e boxy maj¹ wymiary sqrt(size)
		boxW = sqrtSize;
		boxH = sqrtSize;
	}else{
		bool choice = false;
		for(int n = 1; n <= size/2; n++){
			if(size%n == 0){
				char key;
				cout << "Czy plansza podzielona jest na bloki o wymiarze " << size/n << " x " << n << " ? t - jesli tak, inny klawisz zeby wybrac inne wymiary" << endl;
				cin >> key;
				if(key == 't'){ boxW = size/n; boxH = n; choice = true; break;}
			}
		}
		if(!choice) {
			cout << "Brak wyboru! Plansza zostanie podzielona na bloki o wymiarze " << size << " x 1 " << endl;
			boxW = size;
			boxH = 1;
		}
	}
	
	for(int l=0; l<boxH; l++){
		for(int k=0; k<boxW; k++){
			for(int i = (size/boxH)*l; i<(size/boxH)*(l+1); i++){
				for(int j = (size/boxW)*k; j <(size/boxW)*(k+1); j++){
					int index = tab[i][j];
					if(index > 0 && index <= size) numbers[index-1]++; else { flag = true; break; }
				}
			}
			if(flag) break;
			for(int j = 0; j < size; j++){
				if(numbers[j] != 1){ flag = true; break; }
				numbers[j] = 0;
			}	
			if(flag) break;
		}
	}
	
	/**********************************************************/
	
	if(flag) return false;
	
	delete [] numbers;
	return !flag;
}
int main(){
	//zmienne
	int size;
	
	string fileName;
	
	vector<int> puzzle;
	
	cout << "Podaj nazwe pliku (wraz z rozszerzeniem .txt!): ";
	cin >> fileName;
	if(fileName.empty()) cout << "Podaj poprawna nazwe pliku!" << endl;
	
	getPuzzle(size, fileName, puzzle);
	
	if(size != -1){
	
		if(checkPuzzle(size, puzzle)) cout << "Poprawnie!" << endl; else cout << "Niepoprawnie!" << endl;

	}else cout << "Program nie obsluguje tego rozmiaru diagramu!" << endl;
	
	system("pause");
	return 0;
}

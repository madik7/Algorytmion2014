/* Zadanie 2, C++, GCC 4.7.1 */

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

//Funkcja wczytuj¹ca planszê z pliku
void getBoard(int size, bool ** &board){
	ifstream gameFile;
	gameFile.open("gra.txt");
	
	string tmp;
	for(int i = 0; i < size; i++){
		gameFile >> tmp;
		for(int j = 0; j < size; j++){
			if(tmp[j] == 'x') board[i][j] = true; else board[i][j] = false;
		}
	}
	gameFile.close();
}

//Funkcja zwracaj¹ca ilosæ punktów ze wzglêdu na licznik(counter)
int points(int counter){
	switch(counter){
		case 2: return 1; break;
		case 3: return 3; break;
		case 4: return 7; break;
		case 5: return 15; break;
	}
	return 0;
}

int main(){
	//zmienne
	int size = 5; //Rozmiar planszy

	int pointsX = 0;
	int pointsO = 0;
	
	int maxX = 0;
	int maxO = 0;
	int maxX2 = 0;
	int maxO2 = 0;

	int resultX = 0;
	int resultO = 0;
	
	bool flag = true;
	bool flag2 = true;
	
	bool ** board = new bool * [size];

	for(int i = 0; i < size; i++){
		board[i] = new bool[size];
	}

	getBoard(size, board);
	
	//Sprawdzanie w poziomie
	for(int i = 0; i < size; i++){
		int tmp = 0;
		for(int j = 0; j < size; j++){
			if(board[i][j] == true){
			
				if(flag){ tmp++; if(tmp>maxX) maxX = tmp;} else  {  tmp = 1; flag = true; }
				
			}else{
				
				if(!flag){ tmp++; if(tmp>maxO) maxO = tmp;} else  {  tmp = 1; flag = false; }
				
			}
		}
		resultX += points(maxX);
		resultO += points(maxO);
		maxX = 0;
		maxO = 0;
	}
	
	//Sprawdzanie w pionie
	for(int j = 0; j < size; j++){
		int tmp = 0;
		for(int i = 0; i < size; i++){
			if(board[i][j] == true){
			
				if(flag){ tmp++; if(tmp>maxX) maxX = tmp;} else  {  tmp = 1; flag = true; }
				
			}else{
				
				if(!flag){ tmp++; if(tmp>maxO) maxO = tmp;} else  {  tmp = 1; flag = false; }
				
			}
		}
		resultX += points(maxX);
		resultO += points(maxO);
		maxX = 0;
		maxO = 0;
	}
	
	//Sprawdzanie po ukosie 
	
	for(int k = 0; k < size; k++){
		int tmp = 0;
		int tmp2 = 0;
		for(int n = 0; n <= k; n++){
			
			int i = n; 
			int j = k-n; 
			int i2 = (size-1) - (k-n); 
			int j2 = size - n - 1; 
			
			if(k != 4){
			
				if(board[i][j] == true){
				
					if(flag){ tmp++; if(tmp>maxX) maxX = tmp; }else  {  tmp = 1; flag = true; }
					
				}else{
					
					if(!flag){ tmp++; if(tmp>maxO) maxO = tmp;} else  {  tmp = 1; flag = false; }
					
				}
				if(board[i2][j2] == true){
				
					if(flag2){ tmp2++; if(tmp2>maxX2) maxX2 = tmp2;} else  {  tmp2 = 1; flag2 = true; }
					
				}else{
					
					if(!flag2){ tmp2++; if(tmp2>maxO2) maxO2 = tmp2;} else  {  tmp2 = 1; flag2 = false; }
					
				}
			}else{
				
				if(board[i][j] == true){
				
					if(flag){ tmp++; if(tmp>maxX) maxX = tmp;} else  {  tmp = 1; flag = true; }
					
				}else{
					
					if(!flag){ tmp++; if(tmp>maxO) maxO = tmp;} else  {  tmp = 1; flag = false; }
					
				}	
				
			}
		}
		resultX += points(maxX);
		resultO += points(maxO);
		resultX += points(maxX2);
		resultO += points(maxO2);
		maxX = 0;
		maxO = 0;
		maxX2 = 0;
		maxO2 = 0;
	}

	//Sprawdzanie po ukosie
	for(int k = 0; k < size; k++){
		int tmp = 0;
		int tmp2 = 0;
		for(int n = 0; n <= k; n++){
			
			int i = n; 
			int j = ((size-1) - (k-n)); 
			int i2 = ((size-1) - (k-n)); 
			int j2 = n; 
			
			if(k != 4){
			
				if(board[i][j] == true){
				
					if(flag){ tmp++; if(tmp>maxX) maxX = tmp;} else  {  tmp = 1; flag = true; }
					
				}else{
					
					if(!flag){ tmp++; if(tmp>maxO) maxO = tmp;} else  {  tmp = 1; flag = false; }
					
				}
				if(board[i2][j2] == true){
				
					if(flag2){ tmp2++; if(tmp2>maxX2) maxX2 = tmp2;} else  {  tmp2 = 1; flag2 = true; }
					
				}else{
					
					if(!flag2){ tmp2++; if(tmp2>maxO2) maxO2 = tmp2;} else  {  tmp2 = 1; flag2 = false; }
					
				}
			}else{
				
				if(board[i][j] == true){
				
					if(flag){ tmp++; if(tmp>maxX) maxX = tmp;} else  {  tmp = 1; flag = true; }
					
				}else{
					
					if(!flag){ tmp++; if(tmp>maxO) maxO = tmp;} else  {  tmp = 1; flag = false; }
					
				}	
				
			}
		}
		resultX += points(maxX);
		resultO += points(maxO);
		resultX += points(maxX2);
		resultO += points(maxO2);
		maxX = 0;
		maxO = 0;
		maxX2 = 0;
		maxO2 = 0;
	}
	
	//Wypisujemy wynik
	cout << "Gracz X: " << resultX << endl <<  "Gracz O: " << resultO << endl;
	
	for(int i = 0; i < size; i++) delete [] board[i];
	
	delete [] board;
	
	system("pause");	
	return 0;
}

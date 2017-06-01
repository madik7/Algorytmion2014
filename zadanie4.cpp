/* Zadanie 4, C++, GCC 4.7.1 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

//Funkcja zapisuj¹ca szachownicê do pliku
void saveBoard(char color, char chessmen, int x, int y, int size, bool ** board){
	ofstream boardFile;
	boardFile.open("szachy.txt");
	boardFile << "  ";
	for(int i = 0; i < size; i++) boardFile << i+1 << " ";
	boardFile << endl;
	for(int i = 0; i < size; i++){
		boardFile << i+1 << " ";
		for(int j = 0; j < size; j++){
			if(i == x && j == y){
				if(color == 'b'){
					boardFile << static_cast<char>(toupper(chessmen)) << " ";
				} else {
					boardFile << chessmen << " ";
				}
			}else{
				if(board[i][j]) boardFile << "x "; else boardFile << "  ";
			}	
		}
		boardFile << endl;
	}
	boardFile.close();
}

void rook(char color, int x, int y, int size, bool ** &board){
	for(int i = 0; i < size; i++) board[i][y] = true;
	for(int i = 0; i < size; i++) board[x][i] = true;
}

void bishop(char color, int x, int y, int size, bool ** &board){
	for(int i = 0; i < size; i++){
		if(x+i >= size || y+i >= size) break;
		board[x+i][y+i] = true;
	}
	
	for(int i = 0; i < size; i++){
		if(x-i < 0 || y+i >= size) break;
		board[x-i][y+i] = true;
	}
	
	for(int i = 0; i < size; i++){
		if(x-i < 0 || y-i < 0) break;
		board[x-i][y-i] = true;
	}
	
	for(int i = 0; i < size; i++){
		if(x+i >= size || y-i < 0) break;
		board[x+i][y-i] = true;
	}
}

void knight(char color, int x, int y, int size, bool ** &board){
	if(x+1 < size && y+2 < size) board[x+1][y+2] = true;
	if(x+1 < size && y-2 >= 0) board[x+1][y-2] = true;
	
	if(x-1 < size && y+2 < size) board[x-1][y+2] = true;
	if(x-1 < size && y-2 >= 0) board[x-1][y-2] = true;
	
	if(x+2 < size && y+1 < size) board[x+2][y+1] = true;
	if(x+2 < size && y-1 >= 0) board[x+2][y-1] = true;
	
	if(x-2 < size && y+1 < size) board[x-2][y+1] = true;
	if(x-2 < size && y-1 >= 0) board[x-2][y-1] = true;
}

void king (char color, int x, int y, int size, bool ** &board){
	if(x+1 < size) board[x+1][y] = true;
	if(x-1 >= 0) board[x-1][y] = true;
	if(y+1 < size) board[x][y+1] = true;
	if(y-1 >= 0) board[x][y-1] = true;
	
	if(x+1 < size && y+1 < size) board[x+1][y+1] = true;
	if(x+1 < size && y-1 >= 0) board[x+1][y-1] = true;
	if(x-1 >= 0 && y-1 >= 0) board[x-1][y-1] = true;
	if(x-1 >= 0 && y+1 < size) board[x-1][y+1] = true;
}

void queen(char color, int x, int y, int size, bool ** &board){
	for(int i = 0; i < size; i++) board[i][y] = true;
	for(int i = 0; i < size; i++) board[x][i] = true;
	
	for(int i = 0; i < size; i++){
		if(x+i >= size || y+i >= size) break;
		board[x+i][y+i] = true;
	}
	
	for(int i = 0; i < size; i++){
		if(x-i < 0 || y+i >= size) break;
		board[x-i][y+i] = true;
	}
	
	for(int i = 0; i < size; i++){
		if(x-i < 0 || y-i < 0) break;
		board[x-i][y-i] = true;
	}
	
	for(int i = 0; i < size; i++){
		if(x+i >= size || y-i < 0) break;
		board[x+i][y-i] = true;
	}
}

void pawn(char color, int x, int y, int size, bool ** &board){
	if(color == 'b'){
		if(x+1 < size) board[x+1][y] = true;
	}else{
		if(x-1 >= 0) board[x-1][y] = true;
	}
}
void move(char color, char chessmen, int x, int y, int size, bool ** &board){
	switch(chessmen){
		case 'w': rook(color, x, y, size, board); break; //wie¿a
		case 'g': bishop(color, x, y, size, board); break; //goniec
		case 's': knight(color, x, y, size, board); break; // skoczek
		case 'k': king(color, x, y, size, board); break; //król
		case 'h': queen(color, x, y, size, board); break; //hetman
		case 'p': pawn(color, x, y, size, board); break; //pion
	}
}

int main(){
	//Zmienne
	int size = 8; 
	int x;
	int y;
	
	char color;
	char chessmen;
	
	bool ** board = new bool * [size];

	for(int i = 0; i < size; i++){
		board[i] = new bool[size];
	}
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			board[i][j] = false;
		}
	}
	
	//Wczytywanie danych
	cout << "Podaj kolor figury: ";
	cin >> color;
	
	cout << "Podaj wspolrzedne x, y (oddziel spacja) (1-8): ";
	cin >> x >> y;
	
	cout << "Podaj figure (w - wieza, g - goniec, s - skoczek, k - krol, h - hetman, p - pion): ";
	cin >> chessmen;
	
	if(x < 1 || x > 8 || y < 1 || y > 8){cout << "Bledne dane!" << endl; system("pause"); return 0;}
	
	//Zmniejszamy wspó³rzêdne tak aby pasowa³y do indeksu tablicy
	x--;
	y--;
	
	
	move(color, chessmen, x, y, size, board);
	
	saveBoard(color, chessmen, x, y, size, board);
	
	cout << "Plansza zostala zapisana w pliku szachy.txt!" << endl;
	
	system("pause");
	return 0;
}

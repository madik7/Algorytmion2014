/* Zadanie 5, C++, GCC 4.7.1 */

#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

//Funkcje obliczaj¹ce x, y
double getX(double r, double t){
	return r*(t - sin(t));
}

double getY(double r, double t){
	return r*(1 - cos(t));
}

int main(){
	
	double r, length;
	double x1 = 0,x2,y1 = 0,y2; //wspó³rzêdne po³o¿enia muchy
	double t = 0;
	double result = 0;
	
	cout << "Podaj promien kola: ";
	cin >> r;
	
	cout << "Podaj dlugosc przejechanej drogi: ";
	cin >> length;
	
	while(x1 < length){
			x2 = getX(r, t);
			y2 = getY(r, t);
			
			result += sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
			
			x1 = x2;
			y1 = y2;
			
			t+=0.01; //zwiêkszenie k¹ta o sta³¹ wartosæ 0.01 rad
	}
	cout << result << endl;
	
	system("pause");
	return 0;
}

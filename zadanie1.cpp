/* Zadanie 1, C++, GCC 4.7.1 */

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//Polskie znaki
string PL( const char * text )
{
    string result;
    for(; * text; text++ )
    switch( * text )
    {
    case 'π': result += static_cast < char >( 0xa5 ); break;
    case 'Ê': result += static_cast < char >( 0x86 ); break;
    case 'Í': result += static_cast < char >( 0xa9 ); break;
    case '≥': result += static_cast < char >( 0x88 ); break;
    case 'Ò': result += static_cast < char >( 0xe4 ); break;
    case 'Û': result += static_cast < char >( 0xa2 ); break;
    case 'ú': result += static_cast < char >( 0x98 ); break;
    case 'ø': result += static_cast < char >( 0xbe ); break;
    case 'ü': result += static_cast < char >( 0xab ); break;
    case '•': result += static_cast < char >( 0xa4 ); break;
    case '∆': result += static_cast < char >( 0x8f ); break;
    case ' ': result += static_cast < char >( 0xa8 ); break;
    case '£': result += static_cast < char >( 0x9d ); break;
    case '—': result += static_cast < char >( 0xe3 ); break;
    case '”': result += static_cast < char >( 0xe0 ); break;
    case 'å': result += static_cast < char >( 0x97 ); break;
    case 'Ø': result += static_cast < char >( 0xbd ); break;
    case 'è': result += static_cast < char >( 0x8d ); break;
        default: result += * text; break;
    }
     return result;
}

//Funkcje sprawdzajπce wpisywane dane

bool yearValidate(int year){
	//przyjmujemy podany rok jeøeli miesci siÍ w przedziale: 1900 - 2299
	if( year >= 1900 && year <= 2299 ) return true; else return false;
	
}

bool isLeapYear(int year){
	if((year%4 == 0 && year%100 != 0) || year%400 == 0) return true; else return false;
}

bool monthValidate(string month, int &monthInt){
	if(month == "StyczeÒ" || month == "styczeÒ" || month == "Styczen" || month == "styczen" || month == "1"){ monthInt = 1; return true;}
	else if(month == "Luty" || month == "luty" || month == "2"){  monthInt = 2; return true;}
	else if(month == "Marzec" || month == "marzec" || month == "3"){  monthInt = 3; return true;}
	else if(month == "KwiecieÒ" || month == "kwiecieÒ" || month == "Kwiecien" || month == "kwiecien" || month == "4"){  monthInt = 4; return true;}
	else if(month == "Maj" || month == "maj" || month == "5"){  monthInt = 5; return true;}
	else if(month == "Czerwiec" || month == "czerwiec" || month == "6"){  monthInt = 6; return true;}
	else if(month == "Lipiec" || month == "lipiec" || month == "7"){  monthInt = 7; return true;}
	else if(month == "SierpieÒ" || month == "sierpieÒ" || month == "Sierpien" || month == "sierpien" || month == "8"){  monthInt = 8; return true;}
	else if(month == "WrzesieÒ" || month == "wrzesieÒ" || month == "Wrzesien" || month == "wrzesien" || month == "9"){  monthInt = 9; return true;}
	else if(month == "Paüdziernik" || month == "paüdziernik" || month == "Pazdziernik" || month == "pazdziernik" || month == "10"){  monthInt = 10; return true;}
	else if(month == "Listopad" || month == "listopad" || month == "11"){  monthInt = 11; return true;}
	else if(month == "GrudzieÒ" || month == "grudzieÒ" || month == "Grudzien" || month == "grudzien" || month == "12"){  monthInt = 12; return true;}
	else return false;
}

bool dayValidate(int day, int monthInt, int year){
	if(day > 0){
		switch(monthInt){
			case 1: { if(day <= 31) return true; break;}
			case 2:	{ if(isLeapYear(year)){ if(day <= 29) return true; } else if(day <= 28) return true; break;}
			case 3: { if(day <= 31) return true; break;}
			case 4: { if(day <= 30) return true; break;}
			case 5: { if(day <= 31) return true; break;}
			case 6: { if(day <= 30) return true; break;}
			case 7: { if(day <= 31) return true; break;}
			case 8: { if(day <= 31) return true; break;}
			case 9: { if(day <= 30) return true; break;}
			case 10: { if(day <= 31) return true; break;}
			case 11: { if(day <= 30) return true; break;}
			case 12: { if(day <= 31) return true; break;}
		}
	}
	return false;
}

bool sexValidate(char sex){
	if(sex == 'k' || sex == 'm') return true; else false;
}

//Funkcje odpowiedzialne za konwersje

string intToString(int intValue){
	ostringstream ss;
	ss << intValue;
	string stringValue = ss.str();
	return stringValue;
}

int stringToInt(string stringValue){
	int intValue;
	istringstream iss(stringValue);
	iss >> intValue;
	return intValue;
}

int charToInt(char charValue){
	return (charValue - '0');
}

//Funkcje odpowiedzialne za operacje na pliku

void saveDatabase(vector <string> &database){
	ofstream databaseFile;
	databaseFile.open("pesel.txt");
	
	vector<string>::iterator it;
   	
	for( it=database.begin(); it!=database.end(); ++it ) databaseFile << *it << endl;
	
	databaseFile.close();
}

void getDatabase(vector <string> &database){
	ifstream databaseFile;
	databaseFile.open("pesel.txt");
	
	string tmp;
	while(databaseFile >> tmp)	database.push_back(tmp);
	
	databaseFile.close();
}

//Operacje na string
bool compareString(string value1, string value2, int length){
	for(int i=0; i<length; i++) if(value1[i] != value2[i]) return false;
	return true;
}

string addZero(int value, int length){
	string result;
	for(int i = 0; i < length; i++){
		int digit = 0;
		if(value != 0){
			digit = value % 10;
			value /= 10;
		}
		result.push_back(digit + '0');
	}
	reverse(result.begin(), result.end());
	return result;
}

//Funkcja exit();
bool exit(vector <string> &database){
	char key;
	cout << PL("Czy chcesz dokonaÊ kolejnego wpisu? Klawisz t - tak, pozosta≥e - nie: ");
	cin.ignore();
	key = getchar();
	
	
	if(key == 't') return true; 
	saveDatabase(database);
	return false;
}

void insertPesel(string pesel, vector <string> &database){
	//vector
    vector <string> correctDatabase;
	//Jesli vector database jest pusty, nie ma sensu dalszy kod, a wiÍc dodajemy odrazu pesel na koniec vectora
	if(database.empty()){correctDatabase.push_back(pesel);}else{
	
		vector <string>::iterator it;
		//bool
		bool isInsert = false;
		//string pesel
		string peselYear = pesel.substr(0,2);
		string peselMonth = pesel.substr(2,2);
		string peselDay = pesel.substr(4,2);
		string peselSerialNumber = pesel.substr(6,4);    	
	    //int pesel
		int peselYearInt = stringToInt(peselYear);
		int peselMonthInt = stringToInt(peselMonth);
		int peselDayInt = stringToInt(peselDay);
		int peselSerialNumberInt = stringToInt(peselSerialNumber);
		
		if(peselMonthInt >= 1 && peselMonthInt <= 12) peselYearInt += 1900;
		else if(peselMonthInt >= 21 && peselMonthInt <= 32) peselYearInt += 2000;
		else if(peselMonthInt >= 41 && peselMonthInt <= 52) peselYearInt += 2100;
		else if(peselMonthInt >= 61 && peselMonthInt <= 72) peselYearInt += 2200;	
	   	
		for( it=database.begin(); it!=database.end(); ++it ){
			
			//string tmp
			string tmp = *it;
			string tmpYear = tmp.substr(0,2);
			string tmpMonth = tmp.substr(2,2);
			string tmpDay = tmp.substr(4,2);
			string tmpSerialNumber = tmp.substr(6,4);
			//int tmp
			int tmpYearInt = stringToInt(tmpYear);
			int tmpMonthInt = stringToInt(tmpMonth);
			int tmpDayInt = stringToInt(tmpDay);
			int tmpSerialNumberInt = stringToInt(tmpSerialNumber);
			
			if(tmpMonthInt >= 1 && tmpMonthInt <= 12) tmpYearInt += 1900;
			else if(tmpMonthInt >= 21 && tmpMonthInt <= 32 )tmpYearInt += 2000;
			else if(tmpMonthInt >= 41 && tmpMonthInt <= 52) tmpYearInt += 2100;
			else if(tmpMonthInt >= 61 && tmpMonthInt <= 72) tmpYearInt += 2200;
			
			if((tmpYearInt <= peselYearInt) && (tmpMonthInt <= peselMonthInt) && (tmpDayInt <= peselDayInt)){
				if((tmpYearInt == peselYearInt) && (tmpMonthInt == peselMonthInt)&& (tmpDayInt == peselDayInt)){
					if(tmpSerialNumberInt <= peselSerialNumberInt){
						
					} else  { if(!isInsert){ isInsert = true; correctDatabase.push_back(pesel); }}
				}
				
			} else { if(!isInsert){ isInsert = true; correctDatabase.push_back(pesel); }}
			
			correctDatabase.push_back(tmp);
	
	   	}
   		if(!isInsert) correctDatabase.push_back(pesel);
   	}
   	
	database.swap(correctDatabase);

}

string serialNumber(string value, char sex, vector <string> &database){
	string result;
	bool flag = false;
	
	if(sex == 'k') result = "0000"; else result = "0001";
	vector<string>::iterator it;
   	for( it=database.begin(); it!=database.end(); ++it ){
    	string tmp;
		tmp = *it;
    	int sexInt = charToInt(tmp[9]);
		if(compareString(tmp, value, 6)){
			if(sex == 'k' && sexInt%2 == 0) { flag = true; result = tmp.substr(6,4); }
			if(sex == 'm' && sexInt%2 == 1) { flag = true; result = tmp.substr(6,4); }
		}
   	}
   	int intSerialNumber = stringToInt(result);
	if(flag) intSerialNumber += 2;	
	return addZero(intSerialNumber, 4);
}

string newPesel(int year, int monthInt, int day, char sex, vector <string> &database){
	string pesel;
	string yearString;
	string monthString;
	string dayString;
	
	if(year >= 2000 && year <= 2099) monthInt += 20;
	else if(year >= 2100 && year <= 2199) monthInt += 40;
	else if(year >= 2200 && year <= 2299) monthInt += 60;
	
	yearString = intToString(year);
	
	monthString = addZero(monthInt, 2);
	dayString = addZero(day, 2);
	
	pesel.push_back(yearString[2]);
	pesel.push_back(yearString[3]);
	
	pesel.push_back(monthString[0]);
	pesel.push_back(monthString[1]);
	
	pesel.push_back(dayString[0]);
	pesel.push_back(dayString[1]);
	
	string serialNumberString = serialNumber(pesel, sex, database);
	pesel.append(serialNumberString);

	int weight[10] = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
	int checksum = 0;
	for(int i = 0; i < 10; i++){
		checksum += weight[i] * charToInt(pesel[i]);
	}
	char checksumChar = (checksum%10) + '0';
	pesel.push_back(checksumChar);
	
	return pesel;
}

void putPesel(int year, int monthInt, int day, char sex, vector <string> &database){
	string pesel;
	pesel = newPesel(year, monthInt, day, sex, database);
	insertPesel(pesel, database);
}

int main(){
	//zmienne
	int year;
	int monthInt;
	int day;
	
	char key;
	char sex;
	
	string month;
	
	bool flag = false;
	bool repeat = false;
	
	vector <string> database;

	getDatabase(database);
	
	while(true){
	//a.
	do{
		cout << PL("Podaj czterocyfrowy rok urodzenia, np. 1993") << endl;
		cin >> year;
		if(!yearValidate(year)){
			cout << PL("Poda≥eú z≥π formÍ roku, wciúnij p jeúli chcesz podaÊ ponownie rok lub wciúnij inny klawisz jeúli chcesz zakoÒczyÊ: ");
			cin.ignore();
			key = getchar();
			if(key == 'p') flag = true; else { if(exit(database)){ repeat = true; continue;} else return 0; }
		} else flag = false;
	}while(flag);
	if(repeat){ repeat = false; continue; }
	
	//b.
	do{
		cout << PL("Podaj miesiπc urodzenia, np. czerwiec albo 6") << endl;
		cin >> month;
		if(!monthValidate(month, monthInt)){
			cout << PL("Poda≥eú z≥π formÍ miesiπca, wciúnij p jeúli chcesz podaÊ ponownie miesiπc lub wciúnij inny klawisz jeúli chcesz zakoÒczyÊ: ");
			cin.ignore();
			key = getchar();
			if(key == 'p') flag = true; else { if(exit(database)){ repeat = true; continue;} else return 0; }
		} else flag = false;
	}while(flag);
	if(repeat){ repeat = false; continue; }
	
	//c.
	do{
		cout << PL("Podaj numer dnia miesiπca urodzenia, np. 23") << endl;
		cin >> day;
		if(!dayValidate(day, monthInt, year)){
			cout << PL("Poda≥eú z≥y numer, wciúnij p jeúli chcesz podaÊ ponownie numer dnia lub wciúnij inny klawisz jeúli chcesz zakoÒczyÊ: ");
			cin.ignore();
			key = getchar();
			if(key == 'p') flag = true; else { if(exit(database)){ repeat = true; continue;} else return 0; }
		} else flag = false;
	}while(flag);
	if(repeat){ repeat = false; continue; }
	
	//d.
	do{
		cout << PL("Podaj p≥eÊ: wciúnij k jeúli jesteú kobietπ albo m jeúli jesteú mÍøczyznπ.") << endl;
		cin >> sex;
		if(!sexValidate(sex)){
			cout << PL("Poda≥eú niepoprawnπ formÍ p≥ci,wciúnij p jeúli chcesz podaÊ ponownie p≥eÊ lub wciúnij inny klawisz jeúli chcesz zakoÒczyÊ: ");
			cin.ignore();
			key = getchar();
			if(key == 'p') flag = true; else { if(exit(database)){ repeat = true; continue;} else return 0; }
		} else flag = false;
	}while(flag);
	if(repeat){ repeat = false; continue; }
	
	//e.
	do{
		cout << PL("Czy chcesz dokonaÊ wpisu ") << year << ", " << month << ", " << day << ", " << sex << PL("? Klawisz tñtak,pozosta≥eñnie") << endl;
		cin.ignore();
		key = getchar();
		if(key == 't') flag = false; else { if(exit(database)){ repeat = true; continue;} else return 0; }
	}while(flag);
	if(repeat){ repeat = false; continue; }
	
	putPesel(year, monthInt, day, sex, database);

	//f.
	if(exit(database)) continue; else return 0; 

	}
	
	system("pause");
	return 0;
}



#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
	double d = 1.234;
	cout << " Nr Oct  Hex String  Fixed     Scientific " << endl;
	for (int k = 1; k < 11; k++)
	{
		cout << setw(3) << dec << k; //Dezimalzahl und soll 3 Zeichen Abstand haben zur linken Seite
		cout << showbase << oct << setw(4) << k; //Immer mit 0 angezeigt werden, da Oktalzahl, deshalb showbase
		cout << right << setw(5) << hex <<  k <<  noshowbase << " "; //showbase bleibt solange im Code bis man es entfernt, deshalb hex auch mit 0x angezeigt
		cout << left << setw(7) <<  setfill('+') << string(k % 5 + 1, '*')  << " "; //linksbündig und mit + auffüllen
		cout << internal << fixed <<setprecision(3) << setw(9)<<  setfill(' ')<< showpos  << d << noshowpos ; //internal Ausrichtung nach Vorzeichen und showpos für zeigen positives Vorzeichen
		cout << right << setw(11) << scientific << uppercase << d << nouppercase << " "; //wissenschaftliches Format mit Exponenten
		d = d*-2;
		
		cout << endl;
	}
	return 0;
}


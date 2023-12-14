
#include <iostream>
#include <string>
using namespace std;

class A {
public:
	void method_1() {
		cout << "A::method_1()" << endl;
	}
	void method_2(double d) {
		cout << "A::method_2(double)" << endl;
	}
	void method_2(string s) {
		cout << "A::method_2(string)" << endl;
	}
	void method_3(char c) {
		cout << "A::method_3(char)" << endl;
	}
	void method_3(string s) {
		cout << "A::method_3(string)" << endl;
	}
};

class B : public A {
public:
	void method_2(int i) {
		cout << "B::method_2(int)" << endl;
	}
	void method_3(int i) {
		cout << "B::method_3(int)" << endl;
	}
	void method_3(string s) {
		cout << "B::method_3(string)" << endl;
	}
};

int main(int argc, char *argv[]) {
	A a;
	B b;
	cout << "a.method_1() ";
	a.method_1();		// a) keine Fehlermeldung;	b) Ausgabe: a.method_1(): A::method_1()
	cout << "b.method_1() ";
	b.method_1();		// a)keine Fehlermeldung, da die method_1() nicht überschrieben wurde in Class B, da es keine solche Methode gibt in Class B
	                    // b)Ausgabe: b.method_1(): A::method_1()
	cout << "a.method_2(1.2) ";
	a.method_2(1.2);	//a)keine Fehlermeldung; b)A::method_2(double)
	cout << "b.method_2(1.2) ";
	b.method_2(1.2);	//a)keine Fehlermeldung, da die Funktion method_2 in Class B einen Integer Wert, statt einem Double erwartet
	                    //b)"A::method_2(double)"
	cout << "a.method_2(1) ";
	a.method_2(1);		//a)keine Fehlermeldung, da der int wert implizit in einen double wert umgewandelt werden kann
	                    //b)"A::method_2(double)"
	cout << "b.method_2(1) ";
	b.method_2(1);		//a)keine Fehlermeldung, da in Class B eine Methode mit passendem int Parameter vorhanden ist
	                    //b)"B::method_2(int)"
	cout << "a.method_2('c') ";
	a.method_2('c');    //a)keine Fehlermeldung, da implizit in double umgewandelt werden kann
	                    //b)A::method_2(double)
	cout << "b.method_2('c') ";
	b.method_2('c');	//a)keine Fehlermeldung, da implizit in int umgewandelt werden kann
	                    //b)B::method_2(int)
	cout << "a.method_2(''string'') ";
	a.method_2("string");//a)keine Fehlermeldung b)A::method_2(string)	
	cout << "b.method_2(''string'') ";
	//b.method_2("string"); //a)Fehlermeldung, da keine fähige Methode in Class B mit string Übergabeparamter, gleichnamige geerbete Methode aus Class A
	                      //nicht mehr aufrufbar, da überschrieben wurde
	cout << "a.method_3(1) ";
	a.method_3(1);    //a)keine Fehlermeldung da implizit in char umgewandelt werden kann
	                  //b)A::method_3(char)
	cout << "b.method_3(1) ";
	b.method_3(1);		//a)keine Fehlermeldung, b)B::method_3(int)
	cout << "a.method_3('c') ";
	a.method_3('c'); //a)keine Fehlermeldung, b)A::method_3(char)	
	cout << "b.method_3('c') ";
	b.method_3('c');    //a)keine Fehlermeldung b)B::method_3(string)
	cout << "a.method_3(''string'') ";
	a.method_3("string");//a)keine Fehlermeldung,b)A::method_3(string)
	cout << "b.method_3(''string'') ";
	b.method_3("string");	//a)keine Fehlermeldung, bB::method_3(string)
	return 0;
}

//Aufgabe c)
//Funktion      | überlädt, verdeckt oder redefiniert.| Funktion
//void method_2("string") aus class B   verdeckt          void method_2(string) aus Klasse A---------
//void method_2(double d) aus class A   überladt          void method_2(string s) aus class A
//void method_3(string s) aus class B   redefiniert       void method_3(string s) aus class A
//



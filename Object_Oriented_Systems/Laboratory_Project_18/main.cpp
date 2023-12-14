
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Klasse für alle Personen, die Medien leihen können aus Aufgabe 10
class Person {
	string _name;
	int _check_out_duration;
public:
	Person(string name, int check_out_duration = 0);
	int get_check_out_duration() const;
    string get_name() const;
	void print() const;
};

Person::Person(string name, int check_out_duration)
	:_name(name)
	, _check_out_duration(check_out_duration)
{
}

int Person::get_check_out_duration() const
{
	return  _check_out_duration;
}

string Person::get_name() const {
    return _name;
}

void Person::print() const
{
	cout << _name;
}

class Lecturer : public Person
{
	int _examiner_id;
public:
	Lecturer(string name, int examiner_id);
	void print() const;
};

Lecturer::Lecturer(string name, int examiner_id)
	: Person(name, 90)
	, _examiner_id(examiner_id)
{
}

void Lecturer::print() const
{
	Person::print();
	cout << ", _examiner_id " << _examiner_id << endl;
}

class Student : public Person
{
	int _matriculation_number;

public:
	Student(string name, int matriculation_number);
	void print() const;
};


Student::Student(string name, int matriculation_number)
	: Person(name, 30)
	, _matriculation_number(matriculation_number)
{
}

void Student::print() const
{
	Person::print();
	cout << ", Matrikelnummer " << _matriculation_number << endl;
}




// Klasse Datum aus Aufgabe 9
class Date {
	
	int _day, _month, _year;

public:
	Date(int = 0, int = 0, int = 0);
    // ** neu **
    // Konvertierkonstruktor für String neu
    Date(const string &); //datentyp reicht hier aus kein Parametername notwendig, const da 
    // ** neu **          //übergebene Zeichenkette nicht verändert werden soll, nur Daten extrahieren
    // Konvertierkonstruktor für C-String neu
    Date(const char *);
	Date operator+(int days);
	friend ostream & operator<<(ostream &, const Date &);
};


Date::Date(int d, int m, int y)
	: _day(d), _month(m), _year(y)
{
}

// hier Konvertierkonstruktor für String
Date::Date(const string& date_str){ //String Parameter als Referenz übergeben
     stringstream ss(date_str); //stringstream, man kann Daten rausziehen aus dem String oder auch hinzufügen

    // Extrahieren von Tag, Monat und Jahr aus dem String
    ss >> _day;
    ss.ignore();  // Ignorieren des Trennzeichens, also Punkt
    ss >> _month;
    ss.ignore();  
    ss >> _year;
}
// hier Konvertierkonstruktor für C-String
Date::Date(const char *date_char) {
     stringstream ss(date_char);

    ss >> _day;
    ss.ignore(); 
    ss >> _month;
    ss.ignore();  
    ss >> _year;
}

Date Date::operator+(int days)
{
	int abs_date = _day + _month * 30 + _year * 360;
	abs_date += days;
	int y = abs_date / 360;
	abs_date = abs_date % 360;
	int m = abs_date / 30;
	abs_date = abs_date % 30;
	int d = abs_date;

	return Date(d, m, y);
}

ostream& operator<<(ostream& os, const Date& d)
{
	os << d._day << "." << d._month << "." << d._year;
	return os;
}




// Klasse für die Medien, die in der Bibliothek ausgeliehen werden
// können
class Medium
{

protected:
    // Titel des Mediums
    const string _title;
    // Verlag, der das Medium herausgibt
    const string _publisher;
    // Jahr, in dem das Medium veröffentlicht wurde
    const int _year_of_publication;
    // ausgeliehen am
    Date _date_of_check_out;
    // ausgeliehen bis
    Date _date_of_return;
    // ausgeliehen von
    Person *_lender;

public:
    // Konstruktor
    Medium(string title = "", string publisher = "", int year_of_publication = 0);
    virtual ~Medium();
    // Titel zurückliefern
    string get_title() const;
    // Ausleiher zurückliefern
    Person *get_lender() const;
    // das Medium "ausleihen", d.h. Person p, date_of_check_out und date_of_return eintragen
    void check_out(Person &p, Date date_of_check_out, Date date_of_return);
    // Medium in der Konsole ausgeben
    virtual void print() const;
    virtual Medium *clone() const; //Ziel tiefe Kopie eines Objektes zu erstellen und Polymorphie zu ermöglichen, da viele abgeleitete Klassen, nützlich wenn Objekte verschiedener Klassen über gemeinsamen Zeigertyp (hier Medium) behandeln will
};

// hier Konstruktor und Methoden
Medium::Medium(string title, string publisher, int year_of_publication) : _title(title), _publisher(publisher), _year_of_publication(year_of_publication) {
    _lender = nullptr;
}

Medium::~Medium(){}

void Medium::print() const {
    cout << "Titel:         " << _title << endl;
    cout << "Verlag:        " << _publisher << endl;
    cout << "Jahr:          " << _year_of_publication << endl;
    cout << "Ausleiher:     ";
    if (_lender != nullptr) {
        _lender->print(); //je nachdem ob lender auf Objekt der Klasse Student, Lecturer oder Person zeigt wird diese Methode aus der Klasse aufgerufen
        cout << " von: " << _date_of_check_out << " bis: " << _date_of_return;
    } else {
        cout << "-";
    }
    cout << endl;
} 

string Medium::get_title() const {
    return _title;
}

Person* Medium::get_lender() const {
    return _lender;
}

Medium* Medium::clone() const {
    return new Medium(*this);
}

void Medium::check_out(Person&p, Date date_of_check_out, Date date_of_return) {
    _lender = &p;
    _date_of_check_out = date_of_check_out;
    _date_of_return = date_of_return;
}




// Klasse für die Bücher als Spezialisierung von Medium
class Book : public Medium
{
    // Autor(en) des Buches
    string _author;

public:
    // Standardkonstruktor
    Book(string author = "", string title = "", string publisher = "", int year_of_publication = 0);
    // das Buch auf der Konsole ausgeben
    void print() const;
    Medium *clone() const override; //clone Methode von Medium wird hier überschrieben
};

// hier Konstruktor und Methoden
Medium* Book::clone() const { //Kopiekonstruktor von Book wird aufgerufen und eine tiefe Kopie von Book erstellt
    return new Book(*this); //Rückgabe als Zeiger auf Medium, da Book eine spezialisierte Form von Medium ist
}

Book::Book(string author, string title, string publisher, int year_of_publication): Medium(title, publisher, year_of_publication), _author(author){

}

void Book::print() const {
    cout << "Autor:         " << _author << endl;
    Medium::print();
    cout << endl;
     
}





// Klasse für die DVDs als Spezialisierung von Medium
class DVD : public Medium
{
    // Abspieldauer der DVD
    const int _c_play_time;

public:
    // Standardkonstruktor
    DVD(string title = "", string publisher = "", int year_of_publication = 0, int play_time = 0);

    // die DVD auf der Konsole ausgeben
    void print() const;
    Medium *clone() const override;
};

// hier Konstruktor und Methoden
DVD::DVD(string title, string publisher, int year_of_publication, int play_time): Medium(title, publisher, year_of_publication), _c_play_time(play_time){

}

Medium* DVD::clone() const {
    return new DVD(*this);
}

void DVD::print() const{
    Medium::print();
    cout << "Dauer:         " << _c_play_time << endl;
    cout << endl;
}



// Die Klasse Library verweist auf alle Medien (Bücher und DVDs),
// die von Personen (Studierende und Dozenten) ausgeliehen werden
// können.
class Library
{
    // maximale Anzahl der Medien im Katalog
    const unsigned int _c_maximal_number_of_media;
    // Der Medienkatalog
    vector<Medium*> media;

public:
    // Standardkonstruktor
    Library(int maximal_number_of_media = 1000);

    // Kopie einer DVD oder eines Buches in den Katalog der Bibliothek eintragen
    // Die maximale Anzahl an Medien darf nicht überschritten werden
    void procure_medium(Medium &); //Kopie also z.B von Book welche durch Medium* Book::clone() const{return new Book(*this);} erstellt wurde wird hier aufgerufen

    // alle Medien auf der Konsole ausgeben,
    // die im Titel das Suchwort enthalten
    void search_medium(string search_word);

    // im Medium mit der Nummer number, die Person p als Ausleiher
    // eintragen mit von-Datum d und bis-Datum d+p.ausleihdauer
    void check_out_medium(int number, Person &p, Date d);

    // alle Medien in der Konsole ausgeben
    void print() const;
};

// hier Konstruktor und Methoden
void Library::print()const {
    cout << endl;
    cout << "Bibliothekskatalog:" << endl;
    cout << "---------------------------------------" << endl << endl;
     for (unsigned int i = 0; i < media.size(); i++) { //hier geht man den Vektor durch und printet dann das Objekt worauf media am Index i zeigt, also ruft dessen Print Funktion auf
        cout << "Medium " << i << ":" << endl;
        media[i]->print();
    }
    cout << "---------------------------------------" << endl;
}

Library::Library(int c_maximal_number_of_media): _c_maximal_number_of_media(c_maximal_number_of_media){

}

void Library::procure_medium(Medium& m){
    if(media.size() != static_cast<unsigned int>(_c_maximal_number_of_media)){ //nur hinzufügen, wenn media size ungleich maximal number of media ist
        media.push_back(m.clone()); //hier wird dann am Ende nochmal ein neues geklontes Objekt hinzugefügt
    }
}

void Library::search_medium(string search_word){
    cout << endl;
    cout << "Suche nach \"" << search_word << "\" Ergebnis:" << endl;
    cout << "---------------------------------------" << endl << endl;
    for (unsigned int i = 0; i < media.size(); i++) {
        if (media[i]->get_title().find(search_word) != string::npos) {
            cout << "Medium " << i << ":" << endl;
            media[i]->print();
        }
    }
    cout << "---------------------------------------" << endl;
}

void Library::check_out_medium(int number, Person &p, Date d){
     media[number]->check_out(p, d, d + p.get_check_out_duration());
}


int main(int argc, char *argv[]) 
{
    // Umlaute etc. in der Konsole zulassen
    setlocale(LC_ALL, "");
    // Bibliothek mit 100 Plätzen initialisieren
    Library library(100);
    // Bücher und DVDs erstellen
    Book b1("U. Breymann", "C++ - Eine Einführung", "Hanser", 2016);
    Book b2("U. Breymann", "Der C++ Programmierer", "Hanser", 2017);
    Book b3("Rainer Grimm", "C++20, Get the details", "Leanpub", 2021);
    Book b4("Bartłomiej Filipek", "C++17 in detail", "Leanbub", 2018);
    Book b5("Timothy Gallwey", "The Inner Game of Tennis", "Pan", 2015);
    Book b6("Brad Gilbert", "Winning Ugly – Mentale Kriegsführung im Tennis", "riva", 2021);
    DVD d1("The IT Crowd", "2entertain", 2016, 600);
    DVD d2("Mr. Robot", "Universal Pictures UK", 2020, 2106);
    DVD d3("Chuck", "Warner Bros (Universal Pictures)", 2013, 3774);
    // Ein Buch und eine DVD ausgeben
    b1.print();
    d1.print();
    // Kopien der Bücher und DVDs (Medien) in die Bibliothek
    // einfügen
    library.procure_medium(b1);
    library.procure_medium(b2);
    library.procure_medium(b3);
    library.procure_medium(b4);
    library.procure_medium(b5);
    library.procure_medium(b6);
    library.procure_medium(d1);
    library.procure_medium(d2);
    library.procure_medium(d3);
    // Bestand der Bibliothek ausgeben
    library.print();
    // Personen anlegen
    Student p1("Peter", 12345678);
    Student p2("Lisa", 87654321);
    Lecturer p3("Prof Miller", 4711);
    // Suchen im Bibliotheksbestand durchführen
    library.search_medium("C++");
    library.search_medium("Tennis");
    library.search_medium("The");
    // Medien ausleihen
    library.check_out_medium(1, p1, "4.5.2023");
    library.check_out_medium(7, p2, "25.05.2023");
    library.check_out_medium(4, p3, "12.10.2023");
    // Bestand der Bibliothek ausgeben
    library.print();
}


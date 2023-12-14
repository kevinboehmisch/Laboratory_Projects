#include <string>
#include <iostream>
using namespace std;

// Klasse Student
class Student{
//Attribute Privat setzen, da diese geschützt werden sollen
private:
    string _name;
    string _first_name;

public:
    //öffentliche Methoden notwendig, sodass auf die Member Variablen
    //auch von außerhalb zugegriffen werden kann
    string getName() const{
        return _name;
    }
    string getFirstName() const{
        return _first_name;
    }

    // Parametrisierter Konstruktor für die Klasse Student
    //Es werden die Parameter Name und Vorname des Typs String übergeben
    Student(string name, string vorname);

    // Druckmethoden für die Klasse Student
    void print();
    void print(bool wahr);

    // Destruktor für die Klasse Student
    ~Student();
};

// Definition der Methoden für die Klasse Student außerhalb der Klasse
// Student:: um außerhalb darauf zugreifen zu können

//Parametrisierter Konstruktor außerhalb
Student::Student(string name, string vorname){
    _name = name;
    _first_name = vorname;
    cout << "Parametrisierter Konstruktor Student: " << _first_name << " " << _name << endl;
}

// print zur Ausgabe mit Zeilenumbruch am Ende
void Student::print(){
    cout << "print() ohne Parameter; Student: " << _first_name << " " << _name << endl;
}

// print zur Ausgabe mit oder ohne Zeilenumbruch am Ende, abhängig von bool Wert
void Student::print(bool wahr){
    if(wahr){
        cout << "print() mit Parameter; Student: " << _first_name << " " << _name << endl;
    }
    else{
        cout << "print() mit Parameter; Student: " << _first_name << " " << _name;
    }
}

//Destruktor außerhalb der Klasse
Student::~Student(){
    cout << "Destruktor Student: " << _first_name << " " << _name << endl;
}


// Klasse Employee
class Employee{
//Attribute Privat setzen, da diese geschützt werden sollen
private:
    string _name;
    string _first_name;

public:
    // Öffentliche Methoden, um auf die Mitgliedsvariablen zuzugreifen
    string getName() const {
        return _name;
    }
    string getFirstName() const {
        return _first_name;
    }
    //Parametrisierter Konstruktor für Employee
    Employee(string name, string vorname): _name(name), _first_name(vorname){
        cout << "Parametrisierter Konstruktor Employee: " << _first_name << " " << _name << endl;
    }
    //Konvertierungskonstruktor Employee
    //Durch & werden die Werte als Referenz übergeben
    //sodass das alte Objekt nicht seinen Gültigkeitsbereich verlässt oder gelöscht wird und den Destruktor aktiviert
    Employee(Student &student): _name(student.getName()), _first_name(student.getFirstName()){
        cout << "Konvertierungskonstruktor Employee: " << _first_name << " " << _name << endl;
    }

    // Standardkonstruktor für die Klasse Employee
    // Standarkonstruktor delegiert zu Parametrisierten Konstruktor der zwei String Werte erwartet
    Employee(): Employee("Mustermann","Erika"){
        cout << "Standardkonstruktor Employee: " << _first_name << " " << _name << endl;
    }

    // print Methode mit Zeilenumbruch
    void print(){
        cout << "print() ohne Parameter; Mitarbeiter: " << _first_name << " " << _name << endl;
    }
    // print Methode zur Ausgabe mit oder ohne Zeilenumbruch
    void print(bool wahr){
        if(wahr){
            cout << "print() mit Parameter; Employee: " << _first_name << " " << _name << endl;
        }
        else{
            cout << "print() mit Parameter; Employee :" << _first_name << " " << _name;
        }
    }

    // Destruktor für die Klasse Employee
    ~Employee(){
        cout << "Destruktor Employee: " << _first_name << " " << _name << endl;
    }
};


int main(int argc, char *argv[])
{
    Student stud_mustermann = Student("Mustermann", "Max");
    Employee empl_mustermann = Employee(stud_mustermann);
    Employee mit_default = Employee();
    stud_mustermann.print();
    stud_mustermann.print(true);
    empl_mustermann.print();
    mit_default.print();
    Student *p_stud_mustermann = nullptr;
    cout << "Block wird betreten" << endl;
    {
        p_stud_mustermann = new Student("Mustermann", "Markus");
        p_stud_mustermann->print(true);
    }
    cout << "Block wurde verlassen" << endl;
    delete p_stud_mustermann;
    return 0;
}


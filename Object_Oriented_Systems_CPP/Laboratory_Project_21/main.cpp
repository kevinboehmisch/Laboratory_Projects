
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;




// Eigene Exceptionklasse "MyException"
// abgeleitet von Exception
// HIER
class MyException: public exception  {
    // HIER
  
public:
    string _dateiname;
    int _zeilennummer;
    string _beschreibung;
    MyException(string dateiname, int zeilennummer, string beschreibung): _dateiname(dateiname), _zeilennummer(zeilennummer), _beschreibung(beschreibung){}
    //überschreiben der what-Methode
    const char* what() const noexcept override{
        return _beschreibung.c_str(); //.c_str um einen Char Pointer zu erhalten, konvertierung von string zu const *char, c_str gibt Zeiger auf erstes Zeichen des nullterminierten Strings zurück 
    }
};

// Eigene Exceptionklasse "ElefantMeetsMouse"
// abgeleitet von MyException
class ElefantMeetsMouse: public MyException{// HIER 
    // HIER
    public:
    ElefantMeetsMouse(string dateiname, int zeilennummer, string beschreibung): MyException(dateiname, zeilennummer, beschreibung) {} //ruft parametrisierten Konstruktor aus Basisklasse auf
};








// Klasse der Tiere
class Animal
{
    // Name des Tiers
    string _name;

public:
    // Konstruktor
    Animal()
    {
        cout << "Bitte Namen des Tieres eingeben: ";
        cin >> _name;
    };
    // virtuelle print-Funktion
    virtual void print(bool nl) const
    {
        cout << _name;
        if (nl)
        {
            cout << endl;
        }
    }
    virtual Animal *clone() const = 0;
};


// Klasse "Elefant"
// abgeleitet von Animal
// HIER
class Elefant: public Animal{

public:
    //Konstruktor für Elefant
    Elefant():Animal(){} //Konstruktor ruft Standardkonstruktor der Basisklasse auf

    //überschreiben der Print Funktion
    void print(bool nl) const override {
        Animal::print(nl); //aufrufen, der print-Funktion von Animal
    }

    //clonen der Klasse Elefant
    Animal* clone() const override{
        return new Elefant(*this); 
    }
};

// Klasse "Tiger"
// abgeleitet von Animal
// HIER
class Tiger: public Animal  {
    // HIER
public:
    //Konstrukor für Tiger
    Tiger():Animal() {}

    //print-Funktion für Tiger
    void print(bool nl) const override {
        Animal::print(nl);
    }

    //clonen der Klasse Tiger
    Animal *clone() const override{
        return new Tiger(*this);
    }

};


// Klasse "Mouse"
// abgeleitet von Animal
//Hier
class Mouse: public Animal{
    // HIER
public:
    //Konstruktor für Maus
    Mouse(): Animal() {}

    //print-Methode für Maus
    void print(bool nl) const override {
        Animal::print(nl);
    }

    //clonen der Klasse Mouse
    Animal *clone() const override{
        return new Mouse(*this);
    }
};









class Zoo
{
    // Name des Zoos
    string _name;
    // Die Tiere werden in einem Vektor gespeichert
    vector<Animal *> animals;

public:
    // Konstruktor
    Zoo()
    {
        // Name zuweisen
        cout << "Bitte Name des Zoos eingeben: ";
        cin >> _name;
        // Wenn der String kuerzer als 4 Zeichen ist,
        // dann MyException werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        // HIER
        if(_name.length()<4){
            throw MyException(__FILE__,__LINE__, "Fehler 'Zooname zu kurz' "); //hier wird der parametrisierte Konstruktor aufgerufen aus MyException, Zuordnung von _dateiname durch __FILE__ und _zeilennummer durch __LINE__
        }
        // Ansonsten, den 5. Buchstaben des Namens gross machen
        _name.at(4) = toupper(_name.at(4)); //hier würde ein Fehler auftreten, welcher auch gecatcht wird, wenn man zB Wilh eingibt, da dieses Wort nur aus 4 Buchstaben besteht und man hier den 5. Buchstaben großschreiben möchte
    }




    // Ein Tier dem Zoo hinzufuegen
    void add_animal(const Animal &animal)
    {
        // Wenn ein Elefant nach einer Maus eingefuegt wird, oder anders herum
        // dann Ausnahme werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        // HIER
        if(animals.size() > 0){ //Bedingung ist, dass schon Objekte im Vektor vorhanden sind, da ansonsten Laufzeitfehler ensteht, wenn man auf das letzte Objekt im Vektor zugreifen möchte, obwohl es noch nicht existiert
            if (((typeid(*animals.back())== typeid(Mouse) && typeid(animal) == typeid(Elefant)) || //überprüfen ob das letzte Element Mouse ist und das aktuell hinzuzufügende Tier Elefant ist
                (typeid(*animals.back())== typeid(Elefant) && typeid(animal) == typeid(Mouse)))){  //oder andersrum
                throw ElefantMeetsMouse(__FILE__,__LINE__, "Fehler 'Elefant trifft auf Maus' ");
            }
        }   
        // sonst Tier hinzufuegen
        // HIER
        animals.push_back(animal.clone());
    }

    // Alle Zootiere ausgeben
    void print() const
    {
        // HIER
        for( const auto &animal: animals){
            animal->print(true);
        }
    }
};









int main(int argc, char *argv[])
{
    char choice;
    string name;

    // Ausnahmepruefung aktivieren
    // HIER
    try{
        Zoo zoo;
        do
        {
            cout << endl
                 << "Bitte Tierart auswaehlen:" << endl;
            cout << "1 = Elefant" << endl;
            cout << "2 = Tiger" << endl;
            cout << "3 = Maus" << endl;
            cout << "e = Ende mit Eingabe" << endl;
            cout << "Eingabe: ";
            cin >> choice;
            switch (choice)
            {
            case '1':
            {
                Elefant elefant = Elefant();
                zoo.add_animal(elefant);
                break;
            }
            case '2':
            {
                Tiger tiger = Tiger();
                zoo.add_animal(tiger);
                break;
            }
            case '3':
            {
                Mouse mouse = Mouse();
                zoo.add_animal(mouse);
                break;
            }
            case 'e':
                break;
            default:
                // Einen String als Ausnahme werfen
                // HIER
               throw string("ungültige Eingabe");
            }

            cout << endl;
            zoo.print();
        } while (choice != 'e');
    }
    // Ausnahmen auffangen
    // Speziellste Ausnahme auffangen und ausgeben
    catch (ElefantMeetsMouse &e)
    {
        cout << e.what() << "aufgetreten in Datei " << e._dateiname  << ", Zeile: " << e._zeilennummer << "." << endl;
    }
    // MyException auffangen und ausgeben
    // HIER
    catch(MyException &e){
        cout << e.what() << "aufgetreten in Datei " << e._dateiname << ", Zeile: " << e._zeilennummer << "." << endl;
    }

    // Alle anderen Standardausnahmen auffangen und ausgeben
    // HIER
     catch(exception &e) {
        cout << "Standardausnahme: " << e.what() << endl;
    }
    // Alle Strings auffangen und ausgeben
    // HIER
    catch (string &e) {
        cout << "Fehlerhafte Eingabe!" << endl;
    }

    // Alle anderen Ausnahmen auffangen
    // HIER
     catch(...) {
        cout << "Fehlerhafte Eingabe!" << endl;
    }

    
    return 0;
}


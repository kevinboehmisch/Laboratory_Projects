#include <iostream>
#include <array>
#include <vector>
using namespace std;

class Meal { //abstracte Klasse
    public:
    virtual void prepare() const = 0; //durch virtual und = 0, rein virtuell dient als nur als Vorlage für andere Klassen, hier kann man das const auch weglassen also statt const =0 einfach nur =0 schreiben
    virtual void add_topping(const string& topping) = 0; //anstatt kompliziert mit const und & als Referenz kann man auch einfach (string topping) schreiben, wesentlich übersichtlicher!!
};

class Burger: public Meal {
    string _name;
    vector<string> _toppings; //Vektor für die Toppings erstellen, da mehrere hinzugefügt werden können

public:
    Burger(string name): _name(name){} //Konstruktor für den Hamburger

    void prepare() const override{
        cout << _name << endl; //Ausgabe, des Namen, des Burgers
        for(const string& topping: _toppings) { //for Schleife, wird für jedes String Element (welches ich topping genannt habe) im Vektor _toppings ausgeführt
            cout << topping << endl; //Ausgabe der toppings, also der einzelnen String Elemente
        }

    }
    void add_topping(const string& topping) override{ 
        _toppings.push_back(topping); //hinzufügen eines Toppings, indem topping übergeben wird und angehängt
    }
};

class Pizza: public Meal {

    string _name;
    vector<string> _toppings; //es ist nicht notwendig die Länge etc mit vector<string> _topping(vectorSize, 0); zu bestimmen 

public:
    Pizza(string name): _name(name){}

    void add_topping(const string& topping) override{  //wie in class Meal bereits geschrieben kann man auch hier eine einfachere Schreibweise mit (string topping) schreiben, was deutlich übersichtlicher ist
        _toppings.push_back(topping);
    }
    void prepare() const override{ 
        cout << _name << endl;
        for(const string& topping: _toppings){ //auch hier könnte man einfach (string topping: _toppings schreiben), also jedes string element, welches topping genannt wurde, aus dem vektor toppings
            cout << topping << endl;
        }
    }
};


int main(int argc, char* argv[])
{
    Pizza *mista = new Pizza("Mista");
    mista->add_topping("Salami");
    mista->add_topping("Pilzen");
    Meal *hawaii = new Pizza("Hawaii");
    hawaii->add_topping("Schinken");
    hawaii->add_topping("Ananas");
    Burger *hamburger = new Burger("Hamburger");
    hamburger->add_topping("Hackfleisch");
    Meal *cheesburger = new Burger("Cheesburger");
    cheesburger->add_topping("Hackfleisch");
    cheesburger->add_topping("Käse");
    array<Meal *, 4> menu = {mista, hawaii, hamburger, cheesburger}; //es wird ein Array bestehend aus Objekten erstellt
    for (Meal *g : menu) //für jedes Element des Zeigers *g aus dem Array Menu, wird die Schleife durchlaufen
    {
        g->prepare(); //*[1] //der Zeiger g zeigt auf prepare von dem jeweiligen Objekt aus dem Array
    }
    return 0;
}

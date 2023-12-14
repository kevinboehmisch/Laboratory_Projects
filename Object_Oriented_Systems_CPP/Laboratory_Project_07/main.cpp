#include <iostream>
#include <string>

// Klasse Customer definieren
class Customer{
    public:
    static int _s_count; //statische Variable, da nicht jedem Customer ein _s_count erstellt werden soll, sondern der Klasse an sich
    static int _s_id_generator; //statische Variable, damit jeder eine eindeutige ID hat
    std::string _name;
    std::string _location;
    int _age;
    double _business_done;
    int _transaction_count;
    int _id;
    //Default Werte werden definiert in Übergabe
    //der Customer Count, wie viele sich im Laden befinden wird erhöht, mit jedem neuen Objekt
    //jedem neuen Objekt wird auch eine ID hinzugefügt, diese wird mit jedem neuen Customer um 1 erhöht
    //sodass jeder Customer eine eigene ID bekommt
    Customer(std::string name="Mustermann", int alter=10, std::string ort="Esslingen"){
        _name= name;
        _age= alter;
        _location= ort;
        _s_count++;
        _id = _s_id_generator++;
    }
    //Destruktor setzt die Anzahl der Kunden, die sich aktuell im Laden befinden auch mit runter
    ~Customer() {
        _s_count--;

    }

    void do_business(double amount){
        _business_done+= amount;
        _transaction_count++;
    }

    static int get_s_count(){
        return _s_count;
    }

    void print(){
        std::cout << "Kunde " << _name << " aus " << _location << " (ID = " << _id << ", " << _age << " Jahre) hatte " << _transaction_count << " Transaktion(en) und " << _business_done << " Euro Umsatz" << std::endl;
    }
};
//standardmäßig 0 Customer erstmal im Laden
//standardmäßig, hat der erste Customer die Nummer 1
//außerhalb der Klasse definiert, weil die Variablen dann schon vor Aufruf der Klasse bestehen und nicht einem einzelnen Objekt zugeordnet werden, welches erstellt wird
//Variable der Klasse und nicht des Objekts, das heißt es wird nicht mit jedem Objekt eine neue Variable erstellt
//die nur diesem Objekt zugeordnet wird, sondern alle Objekte innerhalb der Klasse teilen sich diese Variable
int Customer::_s_count = 0;
int Customer::_s_id_generator = 1;

int main(int argc, char *argv[]) {
    Customer peter = Customer("Peter", 17, "Stuttgart");
	Customer simon = Customer("Simon", 23, "Heilbronn");
    peter.~Customer();
	Customer micheal = Customer("Michael", 21, "Karlsruhe");
	Customer claudia = Customer("Claudia", 30, "Nagold");
    std::cout << "Anzahl Kunden: " << Customer::get_s_count() << std::endl;
	simon.do_business(230);
	simon.do_business(400);
	claudia.do_business(1000);
	micheal.do_business(199);
	simon.do_business(3.99);
	simon.print();
	micheal.print();
	claudia.print();
    claudia.~Customer();
    std::cout << "Anzahl Kunden: " << Customer::get_s_count() << std::endl;
	return 0;
}


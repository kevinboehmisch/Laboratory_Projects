#include <iostream>
#include <list>
#include <string>
#include <map>

using namespace std;

// Hier Exception implementieren
class OutOfStockException : public exception
{
private:
    string message;

public:
    OutOfStockException(const string& product, unsigned int available, unsigned int requested) //Parameter des Produkts, der Verfügbaren Anzahl und der nachgefragten Anzahl werden übergeben
    {   //Exception, welche Ausgeben soll wie viele Artikel von bestimmten Typ verfügbar sind und wie viele verkauft werden sollten 
        message = "Es sind " + to_string(available) + " Artikel vom Typ " + product +
                  " verfügbar. Es können nicht " + to_string(requested) + " Artikel verkauft werden.";
    }

    const char *what() const throw()
    {
        return message.c_str();
    }
};

// Hier Interface implementieren 
class ISubscriber{

public:
    virtual void update(string state)= 0;
};

// Hier Klassen Customer und GoldCustomer implementieren

//Klasse Customer
class Customer: public ISubscriber{

private:
    static int _id_generator;
    int _ID;

public:
    Customer(){
        _ID = ++_id_generator;
    } 
     void update(string state) override{
            cout << "Customer "<<_ID<<": neue Nachricht verfügbar --> "<<state<<endl;
    }
};

//Klasse GoldCustomer
class GoldCustomer: public ISubscriber{

private:
    static int _id_generator;
    int _ID;

public:
    GoldCustomer(){
        _ID= ++_id_generator;
    }
    void update(string state) override{ //diese Methode wird durch die Methode notify_subscribers aus der Klasse Store aufgerufen
        cout << "GoldCustomer " << _ID << ": neue Nachricht verfügbar --> " << state << endl;
    }
};



class Store
{
public:
 // Hier Methoden implementieren
    void subscribe(ISubscriber* subscriber)
    {
        _subscribers.push_back(subscriber);
    }

    void unsubscribe(ISubscriber* subscriber)
    {
        for (auto it = _subscribers.begin(); it != _subscribers.end(); ++it) //Schleife, welche durch alle Elemente der Liste Schleife iteriert, it ist ein Iterator der auf das aktuelle Element der Liste zeigt
        {
            if (*it == subscriber) //Hier wird überprüft ob das aktuelle Element auf das *it zeigt, auch dem übergebenen subscriber entspricht
            {
                _subscribers.erase(it); //Hier wird das Element auf das der Iterator zeigt entfernt
                break; //danach wird es abgebrochen, da der Subscriber nur einmal vorkommen sollte
            }
        }
    }

    void notify_subscribers(string state)
    {
        for (ISubscriber* subscriber : _subscribers) //Jeder Subscriber aus dem Vektor wird durchgegangen
        {
            subscriber->update(state); //Aufruf der FUnktion Update
        }
    }

    void deliver_products(string product, unsigned int quantity) //Übergabe der Parameter aus dem main Programm
    {
        cout << "Vorrätige Artikel vom Typ " << product << ": " << _product_availability[product] << endl; //Produkt welches übergeben wurde über Parameterübergabe und dann noch in der Map der product zugeordnete Wert
        cout << "Ausgelieferte Artikel vom Typ " << product << ": " << quantity << endl; //Hier einfach eingesetzt was in der Parameterübergabe übergeben wurde
        _product_availability[product] += quantity; //zum aktuellen Bestand wird die neue quantity dazugerechnet
        cout << "Neuer Bestand: " << _product_availability[product] << endl; //Hier dann der neue Bestand durch Wert aus der Map
    
        if (_product_availability[product] == quantity) //nur wenn Bestand 0 war und neue dazu kommen soll Benachrichtigung verschickt werden, weshalb es == sein muss, da ansonsten nicht 0 verfügbar gewesem sein müssen vor der Anlieferung
        {
            notify_subscribers("Neue Artikel vom Typ " + product + " verfügbar."); //Funktionsaufruf der Methode notify_subscribers mit Übergabe
        }
    }
    

    void sell_products(string product, unsigned int quantity) //Das Produkt und auch die Anzahl wie viel verkauft wird
    {
        if (_product_availability[product] >= quantity) //Schlüssel also Produktname, welcher mit dem Wert, also dem Bestand verbunden ist wird durch _product_availabitlty abgefragt, sprich hier wird der Bestand in der Map mit der gefragten Menge verglichen
        {   //wenn genügend verfügbar sind dann möglich
            cout << "Vorrätige Artikel vom Typ " << product << ": " << _product_availability[product] << endl;
            cout << "Verkaufte Artikel vom Typ " << product << ": " << quantity << endl;
            _product_availability[product] -= quantity;
            cout << "Neuer Bestand: " << _product_availability[product] << endl;

            if (_product_availability[product] == 0) //wenn ==0 dann kein Bestand mehr verfügbar
            {
                notify_subscribers("Artikel vom Typ " + product + " nicht mehr verfügbar"); //Benachrichtigen, wenn kein Produkt mehr verfügbar ist
            }
        }
        else //wenn zu wenig Produkte verfügbar dann exception werfen
        {   
            throw OutOfStockException(product, _product_availability[product], quantity); //exception auslösen, welche Übergabeparameter enthält
        }
    }
private:
    list<ISubscriber *> _subscribers;
    map<string, unsigned int> _product_availability{{"iPhone", 0}, {"Galaxy", 5}}; //hier wird map _product_availability erstellt, Schlüssel ist der Produktname (string) und Wert ist der Bestand (unsigned int)
};


int Customer::_id_generator = 100;
int GoldCustomer::_id_generator = 0;

void manage_store()
{
    try
    {
        Store *store = new Store; //store objekt erstellen
        ISubscriber *customer_1 = new Customer(); //Subscribers erstellen 
        store->subscribe(customer_1); //Subscriber abonnieren lassen
        ISubscriber *customer_2 = new GoldCustomer();
        store->subscribe(customer_2);
        ISubscriber *customer_3 = new GoldCustomer();
        store->subscribe(customer_3);
        store->deliver_products("iPhone", 5); //Produkt angeliefert
        store->unsubscribe(customer_3); //Subscriber deabonnieren
        store->sell_products("iPhone", 3); //Produkt verkaufen
        ISubscriber *customer_4 = new Customer();
        store->subscribe(customer_4);
        store->deliver_products("iPhone", 5);
        store->sell_products("iPhone", 7);
        store->unsubscribe(customer_1);
        ISubscriber *customer_5 = new GoldCustomer();
        store->subscribe(customer_5);
        store->deliver_products("iPhone", 15);
        store->sell_products("Galaxy", 8); //hier Exception, da nicht genügend verfügbar sind
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Ein unbekannter Fehler ist aufgetreten." << endl;
    }
}

int main(int argc, char *argv[])
{
    manage_store();
    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

//Interface IComponent
class IComponent{

public:
    virtual int get_price()=0; //virtuelle Methode zur Abfrage des Preises
    virtual void add(IComponent *component){}; //virtuelle Methode zum hinzufügen von Komponenten
};

//Class Product
class Product: public IComponent{

private:
    int _price; 

public:
    Product(int price): _price(price){}; 
    int get_price() override{ //überschreiben der virtuellen Funktion zum returnen des Preises
        return _price;
    } 
};

//Class Box
class Box: public IComponent{

public:
    vector<IComponent*> components; //Vektor welcher Komponenten speichert
    int get_price() override{
        int price = 0;
         for (IComponent* component : components) { //for Schleife, welche den Vektor components durchläuft mit Zeiger von IComponent welcher auf aktuelles Objekt im Vektor zeigt
        price += component->get_price();
    }
        return price;
    }
    void add(IComponent* component) override{
        components.push_back(component); //Komponent hinzufügen
    }
};

void calculate_price(IComponent *component)
{
    cout << "Preis: " << component->get_price() << endl;
}

int main(int argc, char* argv[]) {

    cout << "Preisermittlung für ein einfaches Produkt: " << endl;
    IComponent *product = new Product(10);
    calculate_price(product);
    cout << endl;

    cout << "Preisermittlung für eine verschachtelte Box: " << endl;
    IComponent *outer_box = new Box;
    IComponent *inner_box_1 = new Box;
    IComponent *product_1 = new Product(10);
    IComponent *product_2 = new Product(5);
    IComponent *product_3 = new Product(4);
    inner_box_1->add(product_1);
    inner_box_1->add(product_2);
    IComponent *inner_box_2 = new Box;
    inner_box_2->add(product_3);
    outer_box->add(inner_box_1);
    outer_box->add(inner_box_2);
    calculate_price(outer_box);
    cout << endl;
    
    cout << "Preisermittlung für eine erweiterte verschachtelte Box: " << endl;
    IComponent *product_4 = new Product(7);
    inner_box_2->add(product_4);
    calculate_price(outer_box);
    cout << endl;

    return 0;
}


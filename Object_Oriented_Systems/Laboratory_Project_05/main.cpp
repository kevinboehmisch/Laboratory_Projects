
#include<iostream>
using namespace std;

// hier die Klasse Punkt implementieren
class Point{
//Public da von außerhalb auf die Funktionen zugegriffen wird
public:
    //Member-Variablen
    double x;
    double y;
    
    //Setter-Methoden
    //hier werden die Übergabewerte den x und y Werten zugeordnet
    void set_x(int x_set){
        x= x_set;
    }
    void set_y(int y_set){
        y= y_set;
    }
    //Getter-Methoden
    //keine Werte werden übergeben,
    //d.h die Integer Werte von x,y werden einfach übergeben
    double get_x(){
        return x;
    }
    double get_y(){
        return y;
    }
    //Methode Ausgabe Koordinaten
    void print(){
        cout<<"print-Methode:"<<endl;
        cout<<"X = "<<x<<endl;
        cout<<"Y = "<<y<<endl;
    }
        
};

int main(int argc, char* argv[]) {
    Point p;
    p.set_x(1);
    p.set_y(10);
    p.print();
    p.set_x(5);
    cout << "X ohne print(): " << p.get_x() << endl;
    cout << "Y ohne print(): " << p.get_y() << endl;
    return 0;
}





#include <iostream>
#include <vector>
using namespace std;

class Point
{
	double _x;
	double _y;
public:
    // Konstruktor mit Parametern
	Point(double x = 0.0, double y = 0.0);
	// Verschiebt einen Punkt
	void move(double dx, double dy);
	// gibt den Punkt auf der Konsole aus
	void print(bool nl = true);
};

// Implementierung Konstruktor
Point::Point(double x, double y) //Konstruktor außerhalb, welcher Parameter zuordnet
{
    _x = x;
    _y = y;
}
// Implementierung Methoden
void Point::move(double dx, double dy) //Methode, welche den Punkt verschiebt
{
    _x += dx;
    _y += dy;
}

void Point::print(bool nl) //Konstruktor für die Ausgabe, mit Übergabeparameter nl, für Zeilenumbruch
{
    cout << "(" << _x << ", " << _y << ")";
    if (nl)
        cout << endl;
}


class Polygonline{
    vector<Point> _points; //speichert Datenmitglied  _points vom typ vector ab, Vektor wie Array nur dynamisch wachsend
public:
	// Konstruktor
	Polygonline();
	// Konstruktor mit Parameter
	Polygonline(Point& p);
	// gibt die Elemente des Polygons auf der Konsole aus
	void print(bool nl = true);
	// Hängt einen Punkt hinten an
	Polygonline& add_point(Point p);
	// Hängt einen zusätzlichen Polygon hinten an
	void append_polygonline(Polygonline& pl);
	// Verschiebt den gesamten Polygon
	void move(double dx, double dy);
};

// Implementierung Konstruktor
Polygonline::Polygonline(){} //Standardkonstruktor  
Polygonline::Polygonline(Point& p) //Konstruktor mit Parameter mit Referenz auf die Klasse Point
{
    _points.push_back(p); //.push_back(p) fügt den Punkt am ende des Vektors _points an
}
// Implementierung Methoden

void Polygonline::print(bool nl){ //print Methide zur Ausgabe
	cout << "|"; 

    for (vector<Point>::size_type i = 0; i < _points.size(); ++i) { 
        _points[i].print(false); //rd wird die Print Methode aus der Klasse Point aufgerufen, nicht aus Polygonline!! Das liegt daran, da an dem Index des Vektors _points aus der Klasse Polygonline
                                 //ein Objekt der Klasse Point steht und somit auch die print Methode der Klasse point verwendet wird! false übergeben, da kein Zeilenumbruch stattfinden soll
        if (i<_points.size()-1) //gibt immer zwischen den Objekten des Vektores einen Bindestrich aus, -1 sodass nicht nach dem letzten Objekt noch eins ausgegeben wird |(1, 1) - (2, 2)| und nicht |(1, 1) - (2, 2)-|
        {
            cout << " - ";
        }
    }

	cout << "|"; 

	if (nl) 
	{
		cout << endl;
	}
}

Polygonline& Polygonline::add_point(Point p) //Methode zum anhängen eines Punktes per Referenz und nicht als Kopie
{
	_points.push_back(p); //anhängen eines neuen Punktes
	return *this; //Referenz auf das aktuelle Polygonline Objekt
}

void Polygonline::append_polygonline(Polygonline& pl) //Methode zum Anhängen eines zweiten Vektors an den ersten l1.append_polygonline(l2); so würde der Befehl im main Programm aussehen, im Prinzip 2 Arrays aneinanderfügen, Vektor ja offenes dynamisches Array
{
	_points.insert(_points.end(), pl._points.begin(), pl._points.end()); //alles Funktionen der Standardbibliothek, .insert dafür dass es wo einfügen soll
}                                                                        //_points.end zeigt das Ende des aktuellen _points Vektors an, p1._points.begin() zeigt den Beginn des Bereichs wo es einzufügen ist an
                                                                         //und p1._points.end das Ende des einzufügenden Bereichs an

void Polygonline::move(double dx, double dy) //Methode zum verschieben des Polygonline Vektors
{
	for (size_t i = 0; i < _points.size(); i++) //Durchläuft den kompletten Vektor
	{
		_points[i].move(dx, dy); //hier wird wieder die move Funktion der Klasse Point aufgerufen und nicht der Klasse Polygonline! Da hier ja wieder das Objekt aus der Klasse Point an Index i des Vektors aufgerufen wird
	}
}


int main(int argc, char *argv[]) 
{
	Point p1(1, 1), p2(2, 2), p3(3, 3), p4(4, 4), p5(5, 5);
	Polygonline l1;
	Polygonline l2(p3);
	cout << "Ausgabe 1:" << endl;
	l1.print();
	l2.print();
	l1.add_point(p1).add_point(p2);
	l2.add_point(p4).add_point(p5);
	cout << "Ausgabe 2:" << endl;
	l1.print();
	l2.print();
	p2.move(0.5, 0.5);
	cout << "Ausgabe 3:" << endl;
	p2.print();
	l1.print();
	l2.print();
	l1.append_polygonline(l2);
	cout << "Ausgabe 4:" << endl;
	l1.print();
	l2.print();
	l1.move(0, 0.5);
	cout << "Ausgabe 5:" << endl;
	l1.print();
	l2.print();
	return 0;
}


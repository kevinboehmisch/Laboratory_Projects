# THEMEN:
Klassen, Klassenvariablen

# IHRE AUFGABE:
Die Klasse 'Customer' soll folgende Attribute besitzen:

static int _s_count;
static int _s_id_generator;
std::string _name;
std::string _location;
int _age;
double _business_done;
int _transaction_count;
int _id;

Das Attribut '_business_done' gibt an, welcher Umsatz in Euro in einer Transaktion (d.h. einem Einkauf) gemacht wird. Die Variable '_id' gibt die Kundennummer an. Sie wird in Abhängigkeit der statischen Variablen '_s_id_generator' gesetzt. Die statischen Variablen '_s_count' und '_s_id_generator' werden automatisch inkrementiert, wenn ein Objekt der Klasse 'Customer' angelegt wird. Verfassen Sie a) einen Konstruktor mit Default-Parametern für '_name', '_location' und '_age'.

b) einen Destruktor

c) die Methode 'do_business(double amount)', mit welcher '_business_done' um 'amount' erhöht und gleichzeitig das Atribut '_transaction_count' inkrementiert wird.

d) eine statische Methode 'get_s_count()', mit welcher die statische Variable '_s_count' zurückgegeben werden kann.

e) eine print()-Methode, mit welcher z.B. der unten angegebene Text ausgegeben werden kann:

Kunde Meier aus Esslingen (ID = 4, 28 Jahre) hatte 3 Transaktion(en) und 230 Euro Unsatz
Das angegebene Hauptprogramm soll folglich die folgende Ausgabe erzeugen:

Ausgabe:

Anzahl Kunden: 3
Kunde Simon aus Heilbronn (ID = 2, 23 Jahre) hatte 3 Transaktion(en) und 633.99 Euro Umsatz
Kunde Michael aus Karlsruhe (ID = 3, 21 Jahre) hatte 1 Transaktion(en) und 199 Euro Umsatz
Kunde Claudia aus Nagold (ID = 4, 30 Jahre) hatte 1 Transaktion(en) und 1000 Euro Umsatz
Anzahl Kunden: 2

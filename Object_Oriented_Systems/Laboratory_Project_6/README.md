THEMEN:
Initialisierung von Objekten, Konstruktoren, Destruktoren

IHRE AUFGABE:
Schreiben Sie eine Klasse 'Student' mit den Attributen '_name' und '_first_name' vom Typ String. Schützen Sie die Attribute gegen Zugriff von außen. Die folgenden Methoden implementieren sie außerhalb der Klasse: Die Klasse soll einen parametrisierten Konstruktor haben, der Name und Vorname entgegennimmt und die beiden Attribute '_name' und '_first_name' entsprechend belegt. Verwenden Sie hierzu keine Initialisierungsliste. Schreiben sie get-Methoden für beide Attribute und einen Destruktor. Schreiben Sie zwei print-Methoden, beide ohne Rückgabewert. Eine der beiden Methoden nimmt eine boolsche Variable entgegen, mit der gesteuert werden kann, ob am Ende der Zeile ein Zeilenumbruch erfolgen soll oder nicht. In der anderen Methode erfolgt immer ein Zeilenumbruch.

Schreiben Sie eine Klasse 'Employee', ebenfalls mit den Attributen '_name' und '_first_name' vom Typ String. Schützen Sie auch diese Attribute gegen einen Zugriff von außen. Die folgenden Methoden implementieren sie innerhalb der Klasse: Die Klasse soll einen parametrisierten Konstruktor haben, der Name und Vorname entgegennimmt und die beiden Attribute '_name' und '_first_name' entsprechend belegt. Verwenden Sie hierzu die Initialisierungsliste. Die Klasse soll einen Standardkonstruktor haben, die den Konstruktoraufruf an den parametrisierten Konstruktor delegiert. Nutzen Sie auch hier die Initialisierungsliste und setzen sie die Werte 'Mustermann' für Name und 'Erika' für Vorname. Schreiben Sie zusätzlich einen Konvertierkonstruktor, der einen Studenten entgegenimmt und die enthaltenen Daten zur Initialisierung von Name und Vorname verwendet. Schreiben sie einen Destruktor. Schreiben Sie auch für diese Klasse zwei print-Methoden, ebenfalls beide ohne Rückgabewert. Eine der beiden Methoden nimmt eine boolsche Variable entgegen, mit der gesteuert werden kann, ob am Ende der Zeile ein Zeilenumbruch erfolgen soll oder nicht. In der anderen Methode erfolgt immer ein Zeilenumbruch.

Die Methoden der beiden Klassen sollen jeweils eine Ausgabe enthalten, die zur Ausgabe der vorgegebenen main-Methode passt. Die Ausgabe ist unten angegeben.

Ausgabe:

Parametrisierter Konstruktor Student: Max Mustermann
Konvertierungskonstruktor Employee: Max Mustermann
Parametrisierter Konstruktor Employee: Erika Mustermann
Standardkonstruktor Employee: Erika Mustermann
print() ohne Parameter; Student: Max Mustermann
print() mit Parameter; Student: Max Mustermann
print() ohne Parameter; Mitarbeiter: Max Mustermann
print() ohne Parameter; Mitarbeiter: Erika Mustermann
Block wird betreten
Parametrisierter Konstruktor Student: Markus Mustermann
print() mit Parameter; Student: Markus Mustermann
Block wurde verlassen
Destruktor Student: Markus Mustermann
Destruktor Employee: Erika Mustermann
Destruktor Employee: Max Mustermann
Destruktor Student: Max Mustermann 

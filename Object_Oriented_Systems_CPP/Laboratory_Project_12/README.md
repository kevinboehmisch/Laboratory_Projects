# THEMEN:
Mehrfache Vererbung, Vermeidung von mehrfachem Erbgut

# IHRE AUFGABE:
Das gegebene Programm erzeugt die folgende Ausgabe:

D1::print() ...
---------------------
C2::a = D1C2A
---------------------
C3::a = D1C3A
---------------------
C2::b = D1C2B
---------------------
C3::b = D1C3B
---------------------

D2::print() ...
---------------------
C1::a = D2C1A
---------------------
C2::a = D2C2A
---------------------
C3::a = D2C3A
---------------------
C1::b = D2C1B
---------------------
C2::b = D2C2B
---------------------
C3::b = D2C3B
---------------------
Die Funktionen 'search' und 'cell' zusammen geben die Instanzvariablen der Objekte d1_object und d2_object aus. Instanzvariablen, die bei der Ausgabe in getrennten Zeilen ausgegeben werden, sind eigenständige Instanzvariablen, die eigenen Speicherplatz in Anspruch nehmen. In der Ausgabe oben werden daher die Instanzvariablen a und b mehrfach an D1 und D2 vererbt. Ändern Sie die Klassen im Programm so ab, dass die folgende Ausgabe erzeugt wird:

D1::print() ...
---------------------
C2::a C3::a = D1A
---------------------
C2::b C3::b = B
---------------------

D2::print() ...
---------------------
C1::a C2::a C3::a = A
---------------------
C1::b = D2C1B
---------------------
C2::b C3::b = D2B
---------------------
Es soll also für das Attribut a ein gemeinsames Erbgut über alle abgeleiteten Klassen geben und für das Attribut b ein gemeinsames Erbgut für die Klassen C2 und C3 aber ein separates Erbgut für die Klasse C1.

Verwenden Sie dazu virtuelle Ableitung und ergänzen Sie Initialisierungslisten wenn notwendig. Ändern Sie nicht die Default-Parameter der Konstruktoren und ändern sie nicht die existierende Delegation an Konstruktoren der abgeleiteten Klassen.

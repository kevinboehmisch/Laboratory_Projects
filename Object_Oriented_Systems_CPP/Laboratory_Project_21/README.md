# THEMEN:
Exception Handling, Polymorphie

# IHRE AUFGABE:
a) Leiten Sie von der Standardexceptionklasse exception eine eigene Klasse MyException ab.

Schreiben Sie einen parametrisierten Konstruktor, der in seperaten Parametern den Dateinamen und die Zeilennummer entgegegennimmt, in der eine Ausnahme auftritt. Zusätzlich soll ein dritter Parameter übergeben werden können, der den Namen bzw. eine Beschreibung der Ausnahme enthält.

Um die Zeile und den Dateinamen zu ermitteln sollen die Präprozessormakros __LINE__ und __FILE__ im Aufruf des Konstruktors genutzt werden. Stimmt die durch das Makro __LINE__ zurückgegebene Zeilennummer nicht mit der erwarteten überein, kann entsprechen hinzuaddiert / substrahiert werden, z.B.: throw MyException(__FILE__, __LINE__ + 7 , "Zooname zu kurz");

Überschreiben sie zusätzlich die Methode what() der Standardexception, die eine Beschreibung des Fehlers - bestehend aus der Angabe der Datei, der Zeile und des Namens des Fehlers - zurückgibt.

b) Ergänzen Sie den Programmcode an den gekennzeichneten Stellen (//HIER).

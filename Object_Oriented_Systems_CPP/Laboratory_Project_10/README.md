# THEMEN:
Vererbung, Delegation von Konstruktoren und Methoden

# IHRE AUFGABE:
Für eine Bibliotheksanwendung benötigen Sie verschiedene Benutzergruppen, Dozenten (Klasse 'Lecturer') und Studenten (Klasse 'Student'). Diese sollen von einer gemeinsamen Basisklasse 'Person' erben. Die Ausleihdauer soll für Dozenten 90 Tage und für Studenten 30 Tage betragen. Ergänzen Sie die Vererbungshierarchie und implementieren Sie die angegebenen Methoden. Verwenden Sie Delegation, um den Konstruktor der Basisklasse aufzurufen und nutzen Sie in den print()-Methoden von Dozent und Student die print()-Methode der Basisklasse.

Das angegebene Hauptprogramm soll folgende Ausgabe erzeugen:

Ausgabe:

smith, Matrikelnummer 12345678
Ausleihdauer: 30 Tage(e)
miller, Prüfernummer 98
Ausleihdauer: 90 Tage(e)

# THEMEN:
Interfaces, Dependency Inversion Principle, Composite Pattern, Exceptions

# IHRE AUFGABE:
Implementieren Sie das Observer Pattern, vgl. Foliensatz "11-1_Pattern", Folie 38 bis 41.

Implementieren Sie das Interface ISubscriber mit der rein virtuellen Methode update, die einen String als Parameter entgegennimmt. Implementieren Sie die Klassen Customer und GoldCustomer, die jeweils das Interface ISubscribers implementieren. Jedes Objekt der Klasse Customer und auch jedes Objekt der Klasse GoldCustomer soll eine eindeutige ID erhalten. Nutzen sie zur Erzeugung der IDs jeweils eine statische Variable.

Implementieren sie die Methoden subscribe, unsubscribe, notify_subscribers, deliver_products und sell_products der Klasse Store.

Die Methode deliver_products soll ausgeben, wie viele Artikel bisher verfügabr waren, wie viele Artikel ausgeliefert wurden und wie der neue Bestand ist. Waren vor der Lieferung keine Produkte verfügbar waren, sollen die Kunden darüber informiert werden.

Die Methode sell_products soll zunächst prüfen ob die angegebene Anzahl an Produkten verkauft werden kann. ist dies nicht der Fall, so soll eine OutOfStockException geworfen werden, die von der Standardexception erbt und die what-Methode überschreibt. Die letzte Zeile der Ausgabe unten zeigt die Fehlermeldung, die durch die Exception ausgelöst wird. Kann die angegebene Anzahl an Produkten verkauft werden, so soll die Methode ausgeben, wie viele Artikel bisher verfügabr waren, wie viele Artikel verkauft wurden und wie der neue Bestand ist. Sind nach dem Verkauf keine Produkte mehr verfügbar, sollen die Kunden darüber informiert werden.

Das gegebene Programm soll die folgende Ausgabe erzeugen:

# Ausgabe:

Vorrätige Artikel vom Typ iPhone: 0
Ausgelieferte Artikel vom Typ iPhone: 5
Neuer Bestand: 5
Customer 101: neue Nachricht verfügbar --> Neue Artikel vom Typ iPhone verfügbar.
GoldCustomer 1: neue Nachricht verfügbar --> Neue Artikel vom Typ iPhone verfügbar.
GoldCustomer 2: neue Nachricht verfügbar --> Neue Artikel vom Typ iPhone verfügbar.
Vorrätige Artikel vom Typ iPhone: 5
Verkaufte Artikel vom Typ iPhone: 3
Neuer Bestand: 2
Vorrätige Artikel vom Typ iPhone: 2
Ausgelieferte Artikel vom Typ iPhone: 5
Neuer Bestand: 7
Vorrätige Artikel vom Typ iPhone: 7
Verkaufte Artikel vom Typ iPhone: 7
Neuer Bestand: 0
Customer 101: neue Nachricht verfügbar --> Artikel vom Typ iPhone nicht mehr verfügbar
GoldCustomer 1: neue Nachricht verfügbar --> Artikel vom Typ iPhone nicht mehr verfügbar
Customer 102: neue Nachricht verfügbar --> Artikel vom Typ iPhone nicht mehr verfügbar
Vorrätige Artikel vom Typ iPhone: 0
Ausgelieferte Artikel vom Typ iPhone: 15
Neuer Bestand: 15
GoldCustomer 1: neue Nachricht verfügbar --> Neue Artikel vom Typ iPhone verfügbar.
Customer 102: neue Nachricht verfügbar --> Neue Artikel vom Typ iPhone verfügbar.
GoldCustomer 3: neue Nachricht verfügbar --> Neue Artikel vom Typ iPhone verfügbar.
Es sind 5 Artikel vom Typ Galaxy verfügbar. Es können nicht 8 Artikel verkauft werden.

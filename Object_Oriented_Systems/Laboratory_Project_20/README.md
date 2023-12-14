# THEMEN:
Interfaces, Dependency Inversion Principle

# IHRE AUFGABE:
Setzen Sie das Dependency Inversion Principle um.

Implementieren Sie eine Klasse "AuthenticationResult" mit den konstanten Attributen "_authenticated" von Typ bool und "_username" vom typ string, einem parametrisierten Kontruktor, der die Attribute initialisiert sowie getter-Methoden um die jeweilingen Werte auszulesen. Der Parameter für den Usernamen soll den default-Wert "unauthenticated_user" enthalten.

Schreiben Sie ein Interface "IAuthenticationProcedure", das die rein virtuelle Methode "authenticate" mit dem Rückgabewert "AuthenticationResult" enthält.

Schreiben Sie eine Klasse "Client" mit dem Attribut "_auth" vom Typ Pointer auf "IAuthenticationProcedure". Die Methode "set_authentication" nimmt einen Pointer auf "IAuthenticationProcedure" entgegen und setzt das Attribut "_auth_procedure" entsprechend. Die methode "execute" nimmt keine Parameter entgegen und führt die folgende Logik aus: Es führt zunächst auf dem "_auth_procedure"-Attribut die Methode "authenticate" aus und weist das Ergebnis einer konstanten vom Typ "AuthenticationResult" zu. Weist das "AuthenticationResult" ein positives Ergebnis aus, so wird auf der Konsole folgendes ausgegeben:

Das Programm wird ausgeführt für [user].
War die Authentifizierung nicht erfolgreich so wird folgendes ausgegeben:

Das Programm konnte nicht ausgeführt werden.
Schreiben Sie drei verschiedene Implementierungen des Interfaces "IAuthenticationProcedure": "MockAuth", "UsernamePassword" und "Certificate".

Die Klasse "MockAuth" gibt in jedem Fall ein positives "AuthenticationResult" für den Username "Default" zurück.

Die Klasse "UsernamePassword" liest nacheinander zunächst den Usernamen und das Passwort ein. Dazu wird der Anwender jeweils über die Konsole zur Eingabe aufgefordert:

Username:
bzw.

Password:
Sind Username und Passwort identisch, so gibt die Klasse ein positives "AuthenticationResult" für den entsprechenden Username zurück. Andernfalls wird ein negatives "AuthenticationResult" zurückgegeben.

Die Klasse "Certificate" liest den Zertifikatsaussteller von der Konsole ein. Der Anwender wird hierzu folgendermaßen aufgefordert:

Zertifikatsaussteller:
Ist der Zertifikatsaussteller "hs-esslingen" so gibt die Klasse ein positives "AuthenticationResult" zurück mit dem Usernamen "certificate.owner". Andernfalls wird ein negatives "AuthenticationResult" zurückgegeben.

Für die Eingaben:

Username:
Maier
Passwort:
Maier

Zertifikatsaussteller:
hs-esslingen
erzeugt das Programm die folgende (Ein-)Ausgabe:

Authentifizierung über MockAuth
Das Programm wird ausgeführt für Default.
Authentifizierung über UsernamePassword
Username:
Maier
Password:
Maier
Das Programm wird ausgeführt für Maier.
Authentifizierung über Zertifikat
Zertifikatsaussteller:
hs-eslingen
Das Programm wird ausgeführt für certificate.owner.

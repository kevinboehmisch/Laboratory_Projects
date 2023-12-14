#include <iostream>
#include <string>
using namespace std;


//Klasse AuthenticationResult mit konstanten Attributen
class AuthenticationResult {
    const bool _authenticated;
    const string _username;

public:
    AuthenticationResult(bool authenticated, string username="unauthenticated_user");
    const bool get_authenticated() const;
    const string get_username() const;
};
//Konstruktor, welcher Attribute initialisert
AuthenticationResult::AuthenticationResult(bool authenticated, string username) : _authenticated(authenticated), _username(username) {}
const bool AuthenticationResult::get_authenticated() const {
    return _authenticated;
}
const string AuthenticationResult::get_username() const {
    return _username;
}



//Implementierung des Interfaces IAuthenticationProcedure
class IAuthenticationProcedure {
public:
    virtual AuthenticationResult authenticate() const = 0; //rein Virtuelle Methode
};


//Implementierung des Interfaces IAuthenticationProcedure als MockAuthentication
class MockAuthentication : public IAuthenticationProcedure {
public:
    AuthenticationResult authenticate() const {
        return AuthenticationResult(true, "Default"); //gibt immer positven Wert für Default zurück
    }
};

//Implementierung des Interfaces IAuthenticationProcedure als UsernamePassword
class UsernamePassword : public IAuthenticationProcedure {
public:
    AuthenticationResult authenticate() const { //Es soll immer gefragt werden, vor der Eingabe
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << endl;
        cout << "Password: ";
        cin >> password;
        cout << endl;

        if (username == password) { //Wenn beides übereinstimmt positives AuthenticationResult zurückgegeben
            return AuthenticationResult(true, username);
        } else {
            return AuthenticationResult(false, username); //ansonsten negativ
        }
    }
};

//Implementierung des Interfaces IAuthenticationProcedure als Certificate
class Certificate : public IAuthenticationProcedure {
public:
    AuthenticationResult authenticate() const  { 
        string certificateIssuer;
        cout << "Zertifikatsaussteller: "<< endl; //Abfrage nach Zertifikatsaussteller
        cin >> certificateIssuer;

        if (certificateIssuer == "hs-esslingen") { //Wenn hs-esslingen, positv und certificate.owner als Rückgabe
            return AuthenticationResult(true, "certificate.owner");
        } else {
            return AuthenticationResult(false, "unauthenticated_user");
        }
    }
};




//Klasse Client
class Client {
    IAuthenticationProcedure* _auth_procedure; //Pointer auf IAuthenticationProcedure
public:
    void set_authentication_procedure(IAuthenticationProcedure* auth_procedure) {
        _auth_procedure = auth_procedure; //Funktion nimmt Pointer entgegen und setzt ihn entsprechend 
    }

    void execute() {
        AuthenticationResult result = _auth_procedure->authenticate(); //wird in Interface Implementierung ausgeführt, 
                                                                       //worauf Pointer gezeigt hat, weißt AuthenticaitonResult dann entsprechendes Ergebnis zu 
        if (result.get_authenticated()) {
            cout << "Das Programm wird ausgeführt für " << result.get_username() << "." << endl;
        } else {
            cout << "Das Programm konnte nicht ausgeführt werden." << endl;
        }
    }
};

int main(int argc, char* argv[]) {
    Client client;

    cout << "Authentifizierung über das Authentifizierungsverfahren Mock Authentication" << endl;
    IAuthenticationProcedure* mock_authentication = new MockAuthentication();
    client.set_authentication_procedure(mock_authentication);
    client.execute();

    cout << "Authentifizierung über das Authentifizierungsverfahren Username Password" << endl;
    IAuthenticationProcedure* username_password = new UsernamePassword();
    client.set_authentication_procedure(username_password);
    client.execute();

    cout << "Authentifizierung über das Authentifizierungsverfahren Zertifikat" << endl;
    IAuthenticationProcedure* certificate = new Certificate();
    client.set_authentication_procedure(certificate);
    client.execute();
    return 0;
}


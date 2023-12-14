
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

// Aufzählungstyp für wählbare Objekte
// STEIN - 0, SCHERE - 1, PAPIER - 2
enum class Object
{
    ROCK,
    SCISSORS,
    PAPER
};

// Aufzählungstyp für mögliche Spielausgänge
enum class Result
{
    PLAYER_ONE_WINS,
    PLAYER_TWO_WINS,
    DRAW
};

// Struktur für einen Spieler bestehend aus Name und Wahl des Spielers
struct Player
{
    string name;
    Object choice;
};

// Name des Spielers eingeben
string insert_name()
{

    // HIER programmieren:
    // Den Namen des Spielers von der Konsole einlesen und zurückgeben
    string name;
    cout<< "Name des Spielers: ";
    getline(cin, name);
    return name;
    // Tip: für das Einlesen eines Strings gibt es eine bestimmte Funktion, siehe auch Vorlesung Folie "Eine Zeile als String einlesen"

}

Object determine_choice(string choice)
{
    if (choice.compare("CoderunnerTestValueROCK") == 0)
    {
        return Object::ROCK;
    }
    else if (choice.compare("CoderunnerTestValueSCISSORS") == 0)
    {
        return Object::SCISSORS;
    }
    else if (choice.compare("CoderunnerTestValuePAPER") == 0)
    {
        return Object::PAPER;
    }
    else
    {
        // Den Computer zufällig waehlen lassen.
        srand(static_cast<int>(time(nullptr)));
        int choice = rand() % 3;
        return static_cast<Object>(choice);
    }
}

// Die Wahl von Stein etc. als String zurückgeben lassen
string get_name(Object object)
{

    // HIER programmieren:
    string name;
    if (object == Object::ROCK)
    {
        name = "Stein";
    }
    else if (object==Object::SCISSORS)
    {
        name = "Schere";
    }
    else if (object==Object::PAPER)
    {
        name = "Papier";
    }
    return name;
    // Abhängig vom vorliegenden Object einen entsprechenden String zurückgeben.
    // z.B: Wenn Object dem Wert Object::ROCK entspricht, dann String "Stein" zurückgeben

}

// Einen Text mit dem Namen des Spielers und seiner Wahl ausgeben
void print_choice(Player player)
{

    // HIER programmieren:
    cout << player.name <<" hat das Objekt " << get_name(player.choice) << " gewählt" <<endl;
    // Auf der Konsole ausgeben, für welches Object sich der Spieler entschieden hat.
    // z.B.: "Computer hat das Object Schere gewählt"
    // TIP: Nutzen sie hierzu die Funktion get_name

}

// Die Wahl des Spielers abfragen
Object choose()
{

    // HIER programmieren:
    int choice;
    do{
        string object;
        cout<<"Bitte Objektwahl eingeben (1 = Stein, 2 = Schere, 3 = Papier): ";
        cin>> choice;
    }while(choice<1||choice>3);
    return static_cast<Object>(choice-1);
    // Die Wahl des Spielers von der Konsole einlesen und zurückgeben
    // Stellen sie sicher, dass es sich um eine gültige Wahl handelt!
    // TIP: Nutzen Sie dazu eine geeignete Schleife. Siehe auch Vorlesung Folie "Annehmende Schleifenanweisungen – Do"

}

Result determine_result(Player player_1, Player player_2)
{

    // HIER programmieren:
    if (player_1.choice==player_2.choice){
        return Result::DRAW;
    }
    else if ((player_1.choice==Object::ROCK && player_2.choice==Object::SCISSORS)||
             (player_1.choice==Object::SCISSORS && player_2.choice==Object::PAPER)||
             (player_1.choice==Object::PAPER && player_2.choice==Object::ROCK)){
        return Result::PLAYER_ONE_WINS;
    }
    else {
        return Result::PLAYER_TWO_WINS;
    }
    // Vergleichen Sie die gewählten Objekte, ermitteln sie das Spielergebnis und geben sie es zurück.
    // TIP: Wenn Sie für den Vergleich mit ganzene Zahlen _rechnen_ wollen, dann nutzen sie den static_cast, siehe auch Vorlesung Folie "Casts in C++: Static_cast"

}

void print_result(Player player_1, Player player_2)
{

    // HIER programmieren:
    Result result = determine_result(player_1, player_2);
    if (result == Result::DRAW)
    {
        cout << "Unentschieden" << endl;
    }
    else if (result == Result::PLAYER_ONE_WINS)
    {
        cout <<"Spieler "<< player_1.name << " hat gewonnen." << endl;
    }
    else
    {
        cout <<"Spieler "<< player_2.name << " hat gewonnen." << endl;
    }
    // Ermitteln Sie zunächst das Spielergebnis. Nutzen sie dazu die Funktion determine_result.
    // Geben Sie anschließend auf der Konsole aus, wer gewonnen hat.
    // z.B: "Spieler Computer hat gewonnen" oder "Unentschieden"

}

int main(int argc, char *argv[])
{
    Player player_1, player_2;
    player_1.name = "Computer";
    player_2.name = insert_name();
    player_1.choice = determine_choice(player_2.name);
    cout << "Der Computer hat seine Wahl getroffen." << endl;
    player_2.choice = choose();
    print_choice(player_1);
    print_choice(player_2);
    print_result(player_1, player_2);

    return 0;
}


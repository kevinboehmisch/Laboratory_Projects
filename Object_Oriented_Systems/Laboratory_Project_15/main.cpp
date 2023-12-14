

#include <array>
#include <iostream>
using namespace std;

const unsigned int length = 10;

// hier die Funktion 'sort' implementieren

template <typename T>
array<T,length> sort(array<T,length>array) //array<T,length> sorgt dafür, das gesamtes Array als Rückgabetyp zurückgegeben wird
                                           //(array<T,length>array) array mit Datentyp T und der länge length als Übergabeparameter
{
    T temp;
    bool swapped = true;
    unsigned int counter = 0;
    while(swapped && counter < length) //while-Schleife läuft so lange, bis es getauscht wurde und bis das komplette Array durchlaufen ist 
    {
        swapped = false;
        for(unsigned int i = 0; i < length - 1-counter; i++) //läuft das komplette Array durch, dabei werden die bereits sortier
        {                                                    //Indexe durch length-1-counter geskipped, weil diese schon bereits sortiert sind, größte ganz hinten, letzte, also length-1 muss nie kontrolliert werden
            if(array[i] > array[i + 1]) //wenn der Index danach kleiner ist wird getauscht
            {
                temp = array[i]; //alten Wert an Index i speichern
                array[i] = array[i + 1]; //vorheriger Wert wird mit späterem Wert getauscht
                array[i + 1] = temp; //vorheriger Wert wird an spätere Stelle gesetzt
                swapped = true; //wenn getauscht swapped= true damit while schleife weiter läuft
            }
        }
    }
    return array;
}

int main(int argc, char *argv[]) 
{
    array<int,length> int_container = {10, 2, 7, 5, 8, 3, 4, 1, 9, 6}; //array mit int Werten erstellt, Schreibweise dafür
    array<int, length> sorted_int_container = sort(int_container); 

    for (size_t i = 0; i < sorted_int_container.size(); i++) {
        cout << i << ": " << sorted_int_container[i] << endl;
    }

    array<char,length> char_container = {'j', 'm', 'e', 't', 'k', 'o', 'p', 's', 'a', 'f'};
    array<char, length> sorted_char_container = sort(char_container);

    for (size_t i = 0; i < sorted_char_container.size(); i++) {
        cout << i << ": " << sorted_char_container[i] << endl;
    }

    array<string,length> string_container = {"Im", "Sommer", "ist", "es", "meistens", "heiß", "und", "es", "regnet", "wenig."};
    array<string, length> sorted_string_container = sort(string_container);

    for (size_t i = 0; i < sorted_string_container.size(); i++) {
        cout << i << ": " << sorted_string_container[i] << endl;
    }
}




#include <string>
#include <iostream>
using namespace std;

struct ListElement
{
    int id;
    ListElement* p_next;
};

ListElement* p_root = nullptr;

void add_new_head_element(int id)
{
    ListElement* p_new_element = new ListElement();
    p_new_element->id = id;
    p_new_element->p_next = p_root;
    p_root = p_new_element;
}

void add_new_tail_element(int id)
{
    // HIER programmieren:
    //neues Listenelement erstellen, Heap Speicher zuweisen
    //Hier wird als erstes ein Neues Element erstellt mit der ID und dem zugehörigen Zeiger,
    //Der Zeiger zeigt auf nullptr, da es sich um das letzte Element handelt
    ListElement* p_new_element = new ListElement(); 
    p_new_element->id=id;
    p_new_element->p_next=nullptr;
    //if schleife notwendig, da ansonsten Endlosschleife, wenn die Liste nur aus einem Element besteht
    //da bei p_temp->p_next != nullptr, der nullptr somit nie erreicht wird
    if (p_root == nullptr)
    {
        p_root = p_new_element;
    }
    else
    {
        //temporärer Pointer, welcher auf die Startposition root zeigt, den Entrypoint der Liste
        //muss erstellt werden, damit p_root erhalten bleibt, ansonsten keinen Zugriff mehr auf vorherige Elemente
        ListElement* p_temp = p_root;
        //während, der Link, des Zeigers von p_temp (p_temp->p_next) auf das nächste Element der Liste, nicht der nullptr ist,
        //wird die Schleife immer weiter durchlaufen
        while(p_temp->p_next != nullptr){
            p_temp=p_temp->p_next; //p_temp, wird auf die Adresse des nächsten Elements gesetzt, auf die der Link zeigt
        }
        //nun wird das letzte Element der bisherigen Liste, mit dem neuen letzten Element der neuen Liste verknüpft
        //dafür wird der Link des bisher letzten Elements auf die Adresse des neues Elements gesetzt
        p_temp->p_next=p_new_element;
    }
    // Neues listenElement erzeugen.
    // Ans Ende der Liste navigieren und neues listenElement anhängen.
}

void delete_element(int id)
{
    ListElement *p_tmp = p_root;
    ListElement *p_predecessor = nullptr;

    while (p_tmp != nullptr && p_tmp->id != id)
    {
        p_predecessor = p_tmp;
        p_tmp = p_tmp->p_next;
    }
    if (p_tmp != nullptr)
    {
        if (p_tmp == p_root)
        {
            p_root = p_tmp->p_next;
        }
        else
        {
            p_predecessor->p_next = p_tmp->p_next;
        }
    }
    delete p_tmp;
}

void print_list()
{
    // Hier programmieren:
    ListElement *p_temp= p_root;
    while(p_temp!=nullptr){
        cout<<p_temp->id<<endl;
        p_temp=p_temp->p_next;
    }
    
    // Die Liste durchlaufen und jeweils die id des listenElements ausgeben. 
}

int main(int argc, char* argv[])
{
    add_new_tail_element(9);
    add_new_head_element(2);
    add_new_head_element(1);
    add_new_tail_element(10);
    print_list();
    delete_element(2);
    print_list();

    return 0;
};


#include "Manager.h"
#include "Worker.h"

#include <iostream>
using namespace std;



int main()
{
    Manager m("Kevin", "B�hmisch", 1000.00);
    m.print();
    cout << "Gehalt: " << m.get_income() << endl << endl;
    Worker w("Peter", "Mueller", 15.00, 40);
    w.print();
    cout << "Lohn: " << w.get_income() << endl;
    return 0;
}

# THEMEN:
Stringformatierung

# IHRE AUFGABE:
Um die Ausgaben über einen Standard-Stream zu formatieren, stehen eine Reihe von Manipulatoren zur Verfügung (siehe die Folien aus der Vorlesung). Während die meisten Manipulatoren in der Bibliothek iostream enthalten sind, benötigen die Manipulatoren setprecision, setw und setfill die Bibliothek iomanip. Genaue Beschreibungen der Manipulatoren sowie Beispiele finden Sie unter der generell hilfreichen Webadresse http://www.cplusplus.com/reference. Ergänzen Sie das untenstehende Programm an den Stellen /xxx/, so dass es die nachfolgende Ausgabe erzeugt:

 Nr Oct  Hex String  Fixed     Scientific
  1  01  0x1 **+++++ +   1.234  1.234E+00
  2  02  0x2 ***++++ -   2.468 -2.468E+00
  3  03  0x3 ****+++ +   4.936  4.936E+00
  4  04  0x4 *****++ -   9.872 -9.872E+00
  5  05  0x5 *++++++ +  19.744  1.974E+01
  6  06  0x6 **+++++ -  39.488 -3.949E+01
  7  07  0x7 ***++++ +  78.976  7.898E+01
  8 010  0x8 ****+++ - 157.952 -1.580E+02
  9 011  0x9 *****++ + 315.904  3.159E+02
 10 012  0xa *++++++ - 631.808 -6.318E+02

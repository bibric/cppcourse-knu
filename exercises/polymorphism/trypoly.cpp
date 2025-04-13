#include "Polygons.hpp"
#include <iostream>

int main() {
    Pentagon a{1.0};
    std::cout<<a.computePerimeter()<<"\n";
    // create a Pentagon, call its perimeter method


    // create a Hexagon, call its perimeter method
    Hexagon b{1.};
    std::cout<<b.computePerimeter()<<"\n";

    // create a Hexagon, call the perimeter method through a reference to Polygon
    RegularPolygon& ref = b;
    std::cout << ref.computePerimeter() << "\n";



    // retry virtual method

    return 0;
}
/* изначальный аутпут
Polygon::computePerimeter is being called
5.87785
Hexagon::computePerimeter is being called
6
Polygon::computePerimeter is being called
6
*/

/* Виртуальный аутпут
for virtual Pentagon Polygon::computePerimeter is being called
5.87785
Hexagon::computePerimeter is being called
6
Hexagon::computePerimeter is being called
6

*/
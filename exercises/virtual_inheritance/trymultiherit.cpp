#include "TextBox.hpp"
#include <iostream>

int main() {
    TextBox a("hop",1,3);
    // create a TextBox and call draw
    //a.draw()
    a.draw();
    Rectangle &b=a;
    b.draw();
    Text &c=a;
    c.draw();
    // Fix the code to call both draws by using types


    // try with virtual inheritance
    //TextBox.cpp:16:10: error: constructor for 'TextBox' must explicitly initialize the base class 'Drawable' which does not have a default constructor
    //переделал: теперь
    //Drawing 3
    //Drawing 3
    //Drawing 3



}

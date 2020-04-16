#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <windows.h>

class Element
{
private:

    typedef unsigned char uc;

    uc symbol;
    uc color;
    uc x;
    uc y;

    void gotoXY(uc x, uc y);

public:

    void setSymbol(uc s);
    uc getSymbol();
    void setColor(uc c);
    uc getColor();
    uc getY();
    void setY(uc value);
    uc getX();
    void setX(uc value);

    void show();
    void hide();

    Element();
};

#endif // ELEMENT_H

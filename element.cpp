#include "element.h"

Element::uc Element::getSymbol() {
    return symbol;
}

void Element::setSymbol(uc s) {
    symbol = s;
}

Element::uc Element::getColor() {
    return color;
}

void Element::setColor(uc c) {
    color = c;
}

Element::uc Element::getY() {
    return y;
}

void Element::setY(uc value) {
    y = value;
}

Element::uc Element::getX() {
    return x;
}

void Element::setX(uc value) {
    x = value;
}

void Element::show() {
    gotoXY(x, y);
    std::cout << static_cast<char>(symbol);
}

void Element::hide() {
    color = 0;
    symbol = ' ';
    show();
}

void Element::gotoXY( uc x, uc y ) {
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

Element::Element() : color(0)
{

}

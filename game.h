#ifndef GAME_H
#define GAME_H

#include "element.h"
#include <cstring>
#include <vector>

class Game {
private:
    const char FIELD_SIZE = 19;
    static const char NUMBER = 8;
    unsigned const char CORRECT_INPUT_DATA = 4;
    const char WHITE = 1;
    const char BLACK = 2;
    const char STEP = 2;
    const char MSG_X = 25;
    const char MSG_Y = 5;
    const char MAX_MSG_LENGTH = 40;

    std::string inputStr;


    bool turn;

    std::string msg;

    Element** field;

    char digits[NUMBER] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char letters[NUMBER] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    std::vector <Element> whites;
    std::vector <Element> blacks;

    void createField();
    void fillField();
    void showField();

    Element getFigure(char symbol, char color, char x, char y);
    void createFigures();

    void inputData(std::string str);
    void handleInputData(unsigned char srcX, unsigned char srcY, unsigned char dstX, unsigned char dstY);
    void move(unsigned char srcX, unsigned char srcY, unsigned char dstX, unsigned char dstY);

    bool checkMoveXOrY(char srcX, char srcY, char dstX, char dstY);
    bool checkMoveDiagonal(char srcX, char srcY, char dstX, char dstY);
    bool checkMoveKnight(char srcX, char srcY, char dstX, char dstY);
    bool checkMovePawn(char srcX, char srcY, char dstX, char dstY);
    bool checkMoveKing(char srcX, char srcY, char dstX, char dstY);

    bool safeFromKnight(char color, char x, char y);
    bool safeFromXorY(char color, char x, char y);
    bool safeFromDiagonal(char color, char x, char y);
    bool safeFromPawns(char color, char x, char y);
    bool safeFromKing(char color, char x, char y);

    void run();

    void gotoXY(char x, char y);
    void showMsg();
    void clearMsg();
    void welcomeMsg();
    void inputDataIncorectMsg();

    void freeMemory();

    void ShowConsoleCursor(bool showFlag);
public:
    Game();
    ~Game();
};

#endif // GAME_H

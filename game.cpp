#include "game.h"

Game::Game() : turn (true)
{
    ShowConsoleCursor(false);
    createField();
    fillField();
    showField();

    welcomeMsg();

    run();


//    inputStr = "e2e4";

//    inputData(inputStr);


//    inputData("e2e4");
//    inputData("f7f6");
//    inputData("e1e2");
//    inputData("e2e3");
//    inputData("e3f3");

//    inputData("f3f4");
//    inputData("f4f5");
}

Game::~Game() {
    freeMemory();
}

void Game::createField() {
    field = new Element*[FIELD_SIZE];
    for (int i= 0; i < FIELD_SIZE; ++i) {
        field[i] = new Element[FIELD_SIZE];
    }
}

void Game::fillField() {
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            if ( ((i % 2) == 0 && j == 0 && i > 0 && i < FIELD_SIZE - 1)
                    || ((i % 2) == 0 && j == FIELD_SIZE - 1 && i > 0 && i < FIELD_SIZE - 1) ) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(digits[(i / 2) - 1]);
            }
            else if (((j % 2) == 0 && i == 0 && j > 0 && j < FIELD_SIZE - 1)
                     || ((j % 2) == 0 && i == FIELD_SIZE - 1 && j > 0 && j < FIELD_SIZE - 1)) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(letters[(j / 2) - 1]);
            }
            else if (i > 0 && i < FIELD_SIZE - 1 && (i % 2) == 0 && (j % 2) != 0) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(179);
            }
            else if (j > 0 && j < FIELD_SIZE - 1 && (j % 2) == 0 && (i % 2) != 0) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(196);
            }
            else if (i > 1 && j > 1 && i < FIELD_SIZE - 1 - 1 && j < FIELD_SIZE - 1 - 1
                     && (i % 2) != 0 && (j % 2) != 0) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(197);
            }
            else if (i == 1 && j > 1 && j < FIELD_SIZE - 1 - 1 && (j % 2) != 0) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(194);
            }
            else if (i == FIELD_SIZE - 1 - 1 && j > 1 && j < FIELD_SIZE - 1 - 1) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(193);
            }
            else if (j == 1 && i > 1 && i < FIELD_SIZE - 1 - 1 && (i % 2) != 0) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(195);
            }
            else if (j == FIELD_SIZE - 1 - 1 && i > 1 && i < FIELD_SIZE - 1 - 1 && (i % 2) != 0) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(180);
            }
            else if (i == 1 && j == 1) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(218);
            }
            else if (i == 1 && j == FIELD_SIZE - 1 - 1) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(191);
            }
            else if (i == FIELD_SIZE - 1 - 1 && j == FIELD_SIZE - 1 - 1) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(217);
            }
            else if (i == FIELD_SIZE - 1 - 1 && j == 1) {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(192);
            }
            else {
                field[i][j].setX(j);
                field[i][j].setY(i);
                field[i][j].setSymbol(' ');
            }
        }
    }
    createFigures();
    for (int i = 0; i < NUMBER * 2; ++i) {
        field[whites.at(i).getY()][whites.at(i).getX()] = whites.at(i);
        field[blacks.at(i).getY()][blacks.at(i).getX()] = blacks.at(i);
    }
}

void Game::showField() {
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            field[i][j].show();
        }
    }
}

Element Game::getFigure(char symbol, char color, char x, char y) {
    Element e;
    e.setSymbol(symbol);
    e.setColor(color);
    e.setX(x);
    e.setY(y);
    return e;
}

void Game::createFigures() {
    whites.push_back(getFigure('R', WHITE, 2, 2));
    whites.push_back(getFigure('N', WHITE, 4, 2));
    whites.push_back(getFigure('B', WHITE, 6, 2));
    whites.push_back(getFigure('Q', WHITE, 8, 2));
    whites.push_back(getFigure('K', WHITE, 10, 2));
    whites.push_back(getFigure('B', WHITE, 12, 2));
    whites.push_back(getFigure('N', WHITE, 14, 2));
    whites.push_back(getFigure('R', WHITE, 16, 2));
    for (int i = 0; i < NUMBER; ++i) {
        whites.push_back(getFigure('P', WHITE,(i + 1) * 2, 4));
    }

    blacks.push_back(getFigure('r', BLACK, 2, FIELD_SIZE - 3));
    blacks.push_back(getFigure('n', BLACK, 4, FIELD_SIZE - 3));
    blacks.push_back(getFigure('b', BLACK, 6, FIELD_SIZE - 3));
    blacks.push_back(getFigure('q', BLACK, 8, FIELD_SIZE - 3));
    blacks.push_back(getFigure('k', BLACK, 10, FIELD_SIZE - 3));
    blacks.push_back(getFigure('b', BLACK, 12, FIELD_SIZE - 3));
    blacks.push_back(getFigure('n', BLACK, 14, FIELD_SIZE - 3));
    blacks.push_back(getFigure('r', BLACK, 16, FIELD_SIZE - 3));
    for (int i = 0; i < NUMBER; ++i) {
        blacks.push_back(getFigure('p', BLACK,(i + 1) * 2, FIELD_SIZE - 5));
    }
}

void Game::inputData(std::string str) {

    if (str.length() == CORRECT_INPUT_DATA) {

        unsigned char srcX, srcY, dstX, dstY;

        switch (str[0]) {
        case 'a' :
            srcX = 2;
            break;
        case 'b' :
            srcX = 4;
            break;
        case 'c' :
            srcX = 6;
            break;
        case 'd' :
            srcX = 8;
            break;
        case 'e' :
            srcX = 10;
            break;
        case 'f' :
            srcX = 12;
            break;
        case 'g' :
            srcX = 14;
            break;
        case 'h' :
            srcX = 16;
            break;
        default:
            inputDataIncorectMsg();
            break;
        }

        switch (str[1]) {
        case '1' :
            srcY = 2;
            break;
        case '2' :
            srcY = 4;
            break;
        case '3' :
            srcY = 6;
            break;
        case '4' :
            srcY = 8;
            break;
        case '5' :
            srcY = 10;
            break;
        case '6' :
            srcY = 12;
            break;
        case '7' :
            srcY = 14;
            break;
        case '8' :
            srcY = 16;
            break;
        default:
            inputDataIncorectMsg();
            break;
        }

        switch (str[2]) {
        case 'a' :
            dstX = 2;
            break;
        case 'b' :
            dstX = 4;
            break;
        case 'c' :
            dstX = 6;
            break;
        case 'd' :
            dstX = 8;
            break;
        case 'e' :
            dstX = 10;
            break;
        case 'f' :
            dstX = 12;
            break;
        case 'g' :
            dstX = 14;
            break;
        case 'h' :
            dstX = 16;
            break;
        default:
            inputDataIncorectMsg();
            break;
        }

        switch (str[3]) {
        case '1' :
            dstY = 2;
            break;
        case '2' :
            dstY = 4;
            break;
        case '3' :
            dstY = 6;
            break;
        case '4' :
            dstY = 8;
            break;
        case '5' :
            dstY = 10;
            break;
        case '6' :
            dstY = 12;
            break;
        case '7' :
            dstY = 14;
            break;
        case '8' :
            dstY = 16;
            break;
        default:
            inputDataIncorectMsg();
            break;
        }

        if (field[srcY][srcX].getColor() == WHITE && !turn) {
            msg = "It isn't your figure";
            showMsg();
            return;
        }

        else if (field[srcY][srcX].getColor() == BLACK && turn) {
            msg = "It isn't your figure";
            showMsg();
            return;
        }

        handleInputData(srcX, srcY, dstX, dstY);

        turn = !turn;
    }
    else {
        inputDataIncorectMsg();
    }
}

void Game::handleInputData(unsigned char srcX, unsigned char srcY, unsigned char dstX, unsigned char dstY) {
    unsigned char figure = field[srcY][srcX].getSymbol();

    switch (figure) {
    case 'R' :
        if (checkMoveXOrY(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'N' :
        if (checkMoveKnight(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'B' :
        if (checkMoveDiagonal(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'Q' :
        if (checkMoveDiagonal(srcX, srcY, dstX, dstY) || checkMoveXOrY(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'K' :
        if (checkMoveKing(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'P' :
        if (checkMovePawn(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'r' :
        if (checkMoveXOrY(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'n' :
        if (checkMoveKnight(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'b' :
        if (checkMoveDiagonal(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'q' :
        if (checkMoveDiagonal(srcX, srcY, dstX, dstY) || checkMoveXOrY(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'k' :
        if (checkMoveKing(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    case 'p' :
        if (checkMovePawn(srcX, srcY, dstX, dstY)) {
            move(srcX, srcY, dstX, dstY);
        }
        break;
    default:
        break;
    }
}

bool Game::checkMoveXOrY(char srcX, char srcY, char dstX, char dstY) {
    unsigned char tmpX = srcX, tmpY = srcY;

    if (field[dstY][dstX].getColor() == field[srcY][srcX].getColor()) {
        return false;
    }
    else if (srcX == dstX) {

        if (srcY < dstY) {
            tmpY = srcY + 2;
            while (tmpY != dstY) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpY += 2;
            }

        }
        else {
            tmpY = srcY - 2;
            while (tmpY != dstY) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpY -= 2;
            }
        }
        return true;

    }
    else if (srcY == dstY) {

        if (srcX < dstX) {
            tmpX = srcX + 2;
            while (tmpX != dstX) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpX += 2;
            }

        }
        else {
            tmpX = srcX - 2;
            while (tmpX != dstX) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpX -= 2;
            }
        }
        return true;

    }
    else {
        return false;
    }
}

bool Game::checkMoveDiagonal(char srcX, char srcY, char dstX, char dstY) {
    unsigned char tmpX = srcX, tmpY = srcY;
    if (field[dstY][dstX].getColor() == field[srcY][srcX].getColor()) {
        return false;
    }
    else if (abs(dstX - srcX) == abs(dstY - srcY)) {

        if (dstX > srcX && dstY > srcY) {
            tmpX = srcX + 2;
            tmpY = srcY + 2;
            while (tmpX != dstX || tmpY != dstY) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpX += 2;
                tmpY += 2;
            }
            return true;
        }
        else if (dstX > srcX && dstY < srcY) {
            tmpX = srcX + 2;
            tmpY = srcY - 2;
            while (tmpX != dstX || tmpY != dstY) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpX += 2;
                tmpY -= 2;
            }
            return true;
        }
        else if (dstX < srcX && dstY > srcY) {
            tmpX = srcX - 2;
            tmpY = srcY + 2;
            while (tmpX != dstX || tmpY != dstY) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpX -= 2;
                tmpY += 2;
            }
            return true;
        }
        else if (dstX < srcX && dstY < srcY) {
            tmpX = srcX - 2;
            tmpY = srcY - 2;
            while (tmpX != dstX || tmpY != dstY) {
                if(field[tmpY][tmpX].getSymbol() != ' ') {
                    return false;
                }
                tmpX -= 2;
                tmpY -= 2;
            }
            return true;
        }
    }
    return false;
}

bool Game::checkMoveKnight(char srcX, char srcY, char dstX, char dstY) {
    if (dstX == srcX + 4 && dstY == srcY + 2) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX + 4 && dstY == srcY - 2) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX + 2 && dstY == srcY + 4) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX + 2 && dstY == srcY - 4) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX - 4 && dstY == srcY + 2) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX - 4 && dstY == srcY - 2) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX - 2 && dstY == srcY + 4) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    else if (dstX == srcX - 2 && dstY == srcY - 4) {
        if (field[dstY][dstX].getSymbol() == ' ' || (field[dstY][dstX].getColor() != field[srcY][srcX].getColor())) {
            return true;
        }
    }
    return false;
}

bool Game::checkMovePawn(char srcX, char srcY, char dstX, char dstY) {

    if (field[srcY][srcX].getColor() == WHITE) {

        if (srcY == 4 && (dstX == srcX && dstY == srcY + 4) && field[dstY][dstX].getSymbol() == ' ') { // first step
            return true;
        }
        else if ((dstX == srcX && dstY == srcY + 2) && field[dstY][dstX].getSymbol() == ' ') { // step forward
            if (dstY == 16) { // Casying pawn to quin
                field[srcY][srcX].setSymbol('Q');
            }
            return true;
        }
        else if ((dstX == srcX + 2 || dstX == srcX - 2) &&// attack
                 dstY == srcY + 2 && (field[dstY][dstX].getColor() == BLACK && field[dstY][dstX].getSymbol() != ' ')) {
            if (dstY == 16) { // Casying pawn to quin
                field[srcY][srcX].setSymbol('Q');
            }
            return true;
        }
    }

    else if (field[srcY][srcX].getColor() == BLACK) {
        if (srcY == 14 && (dstX == srcX && dstY == srcY - 4) && field[dstY][dstX].getSymbol() == ' ') {
            return  true;
        }
        else if ((dstX == srcX && dstY == srcY - 2) && field[dstY][dstX].getSymbol() == ' ') {
            if (dstY == 2) { // Casying pawn to quin
                field[srcY][srcX].setSymbol('Q');
            }
            return true;
        }
        else if ((dstX == srcX + 2 || dstX == srcX - 2) &&
                 dstY == srcY - 2 && (field[dstY][dstX].getColor() == WHITE && field[dstY][dstX].getSymbol() != ' ')) {
            if (dstY == 2) { // Casying pawn to quin
                field[srcY][srcX].setSymbol('Q');
            }
            return true;
        }
    }
    return false;
}

bool Game::checkMoveKing(char srcX, char srcY, char dstX, char dstY) { // do we can go to dst

    if (abs(dstX - srcX) > 2 || abs(dstY - srcY) > 2) {
        return false;
    }

    else if (field[dstY][dstX].getSymbol() != ' ' && field[dstY][dstX].getColor() == field[srcY][srcX].getColor()) {
        return false;
    }
    else if (field[dstY][dstX].getSymbol() != ' ' && field[dstY][dstX].getColor() != field[srcY][srcX].getColor()) {
        if (safeFromKing(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromXorY(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromPawns(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromKnight(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromDiagonal(field[srcY][srcX].getColor(), dstX, dstY)) {
            return true;
        }
    }
    else if (field[dstY][dstX].getSymbol() == ' ') {
        if (safeFromKing(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromXorY(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromPawns(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromKnight(field[srcY][srcX].getColor(), dstX, dstY) &&
                safeFromDiagonal(field[srcY][srcX].getColor(), dstX, dstY)) {
            return true;
        }
    }
    return false;
}


bool Game::safeFromKnight(char color, char x, char y) { // if cell isn't safe returns false
    if (color == WHITE) {
        if (field[y + 2][x + 4].getSymbol() == 'n') {
            return false;
        }
        if (field[y - 2][x + 4].getSymbol() == 'n') {
            return false;
        }
        if (field[y + 4][x + 2].getSymbol() == 'n') {
            return false;
        }
        if (field[y - 4][x + 2].getSymbol() == 'n') {
            return false;
        }
        if (field[y + 2][x - 4].getSymbol() == 'n') {
            return false;
        }
        if (field[y - 2][x - 4].getSymbol() == 'n') {
            return false;
        }
        if (field[y + 4][x - 2].getSymbol() == 'n') {
            return false;
        }
        if (field[y - 4][x - 2].getSymbol() == 'n') {
            return false;
        }
    }
    else if (color == BLACK) {
        if (field[y + 2][x + 4].getSymbol() == 'N') {
            return false;
        }
        if (field[y - 2][x + 4].getSymbol() == 'N') {
            return false;
        }
        if (field[y + 4][x + 2].getSymbol() == 'N') {
            return false;
        }
        if (field[y - 4][x + 2].getSymbol() == 'N') {
            return false;
        }
        if (field[y + 2][x - 4].getSymbol() == 'N') {
            return false;
        }
        if (field[y - 2][x - 4].getSymbol() == 'N') {
            return false;
        }
        if (field[y + 4][x - 2].getSymbol() == 'N') {
            return false;
        }
        if (field[y - 4][x - 2].getSymbol() == 'N') {
            return false;
        }
    }
    return true;
}

bool Game::safeFromXorY(char color, char x, char y) { // if cell isn't safe returns false
    bool safety = true;
    char tmpX = x, tmpY = y;

    if (color == WHITE) {

        while (tmpY >= 2 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'r' || field[tmpY][tmpX].getSymbol() == 'q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'r' || field[tmpY][tmpX].getSymbol() != 'q') {
                break;
            }
            tmpY -= 2;
        }
        tmpY = y;

        while (tmpY <= 16 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'r' || field[tmpY][tmpX].getSymbol() == 'q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'r' || field[tmpY][tmpX].getSymbol() != 'q') {
                break;
            }
            tmpY += 2;
        }
        tmpY = y;

        while (tmpX >= 2 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'r' || field[tmpY][tmpX].getSymbol() == 'q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'r' || field[tmpY][tmpX].getSymbol() != 'q') {
                break;
            }
            tmpX -= 2;
        }
        tmpX = x;

        while (tmpX <= 16 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'r' || field[tmpY][tmpX].getSymbol() == 'q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'r' || field[tmpY][tmpX].getSymbol() != 'q') {
                break;
            }
            tmpY += 2;
        }
        tmpX = x;

    }
    else if (color == BLACK) {

        while (tmpY >= 2 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'R' || field[tmpY][tmpX].getSymbol() == 'Q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'R' || field[tmpY][tmpX].getSymbol() != 'Q') {
                break;
            }
            tmpY -= 2;
        }
        tmpY = y;

        while (tmpY <= 16 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'R' || field[tmpY][tmpX].getSymbol() == 'Q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'R' || field[tmpY][tmpX].getSymbol() != 'Q') {
                break;
            }
            tmpY += 2;
        }
        tmpY = y;

        while (tmpX >= 2 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'R' || field[tmpY][tmpX].getSymbol() == 'Q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'R' || field[tmpY][tmpX].getSymbol() != 'Q') {
                break;
            }
            tmpX -= 2;
        }
        tmpX = x;

        while (tmpX <= 16 && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'R' || field[tmpY][tmpX].getSymbol() == 'Q') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'R' || field[tmpY][tmpX].getSymbol() != 'Q') {
                break;
            }
            tmpY += 2;
        }
        tmpX = x;
    }


    return safety;
}

bool Game::safeFromDiagonal(char color, char x, char y) { // if cell isn't safe returns false
    bool safety = true;
    char tmpX = x, tmpY = y;

    if (color == WHITE) {

        while ((tmpX >= 2 || tmpY >= 2) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'q' || field[tmpY][tmpX].getSymbol() == 'b') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'q' || field[tmpY][tmpX].getSymbol() != 'b') {
                break;
            }
            tmpX -= 2;
            tmpY -= 2;
        }
        tmpX = x;
        tmpY = y;

        while ((tmpX <= 16 || tmpY >= 2) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'q' || field[tmpY][tmpX].getSymbol() == 'b') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'q' || field[tmpY][tmpX].getSymbol() != 'b') {
                break;
            }
            tmpX += 2;
            tmpY -= 2;
        }
        tmpX = x;
        tmpY = y;

        while ((tmpX >= 2 || tmpY <= 16) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'q' || field[tmpY][tmpX].getSymbol() == 'b') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'q' || field[tmpY][tmpX].getSymbol() != 'b') {
                break;
            }
            tmpX -= 2;
            tmpY += 2;
        }
        tmpX = x;
        tmpY = y;

        while ((tmpX <= 16 || tmpY <= 16) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'q' || field[tmpY][tmpX].getSymbol() == 'b') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'q' || field[tmpY][tmpX].getSymbol() != 'b') {
                break;
            }
            tmpX += 2;
            tmpY += 2;
        }
        tmpX = x;
        tmpY = y;

    }
    else if (color == BLACK) {

        while ((tmpX >= 2 || tmpY >= 2) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'Q' || field[tmpY][tmpX].getSymbol() == 'B') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'Q' || field[tmpY][tmpX].getSymbol() != 'B') {
                break;
            }
            tmpX -= 2;
            tmpY -= 2;
        }
        tmpX = x;
        tmpY = y;

        while ((tmpX >= 16 || tmpY <= 2) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'Q' || field[tmpY][tmpX].getSymbol() == 'B') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'Q' || field[tmpY][tmpX].getSymbol() != 'B') {
                break;
            }
            tmpX += 2;
            tmpY -= 2;
        }
        tmpX = x;
        tmpY = y;

        while ((tmpX >= 2 || tmpY <= 16) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'Q' || field[tmpY][tmpX].getSymbol() == 'B') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'Q' || field[tmpY][tmpX].getSymbol() != 'B') {
                break;
            }
            tmpX -= 2;
            tmpY += 2;
        }
        tmpX = x;
        tmpY = y;

        while ((tmpX <= 16 || tmpY <= 16) && safety) {
            if (field[tmpY][tmpX].getSymbol() == 'Q' || field[tmpY][tmpX].getSymbol() == 'B') {
                safety = false;
            }
            else if (field[tmpY][tmpX].getColor() == color || field[tmpY][tmpX].getSymbol() != 'Q' || field[tmpY][tmpX].getSymbol() != 'B') {
                break;
            }
            tmpX += 2;
            tmpY += 2;
        }
        tmpX = x;
        tmpY = y;
    }

    return safety;
}

bool Game::safeFromPawns(char color, char x, char y) { // if cell isn't safe returns false
    bool safety = true;

    if (color == WHITE) {

        if (field[y - 2][x - 2].getSymbol() == 'p' || field[y - 2][x + 2].getSymbol() == 'p') {
            safety = false;
        }
    }

    else if (color == BLACK) {

        if (field[y + 2][x - 2].getSymbol() == 'P' || field[y + 2][x + 2].getSymbol() == 'P') {
            safety = false;
        }
    }

    return safety;
}

bool Game::safeFromKing(char color, char x, char y) { // if cell isn't safe returns false
    bool safety = true;

    if (color == WHITE) {

        if (field[y][x + 2].getSymbol() == 'k' || field[y][x - 2].getSymbol() == 'k' ||
                field[y + 2][x].getSymbol() == 'k' || field[y - 2][x].getSymbol() == 'k') {
            safety = false;
        }
    }

    else if (color == BLACK) {

        if (field[y][x + 2].getSymbol() == 'K' || field[y][x - 2].getSymbol() == 'K' ||
                field[y + 2][x].getSymbol() == 'K' || field[y - 2][x].getSymbol() == 'K') {
            safety = false;
        }
    }

    return safety;
}

void Game::move(unsigned char srcX, unsigned char srcY, unsigned char dstX, unsigned char dstY) {

    field[dstY][dstX].setColor(field[srcY][srcX].getColor());
    field[dstY][dstX].setSymbol(field[srcY][srcX].getSymbol());

    field[srcY][srcX].hide();
    field[dstY][dstX].show();
}


void Game::gotoXY( char x, char y ) {
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void Game::showMsg() {
    gotoXY(MSG_X, MSG_Y);
    std::cout << msg;
    Sleep(1500);
    clearMsg();
}

void Game::clearMsg() {
    gotoXY(MSG_X, MSG_Y);
    for (int  i = 0; i < MAX_MSG_LENGTH; ++i) {
        std::cout << " ";
    }
}

void Game::welcomeMsg() {
    gotoXY(MSG_X, MSG_Y - 4);
    std::cout << "Whites on top, blacks on bottom";
    gotoXY(MSG_X, MSG_Y - 3);
    std::cout << "Input your move as a single four character string. Example: e2e4";
    gotoXY(MSG_X, MSG_Y - 2);
    std::cout << "Input: " ;
}

void Game::inputDataIncorectMsg() {
    msg = "Incorect input!!";
    showMsg();
}

void Game::freeMemory() {
    for (int i= 0; i < FIELD_SIZE; ++i) {
        delete[] field[i];
    }
    delete[] field;
}

void Game::ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


void Game::run() {
    while (true) {
        gotoXY(MSG_X, MSG_Y);
        std::cin >> inputStr;
        gotoXY(MSG_X, MSG_Y);
        std::cout << "        ";
        inputData(inputStr);
    }
}

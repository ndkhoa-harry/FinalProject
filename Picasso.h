#ifndef _PICASSO_H_
#define _PICASSO_H_

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

/// WINDOWS
const int WINDOW_HEIGHT = 32;
const int WINDOW_WIDTH = 128;

void initWindowSize() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 953, 550, TRUE); 
}

void gotoXY(short int x, short int y) {
    static HANDLE h = NULL;  
    if(!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { y, x };  
    SetConsoleCursorPosition(h,c);
}

/// DESIGN
const int KEY_UP = 72;
const int KEY_LEFT = 75;
const int KEY_DOWN = 80;
const int KEY_RIGHT = 77;

const int KEY_ENTER = 13;
const int KEY_BACKSPACE = 8;

const char CHAR_VERTICAL = char(179);               // |
const char CHAR_HORIZONTAL = char(196);             // -
const char CHAR_VERTICAL_HORIZONTAL = char(197);    // +

void drawMenu(int titleLines, const string* title, int optionsCount, const string* options, int &choice) {
    system("cls");

    int startX = (WINDOW_HEIGHT - titleLines - optionsCount * 3) / 2 - 1;
    int x = startX;

    if (titleLines == 0) {
        startX -= 3;
        x -= 3;
    }

    if (startX < 0) {
        startX = 1;
        x = 1;
    }

    for (int i = 0; i < titleLines; ++i) {
        gotoXY(x, (WINDOW_WIDTH - title[i].size()) / 2 - 1);
        cout << title[i];
        ++x;
    }

    for (int i = 0; i < optionsCount; ++i) {
        x += 3;

        gotoXY(x, (WINDOW_WIDTH - options[i].size()) / 2 - 1);
        cout << options[i];
    }

    while (1) {
        gotoXY(startX + titleLines + 3 + choice * 3, (WINDOW_WIDTH - options[choice].size()) / 2 - 4);
        cout << ">> " << options[choice] << " <<";

        char c = getch();

        gotoXY(startX + titleLines + 3 + choice * 3, (WINDOW_WIDTH - options[choice].size()) / 2 - 4);
        cout << "   " << options[choice] << "   ";

        switch (int(c)) {
            case KEY_UP:
                choice = (choice + optionsCount - 1) % optionsCount;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % optionsCount;
                break;
            case KEY_ENTER:
                return;
            case KEY_BACKSPACE:
                choice = -1;
                return;
        }
    }
}

void drawTable(int startX, string tableTitle, int columnsCount, int* columnsWidth, string* columnsName, int rowsCount, string** table) {
    gotoXY(startX, (WINDOW_WIDTH - tableTitle.size()) / 2);
    cout << tableTitle;

    int columnsWidthSum = 0;
    for (int i = 0; i < columnsCount; ++i) 
        columnsWidthSum += columnsWidth[i];

    int x = startX + 2;
    int startY = (WINDOW_WIDTH - columnsWidthSum - columnsCount + 1) / 2 - 1;
    int y = startY;

    if (startY < 0) startY = y = 0;

    gotoXY(x + 1, startY);
    for (int i = 0; i < columnsWidthSum + columnsCount - 1; ++i) 
        cout << CHAR_HORIZONTAL;

    gotoXY(x, y + (columnsWidth[0] - columnsName[0].size()) / 2);
    cout << columnsName[0];

    for (int i = 1; i < columnsCount; ++i) {
        y += columnsWidth[i - 1];

        gotoXY(x, y);
        cout << CHAR_VERTICAL;

        gotoXY(x + 1, y);
        cout << CHAR_VERTICAL_HORIZONTAL;

        ++y;

        gotoXY(x, y + (columnsWidth[i] - columnsName[i].size()) / 2);
        cout << columnsName[i];
    }

    ++x;
    /*gotoXY(x, startY);
    for (int i = 0; i < columnsWidthSum + columnsCount - 1; ++i) 
        cout << '-';*/

    for (int i = 0; i < rowsCount; ++i) {
        ++x;
        y = startY;
        
        gotoXY(x, y + (columnsWidth[0] - table[0][0].size()) / 2);
        cout << table[i][0];

        for (int j = 1; j < columnsCount; ++j) {
            y += columnsWidth[j - 1];

            gotoXY(x, y);
            cout << CHAR_VERTICAL;
            ++y;

            gotoXY(x, y + (columnsWidth[j] - table[i][j].size()) / 2);
            cout << table[i][j];
        }

        cout << '\n';
    }
}

#endif
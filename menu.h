#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "sign.h"
#include "grid.h"

class Menu
{
public:
    Menu();

    void topMenu();
    void botMenu();

    float topMenuLow = .1;
    float topMenuHigh = .2;
    int topMenuSpacer = 2;

    float botBtnLow = -.3;
    float botBtnHigh = -.1;

    bool botLeftHover = false;
    bool botRightHover = false;
};

#endif // MENU_H

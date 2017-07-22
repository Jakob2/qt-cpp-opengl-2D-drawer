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

    float botBigLow = -.5;
    float botBigHigh = -.3;

    bool botLeftHover = false;
    bool botRightHover = false;
    bool botBigHover = false;
};

#endif // MENU_H

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
    void arrow();
    void overtopMenu();
    void leftMenu();

    float topMenuLow = .1;
    float topMenuHigh = .2;
    int topMenuSpacer = 2;
    int topMenuHighlight = 2;

    float botBtnLow = -.3;
    float botBtnHigh = -.1;

    float botBigLow = -.5;
    float botBigHigh = -.3;

    float overtopLow = .3;
    float overtopHigh = .5;

    float leftMenuLow = 0;
    float leftMenuHigh = 0.075;

    bool botLeftHover = false;
    bool botRightHover = false;
    bool botBigHover = false;
    bool leftArrowHover = false;
    bool rightArrowHover = false;
    bool bigRangeHover = false;
    bool mediumRangeHover = false;
    bool smallRangeHover = false;
    bool leftMenuHover = false;

    int topMax;
    void setTopMax();
    int shift = 0;
};

#endif // MENU_H

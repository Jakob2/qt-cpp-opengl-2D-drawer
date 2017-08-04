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

    float topMenuLow = .1;
    float topMenuHigh = .2;
    int topMenuSpacer = 2;
    int topMenuHighlight = 1;

    float botBtnLow = -.3;
    float botBtnHigh = -.1;

    float botBigLow = -.5;
    float botBigHigh = -.3;

    float overtopLow = .3;
    float overtopHigh = .5;

    bool botLeftHover = false;
    bool botRightHover = false;
    bool botBigHover = false;
    bool leftArrowHover = false;
    bool rightArrowHover = false;
    bool bigRangeHover = false;
    bool mediumRangeHover = false;
    bool smallRangeHover = false;

    int topMax;
    void setTopMax();
    int shift = 0;
};

#endif // MENU_H

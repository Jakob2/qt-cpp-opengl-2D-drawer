#include "menu.h"

Menu::Menu(){

}

void Menu::topMenu(){
    bool clr = false;
    for(float x=topMenuSpacer; x<topMax+topMenuSpacer; x++){
        glBegin(GL_POLYGON);
        if(clr) glColor3f(0,0,0.5);
        if(!clr) glColor3f(0,0.5,0);
        glVertex2f(x/10+0, Grid::high+topMenuLow);
        glVertex2f(x/10+0, Grid::high+topMenuHigh);
        glVertex2f(x/10+.1, Grid::high+topMenuHigh);
        glVertex2f(x/10+.1, Grid::high+topMenuLow);
        glEnd();
        clr == false ? clr = true : clr = false;
    }
}

void Menu::botMenu(){
    glBegin(GL_POLYGON);
    glColor3f(0,0.5,0);
    if(botLeftHover) glColor3f(0.5,0.5,0);
    glVertex2f(Grid::low, Grid::low+botBtnHigh);
    glVertex2f(Grid::low, Grid::low+botBtnLow);
    glVertex2f(Grid::high/2, Grid::low+botBtnLow);
    glVertex2f(Grid::high/2, Grid::low+botBtnHigh);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    if(botRightHover) glColor3f(0.5,0.5,0);
    glVertex2f(Grid::high/2, Grid::low+botBtnHigh);
    glVertex2f(Grid::high/2, Grid::low+botBtnLow);
    glVertex2f(Grid::high, Grid::low+botBtnLow);
    glVertex2f(Grid::high, Grid::low+botBtnHigh);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0.5);
    if(botBigHover) glColor3f(0.5,0.5,0);
    glVertex2f(Grid::low, Grid::low+botBigHigh);
    glVertex2f(Grid::low, Grid::low+botBigLow);
    glVertex2f(Grid::high, Grid::low+botBigLow);
    glVertex2f(Grid::high, Grid::low+botBigHigh);
    glEnd();
}

void Menu::arrow(){
    glBegin(GL_POLYGON);
    glColor3f(0.2,0.4,0.7);
    if(leftArrowHover) glColor3f(0.5,0.5,0);
    glVertex2f(Grid::low+0, Grid::high+topMenuLow);
    glVertex2f(Grid::low+0, Grid::high+topMenuHigh);
    glVertex2f(Grid::low+.1, Grid::high+topMenuHigh);
    glVertex2f(Grid::low+.1, Grid::high+topMenuLow);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2,0.4,0.7);
    if(rightArrowHover) glColor3f(0.5,0.5,0);
    glVertex2f(Grid::high-.1, Grid::high+topMenuLow);
    glVertex2f(Grid::high-.1, Grid::high+topMenuHigh);
    glVertex2f(Grid::high, Grid::high+topMenuHigh);
    glVertex2f(Grid::high, Grid::high+topMenuLow);
    glEnd();
}

void Menu::setTopMax(){
    if((int)Sign::set.size()<26) topMax = (int)Sign::set.size();
    else topMax = 26;
}


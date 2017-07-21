#include "menu.h"

Menu::Menu(){

}

void Menu::topMenu(){
    bool clr = false;
    for(float x=topMenuSpacer; x<(int)Sign::set.size()+topMenuSpacer; x++){
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
}


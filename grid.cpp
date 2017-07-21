#include "grid.h"

float Grid::range;
float Grid::low;
float Grid::high;
float Grid::left;
float Grid::right;
float Grid::bottom;
float Grid::top;

Grid::Grid(){
    Grid::range = 30;
    Grid::high = Grid::range/10;
    Grid::low = 0;
    Grid::left = -0.1;
    Grid::right = 0.1;
    Grid::bottom = -0.4;
    Grid::top = 0.3;
}

void Grid::horizontal(){
    for(float y=0; y<Grid::range+1; y++){
        glBegin(GL_LINES);
        glColor3f(0,0,0);
        if(y==Grid::range/2) glColor3f(0,1,0);
        glLineWidth(2.0);
        glVertex2f(Grid::low,y/10);
        glVertex2f(Grid::high,y/10);
        glEnd();
    }
}

void Grid::vertical(){
    for(float x=0; x<Grid::range+1; x++){
        glBegin(GL_LINES);
        glColor3f(0,0,0);
        if(x==Grid::range/2) glColor3f(0,1,0);
        glLineWidth(2.0);
        glVertex2f(x/10,Grid::low);
        glVertex2f(x/10,Grid::high);
        glEnd();
    }
}


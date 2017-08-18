#include "sign.h"

std::vector<std::vector<std::vector<int>>> Sign::sign;
std::vector<int> Sign::set;
std::vector<int> Sign::master;

Sign::Sign(){
    Sign::initSigns();
}

void Sign::initSigns(){
    for(int i=0; i<1; i++){
        Sign::sign.push_back(std::vector<std::vector<int>>());
        for(int j=0; j<Grid::range/Grid::split; j++){
            Sign::sign[i].push_back(std::vector<int>());
            for(int k=0; k<Grid::range/Grid::split; k++){
                Sign::sign[i][j].push_back(0);
            }
        }
    }
}

void Sign::drawSign(){
    for(float x=0; x<(int)Sign::sign[0].size(); x++){
        for(float y=0; y<(int)Sign::sign[0][x].size(); y++){
            if(Sign::sign[0][x][y]){
                glBegin(GL_POLYGON);
                glColor3f(0,0,0);
                glVertex2f(x/10*Grid::split+0, y/10*Grid::split);
                glVertex2f(x/10*Grid::split+0, y/10*Grid::split+.1*Grid::split);
                glVertex2f(x/10*Grid::split+.1*Grid::split, y/10*Grid::split+.1*Grid::split);
                glVertex2f(x/10*Grid::split+.1*Grid::split, y/10*Grid::split);
                glEnd();
            }
        }
    }
}

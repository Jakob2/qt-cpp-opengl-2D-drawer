#ifndef GRID_H
#define GRID_H

#include "global.h"

class Grid
{
public:
    Grid();

    void horizontal();
    void vertical();

    static float range;
    static float low, high;
    static float left, right, bottom, top;
    static float split;

};

#endif // GRID_H

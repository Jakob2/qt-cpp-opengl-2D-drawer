#ifndef SIGN_H
#define SIGN_H

#include "global.h"
#include "grid.h"

class Sign
{
public:
    Sign();

    static std::vector<std::vector<std::vector<int>>> sign;
    static std::vector<int> set;
    static void initSigns();
    void drawSign();
};

#endif // SIGN_H

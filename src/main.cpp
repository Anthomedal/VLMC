#include<iostream>
#include<vector>
#include "VLMC.hpp"

/* CONVENTION :
Le terme le plus à gauche est le plus ancien
Le terme le plus à droite est le dernier terme */

int main()
{
    vector<int> x({6, 6, 6, 9, 6, 0, 1, 3, 1, 2, 6, 6, 9, 9, 3, 7, 8,10,
                6, 6, 4, 7, 4, 5, 5,7, 3, 4, 5, 5, 3, 4, 4, 5, 2, 6,
                6, 7, 6, 2, 4, 2, 3, 5, 9, 6, 2, 1, 9, 2,8, 4, 1, 3,
                6, 2, 9, 4, 4, 1, 5,10, 2, 7, 9, 7, 3, 7, 1, 3, 6, 6,
                3, 3,10, 2, 9, 3, 7, 2, 4, 1, 8, 8,10, 4, 5, 6,10, 6,
                4, 7, 9, 1, 1,10, 8, 1, 6, 3});

    VLMCModel V(x, 0.1);

    V.drawContextTree("h");

    return 0;
}

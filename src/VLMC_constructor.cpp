/*
Copyright 2019 Anthony Gerber-Roth
This file is part of VLMCContextAlgorithm.

VLMCContextAlgorithm is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

VLMCContextAlgorithm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with VLMCContextAlgorithm.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "VLMC.hpp"

VLMC::VLMC(vector<vector<int>> const& context_init, vector<int> const& alphabet_init)
{
    context = context_init;

    alphabet = alphabet_init;

    order = context_init[0].size();

    alphabet_size = alphabet_init.size();

    /* Il y a autant de probabilités de transitions que d'éléments dans
    l'alphabet et de contextes possibles */
    P.resize(context.size()*alphabet.size());

    int j;

    for (int i = 0; i < int(context.size()); i++)
    {
        for (j = 0; j < alphabet_size; j++)
        {
            P[i*alphabet_size+j].setKnowing(context[i]);
            P[i*alphabet_size+j].setPoint(alphabet[j]);
        }
    }
}

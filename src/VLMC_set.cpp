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

void VLMC::setProbabilities(vector<int> const& context_element, int point, double probability_value)
{
    /*
    Cette méthode permet de modifier la valeur de la probabilité de transition
    interne à la classe VLMC p(point|context_element) <- probability_value
    */

    for (int i = 0; i < int(P.size()); i++)
    {
        if (P[i].getKnowing() == context_element)
        {
            // On a trouvé la probabilité avec le bon contexte
            if (P[i].getPoint() == point)
            {
                // On a la probabilité voulue
                P[i].setValue(probability_value);

                // Le travail est terminé
                break;
            }
        }
    }
}

void VLMC::setProbabilities(int point, double probability_value)
{
    /*
    Cette méthode permet de modifier la valeur de la probabilité de transition
    interne à la classe VLMC p(point) <- probability_value
    */

    for (int i = 0; i < int(P.size()); i++)
    {
        if (P[i].getKnowing() == vector<int>(0))
        {
            // On a trouvé la probabilité avec contexte vide
            if (P[i].getPoint() == point)
            {
                // On a la probabilité voulue
                P[i].setValue(probability_value);

                // Le travail est terminé
                break;
            }
        }
    }
}

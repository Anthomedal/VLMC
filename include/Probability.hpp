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

#include<vector>
#include<iostream>

class Probability
{
/*
Cette classe permet de garder en mémoire les probabilités de transition
*/
public:
    // Constructeur
    Probability(double value_init, vector<int> const& knowing_init, int point_init);
    Probability();

    // Méthodes d'accés aux éléments
    double const& getValue() const;
    vector<int> const& getKnowing() const;
    int const& getPoint() const;

    // Méthodes de modification des valeurs
    void setValue(double new_value);
    void setKnowing(vector<int> const& new_knowing);
    void setPoint(int new_point);
private:
    // La valeur de la probabilité
    double value;

    // Le conditionnement
    vector<int> knowing;

    // Le point où on calcule la probabilité
    int point;
};

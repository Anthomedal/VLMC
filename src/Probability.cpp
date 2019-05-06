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

/*
Construction des méthodes de la classe Probability
*/

Probability::Probability(double value_init, vector<int> const& knowing_init, int point_init)
{
    value = value_init;
    knowing = knowing_init;
    point = point_init;
}

Probability::Probability()
{
    value = 0;
    knowing = vector<int>(0);
    point = 0;
}

double const& Probability::getValue() const
{
    return value;
}

vector<int> const& Probability::getKnowing() const
{
    return knowing;
}

int const& Probability::getPoint() const
{
    return point;
}

void Probability::setValue(double new_value)
{
    value = new_value;
}

void Probability::setKnowing(vector<int> const& new_knowing)
{
    knowing = new_knowing;
}

void Probability::setPoint(int new_point)
{
    point = new_point;
}

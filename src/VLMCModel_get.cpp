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

void VLMCModel::printContext()
{
    //Afficher(context);
    int n = context.size();

    for (int i = 0; i < n; i++)
    {
        cout << context[i].Rnombre() << " -> ";

        Afficher(context[i].Rsequence());
    }
}

vector<SequenceNombre> const& VLMCModel::getContext() const
{
    return context;
}

double const& VLMCModel::getCutoff() const
{
    return cutoff;
}

int const& VLMCModel::getOrder() const
{
    return order;
}

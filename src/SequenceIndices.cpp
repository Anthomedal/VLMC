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
Construction des méthodes de la classe SequenceIndices
*/

deque<int> const& SequenceIndices::Rsequence() const
{
    /*
    Cette fonction donne accés à l'élément sequence
    */

    return sequence;
}

vector<int> const& SequenceIndices::Rindices() const
{
    /*
    Cette fonction donne accés à l'élément indices
    */

    return indices;
}

void SequenceIndices::Msequence(deque<int> const& nouvelle_sequence)
{
    sequence = nouvelle_sequence;
}

void SequenceIndices::Mindices(vector<int> const& nouveaux_indices)
{
    indices = nouveaux_indices;
}

void SequenceIndices::Aindice(int const& indice)
{
    /*
    Cette fonction prend un indice et l'ajoute à la fin du vector indices
    */

    indices.push_back(indice);
}

void SequenceIndices::Aelement(int const& x)
{
    /*
    Cette fonction prend un élément et l'ajoute au début de la séquence
    */

    sequence.push_front(x);
}

void SequenceIndices::Sindice(int const& indice)
{
    /*
    Cette méthode supprime un indice contenu dans la liste d'indices
    */
    
    indices.erase(remove(indices.begin(), indices.end(), indice), indices.end());
}

bool operator==(SequenceIndices const& A, SequenceIndices const& B)
{
    /*
    Surchage de l'opérateur de comparaison
    */

    return ((A.Rsequence() == B.Rsequence()) && (A.Rindices() == B.Rindices()));
}

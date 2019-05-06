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
Construction des méthodes de la classe SequenceNombre
*/

SequenceNombre::SequenceNombre(deque<int> const& sequence_init, int const& nombre_init)
{
    sequence = sequence_init;
    nombre = nombre_init;
}

SequenceNombre::SequenceNombre()
{
    sequence = deque<int>(0);
    nombre = 0;
}

deque<int> const& SequenceNombre::Rsequence() const
{
    return sequence;
}

int const& SequenceNombre::Rnombre() const
{
    return nombre;
}

void SequenceNombre::Msequence(deque<int> const& nouvelle_sequence)
{
    sequence = nouvelle_sequence;
}

void SequenceNombre::Mnombre(int const& nouveau_nombre)
{
    nombre = nouveau_nombre;
}

bool operator==(SequenceNombre const& A, SequenceNombre const& B)
{
    /*
    Surchage de l'opérateur de comparaison
    */

    return ((A.Rsequence() == B.Rsequence()) && (A.Rnombre() == B.Rnombre()));
}

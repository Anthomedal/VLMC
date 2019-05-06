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
#include<deque>

using namespace std;

/*
On place dans ce fichier les déclaration de classes conteneurs permttant de
réaliser les étapes de l'algorithme
*/

class SequenceIndices
{
    /*
    On place dans ce conteneur une séquence et les indices auxquels elle est
    observée
    */
    public:
        // Acces aux éléments
        deque<int> const& Rsequence() const;
        vector<int> const& Rindices() const;

        // Modifier les valeurs
        void Msequence(deque<int> const& nouvelle_sequence);
        void Mindices(vector<int> const& nouveaux_indices);

        // Ajouter un indice
        void Aindice(int const& indice);

        // Ajouter un élément à la séquence
        void Aelement(int const& x);

        // Supprime un indice
        void Sindice(int const& indice);

    private:
        deque<int> sequence;
        vector<int> indices;
};

class SequenceNombre
{
    /*
    On place dans ce conteneur une séquence et le nombre de fois où elle est
    apparue
    */
    public:
        // Constructeurs
        SequenceNombre(deque<int> const& sequence_init, int const& nombre_init);
        SequenceNombre();

        // Acces aux éléments
        deque<int> const& Rsequence() const;
        int const& Rnombre() const;

        // Modifier les valeurs
        void Msequence(deque<int> const& nouvelle_sequence);
        void Mnombre(int const& nouveau_nombre);

    private:
        deque<int> sequence;
        int nombre;
};

// Opérateurs
bool operator==(SequenceNombre const& A, SequenceNombre const& B);
bool operator==(SequenceIndices const& A, SequenceIndices const& B);

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
Construction des fonctions ayant un rôle utilitaire dans les différents
algorithmes
*/

void Afficher(vector<int> const& w)
{
    int n = w.size();

    for (int i = 0; i < n; i++)
    {
        cout << w[i] << " ";
    }

    cout << endl;
}

void Afficher(deque<int> const& w)
{
    int n = w.size();

    for (int i = 0; i < n; i++)
    {
        cout << w[i] << " ";
    }

    cout << endl;
}

void Afficher(vector<vector<int>> const& w)
{
    int n = w.size();

    for (int i = 0; i < n; i++)
    {
        Afficher(w[i]);
    }
}

void Afficher(vector<SequenceNombre> const& w)
{
    int n = w.size();

    for (int i = 0; i < n; i++)
    {
        cout << w[i].Rnombre() << " -> ";
        Afficher(w[i].Rsequence());
    }
}

int Count(vector<int> const& X, deque<int> const& w)
{
    /*
    Description :
    Cette fonction compte le nombre d'occurence de la séquence w dans X
    */

    // On stocke la longueur des séquences
    int n = X.size();
    int l_w = w.size();

    // Compteur
    int k = 0;

    // Boucle
    int t;

    # pragma omp parallel for
    for (t = 0; t < n - l_w + 1; t++)
    {
        if (equal(&X[t], &X[t+l_w], &w[0]))
        {
            // On a détecté une occurence
            k = k+1;
        }
    }

    return k;
}

int Count(vector<int> const& X, vector<int> const& w)
{
    /*
    Description :
    Cette fonction compte le nombre d'occurence de la séquence w dans X
    */

    // On stocke la longueur des séquences
    int n = X.size();
    int l_w = w.size();

    // Compteur
    int k = 0;

    // Boucle
    int t;

    # pragma omp parallel for
    for (t = 0; t < n - l_w + 1; t++)
    {
        if (equal(&X[t], &X[t+l_w], &w[0]))
        {
            // On a détecté une occurence
            k = k+1;
        }
    }

    return k;
}

double Uniform()
{
    /*
    Simule la loi U([0,1])
    */

    return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}

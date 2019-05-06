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

double VLMCModel::TransitionProbability(int x, vector<int> const& y)
{
    /*
    Cette fonction calcule la probabilité de transition p(x|y)
    */

    // Taille du context
    int m = context.size();
    int k = y.size();

    int i;

    // Variables intermédiaires
    int taille_actuelle;
    deque<int> sequence;
    vector<int> x_w;

    for (i = 0; i < m; i++)
    {
        // On dispose d'un élément du contexte
        sequence = context[i].Rsequence();

        taille_actuelle = sequence.size();

        if (equal(&y[k - taille_actuelle], &y[k], &sequence[0]))
        {
            x_w.assign(sequence.begin(), sequence.end());
            x_w.push_back(x);

            // La portion récente a été trouvée dans le contexte
            return double(Count(donnees, x_w))/double(context[i].Rnombre());
        }
    }

    /* Si on arrive ici c'est que le passé récent ne fait pas parti de l'arbre
    de contexte, on a donc P(x|y) = P(x) */
    return double(Count(donnees, vector<int>(1,x))) / double(donnees.size());
}

int VLMCModel::SimulateValue(vector<int> const& recent_past)
{
    /*
    Cette fonction permet de simuler un nombre à la lumière des nombres précédents
    */

    // Génération de la variable uniforme dans [0,1]
    double u = Uniform();

    double p = 0.0;

    vector<int> alphabet_copy = alphabet;

    while (true) // On fait une boucle infinie pour être sur de sortir avec une valeur
    {
        for (int i = 0; i < alphabet_size; i++)
        {
            p = p + TransitionProbability(alphabet_copy[i], recent_past);

            if (u <= p)
            {
                return alphabet_copy[i];
            }
        }

        /* On a pas été en mesure de trouver : la somme des probabilités ne fait
        pas 1, on recommence en prenant soin de trier l'alphabet pour ne pas
        pénaliser les termes en fin d'alphabet */
        u = Uniform();
        p = 0.0;
        random_shuffle(alphabet_copy.begin(), alphabet_copy.end());
    }
}

vector<int> VLMCModel::Simulate(int length)
{
    /*
    Cette fonction permet de générer length nombres avec la loi de la VLMC
    */

    vector<int> recent_past(donnees.end() - order, donnees.end());

    vector<int> simulated_values(length);

    int simulated;

    // Boucle
    int j;

    for (int i = 0; i < length; i++)
    {
        // Simulation de la valeur
        simulated = SimulateValue(recent_past);

        // Actualisation du passé récent
        for (j = 0; j < order - 1; j++)
        {
            recent_past[j] = recent_past[j+1];
        }

        recent_past[order - 1] = simulated;

        // On enregistre la valeur simulée
        simulated_values[i] = simulated;
    }

    return simulated_values;
}

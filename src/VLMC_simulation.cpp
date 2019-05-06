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

double VLMC::p(int x, vector<int> y)
{
    /*
    Renvoie p(x|y)
    */

    for (int i = 0; i < int(P.size()); i++)
    {
        if (P[i].getKnowing() == y)
        {
            // On a trouvé la probabilité avec le bon contexte
            if (P[i].getPoint() == x)
            {
                // On a la probabilité voulue
                return P[i].getValue();

                // Le travail est terminé
                break;
            }
        }
    }

    // Problème dans l'utilisation de la fonction
    cout << "Unable to compute transition probability in VLMC : p(x|y)" << endl;
    exit(EXIT_FAILURE);
}

double VLMC::p(int x)
{
    /*
    Renvoie p(x)
    */

    for (int i = 0; i < int(P.size()); i++)
    {
        if (P[i].getKnowing() == vector<int>(0))
        {
            // On a trouvé la probabilité avec le bon contexte
            if (P[i].getPoint() == x)
            {
                // On a la probabilité voulue
                return P[i].getValue();

                // Le travail est terminé
                break;
            }
        }
    }

    // Problème dans l'utilisation de la fonction
    cout << "Unable to compute transition probability in VLMC" << endl;
    exit(EXIT_FAILURE);
}

double VLMC::TransitionProbability(int x, vector<int> const& y)
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
    vector<int> sequence;
    vector<int> x_w;

    for (i = 0; i < m; i++)
    {
        // On dispose d'un élément du contexte
        sequence = context[i];

        taille_actuelle = sequence.size();

        if (equal(&y[k - taille_actuelle], &y[k], &sequence[0]))
        {
            x_w.assign(sequence.begin(), sequence.end());
            x_w.push_back(x);

            // La portion récente a été trouvée dans le contexte
            return p(x, sequence);
        }
    }

    /* Si on arrive ici c'est que le passé récent ne fait pas parti de l'arbre
    de contexte, on a donc P(x|y) = P(x) */
    return p(x);
}

int VLMC::SimulateValue(vector<int> const& recent_past)
{
    /*
    Cette fonction permet de simuler un nombre à la lumière des nombres précédents
    */

    // Génération de la variable uniforme dans [0,1]
    double u = Uniform();

    double p = 0.0;

    vector<int> alphabet_copy = alphabet;

    while(true) // On fait une boucle infinie pour être sur de sortir avec une valeur
    {
        for (int i = 0; i < alphabet_size; i++)
        {
            p = p + TransitionProbability(alphabet_copy[i], recent_past);

            if (u <= p)
            {
                //cout << "on est dessus" << endl;
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

vector<int> VLMC::Simulate(int length)
{
    /*
    Cette fonction permet de générer length nombres avec la loi de la VLMC
    */

    // Boucle
    int j;

    int random_indice;

    vector<int> recent_past(order);

    // On définit aléatoirement le passé récent
    for (j = 0; j < order; j++)
    {
        random_indice = rand() % alphabet_size;

        recent_past[j] = alphabet[random_indice];
    }

    vector<int> simulated_values(length);

    int simulated;

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

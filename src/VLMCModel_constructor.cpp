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

VLMCModel::VLMCModel(vector<int> const& X, double const& C)
{
    /*
    Description :
    Cette fonction va estimer le contexte de chacun des nombre obtenus dans l'échantillon
    X de VLMC avec la tolérance C choisie par l'utilisateur
    */

    // On stocke la longueur de la série
    int n = X.size();

    // Cette variable permet de réaliser les étapes de la méthode
    vector<SequenceIndices> stockage;

    // Cet ensemble contiendra les séquences du contexte maximal
    vector<SequenceNombre> c_max;

    // Variable compteur
    int compteur = 1;

    // Variable permettant de manipuler plus efficacement les séquences
    SequenceIndices sequence_indices;

	// Variable de boucle
    int i, j;

    // On sauvegarde l'ensemble de toutes les valeurs possibles dans cette liste
    vector<int> E;

    /*
    PHASE 1
    */

    // On réalise la première itération à part
    for (j = 0; j < n; j++)
    {
        // On considère un élément

        // On remet le compteur à chaque itération
        compteur = 1;

        // On réinitialise la SequenceIndices
        sequence_indices.Msequence(deque<int>(1, X[j]));
        sequence_indices.Mindices(vector<int>(1,j));

        // On profite de la boucle pour enregistrer les valeurs possibles
        if (find(E.begin(), E.end(), X[j]) == E.end())
        {
            E.push_back(X[j]);
        }

        // On parcourt toute la série
        for (i = 0; i < n; i++)
        {
            if (X[j] == X[i] && i != j)
            {
                // On a trouvé une occurence
                compteur = compteur + 1;

                // On stocke l'indice correspondant
                sequence_indices.Aindice(i);
            }
        }

        // On a parcouru ce qui nous intéressait
        if (compteur >= 2)
        {
            // L'élément peut faire partie d'occurences intéressantes
            stockage.push_back(sequence_indices);


            if (find(c_max.begin(), c_max.end(), SequenceNombre(deque<int>(1, X[j]), compteur)) == c_max.end())
            {
                /* l'élément ne peut pas faire partie d'occurences intéressantes
                on l'enregistre malgré tout dans le contexte maximal */
                c_max.push_back(SequenceNombre(deque<int>(1, X[j]), compteur));
            }
        }
    }

    // Passage aux itérations suivantes

    // Variable qui renseigne la taille actuelle des séquences avec lesquelles
    // on travaille
    int taille_actuelle = 1;

    // Liste des indices à supprimer dans chaque séquence
    vector<int> indices_a_supprimer;

    // Variables intermédiaires
    deque<int> sequence_copie;
    int indice_taille_actuelle;
    vector<int> indices;
    SequenceIndices sequence_indices_copie;

    int taille_stockage = stockage.size();

    while (taille_stockage != 0)
    {
        // Actualisation de la taille des séquences étudiées
        taille_actuelle = taille_actuelle + 1;

        // Remise à 0
        i = 0;

        while (i < taille_stockage)
        {
            // On considère une séquence accompagnée d'indices intéressants
            sequence_indices = stockage[i];
            sequence_indices_copie = stockage[i];

            // Remise à "0"
            compteur = 1;

            // On copie la séquence pour éventuellement l'ajouter à c_max si
            // besoin
            sequence_copie = sequence_indices.Rsequence();

            // On réinitialise les indices à supprimer
            indices_a_supprimer.resize(0);

            // On se donne les indices
            indices = sequence_indices.Rindices();

            // Calcul qu'on ne veut pas faire deux fois
            indice_taille_actuelle = indices[0] - taille_actuelle;

            // On ajoute à la séquence l'élément immédiatement voisin
            if (indice_taille_actuelle >= -1)
            {
                sequence_indices.Aelement(X[indice_taille_actuelle + 1]);

                // On parcourt les indices stockés
                for (j = 1; j < int(indices.size()); j++)
                {
                    // On stocke cette valeur pour ne pas avoir à la calculer deux
                    // fois
                    indice_taille_actuelle = indices[j] - taille_actuelle;

                    if (indice_taille_actuelle >= -1)
                    {
                        //if (sequence_indices.Rsequence() == Extraction_parallel(X, indices[j], indice_taille_actuelle - 1, 2))
                        if (equal(&X[indice_taille_actuelle+1], &X[indices[j]+1], &sequence_indices.Rsequence()[0]))
                        {
                            //Afficher(sequence_indices.Rsequence());
                            // La séquence a été trouvée
                            compteur = compteur + 1;
                        }
                        else
                        {
                            /* La séquence à l'indice donné n'est pas la bonne, on
                            ne conserve pas l'indice dans le stockage */
                            indices_a_supprimer.push_back(indices[j]);

                        }
                    }
                    else
                    {
                        // L'indice n'est pas pertinent
                        indices_a_supprimer.push_back(indices[j]);
                    }
                }

                if (compteur == 1)
                {
                    // On la retire du stockage
                    stockage.erase(remove(stockage.begin(), stockage.end(), sequence_indices_copie), stockage.end());

                    /* On a supprimé un élément, il faut incrémenter en
                    arrière pour ne pas en oublier */
                    i = i - 1;
                }
                else
                {
                    // Pour les calculs suivants on conserve la séquence comme sous branche
                    if (find(c_max.begin(), c_max.end(), SequenceNombre(sequence_indices.Rsequence(), compteur)) == c_max.end())
                    {
                        c_max.push_back(SequenceNombre(sequence_indices.Rsequence(), compteur));
                    }

                    /* On peut repartir pour l'itération suivante, on supprime juste
                    les indices inutiles */
                    for (j = 0; j < int(indices_a_supprimer.size()); j++)
                    {
                        sequence_indices.Sindice(indices_a_supprimer[j]);
                    }

                    /* On remplace la séquence prise initialement par la séquence
                    retravaillée */
                    stockage[i] = sequence_indices;
                }
            }
            else
            {
                // On la retire du stockage
                stockage.erase(std::remove(stockage.begin(), stockage.end(), sequence_indices_copie), stockage.end());

                /* On a supprimé un élément, il faut incrémenter en
                arrière pour ne pas en oublier */
                i = i - 1;
            }

            // Incrémentation
            i++;

            // On actualise la valeur de la taille de stockage
            taille_stockage = stockage.size();
        }
    }

    //Afficher(c_max);

    /*
    PHASE 2
    */

    double delta;

	// Variables intermédiaires
    int N_w_u;
    int N_x_w_u;
    int N_x_w;
    vector<int> w_u;
    vector<int> w;
    vector<int> x_w_u;
    vector<int> x_w;
    SequenceNombre c_max_i;
    vector<int> c_max_i_sequence;
    deque<int> c_max_i_inter;

    // Ce qu'on va finalement renvoyer
    vector<SequenceNombre> context_loc;

    // Variable du critère de sélection
    double K = C*log(double(n));

    // On parcourt c_max mais à l'envers
    for (i = c_max.size() - 1; i >= 0; i--)
    {
        // On parcourt les SequenceNombre

        // On définit les séquences utiles
        c_max_i = c_max[i];
        c_max_i_inter = c_max_i.Rsequence();
        c_max_i_sequence.assign(c_max_i_inter.begin(), c_max_i_inter.end());

        w_u = c_max_i_sequence;

        // On sépare les cas où la séquence est unitaire ou non
        if (w_u.size() > 1)
        {
            //w = Extraction_parallel(w_u, 0, w_u.size() - 2, 3);
            w.assign(w_u.begin() + 1, w_u.end());

            // On stocke le nombre qu'on a pris soin de calculer avant
            N_w_u = c_max_i.Rnombre();

            // On passe au calcul de detla
            delta = 0.0;

            for (j = 0; j < int(E.size()); j++)
            {
                x_w_u.assign(w_u.begin(), w_u.end());
                x_w_u.push_back(E[j]);
                x_w.assign(w_u.begin(), w_u.end());
                x_w.push_back(E[j]);

                N_x_w_u = Count(X, x_w_u);
                N_x_w = Count(X, x_w);

                if (N_x_w_u != 0 && N_x_w != 0)
                {
                    delta = delta + N_x_w_u*log((double(N_x_w_u*Count(X, w)))/(double(N_w_u*N_x_w)));
                }
            }

            // On dispose alors de delta
            if ((delta >= K) && find(context_loc.begin(), context_loc.end(), c_max_i) == context_loc.end())
            {
                // Le critère est satisfait, on peut conserver la séquence
                context_loc.push_back(c_max_i);
            }
        }
        else
        {
            // On stocke le nombre qu'on a pris soin de calculer avant
            N_w_u = c_max_i.Rnombre();

            // On passe au calcul de detla
            delta = 0.0;

            for (j = 0; j < int(E.size()); j++)
            {
                x_w_u.assign(w_u.begin(), w_u.end());
                x_w_u.push_back(E[j]);

                N_x_w_u = Count(X, x_w_u);

                if (N_x_w_u != 0)
                {
                    delta = delta + N_x_w_u*log((double(N_x_w_u*n))/(double(N_w_u*Count(X, deque<int>(E[j])))));
                }
            }

            // On dispose alors de delta
            if ((delta >= K) && find(context_loc.begin(), context_loc.end(), c_max_i) == context_loc.end())
            {
                // Le critère est satisfait, on peut conserver la séquence
                context_loc.push_back(c_max_i);
            }
        }
    }

    /* Dans le cas où les valeurs les plus récentes soient dans le context
    on les supprime */
    i = 0;
    while(i < int(context_loc.size()))
    {
        c_max_i_inter = context_loc[i].Rsequence();

        taille_actuelle = c_max_i_inter.size();

        if (equal(&X[n-taille_actuelle], &X[n], &c_max_i_inter[0]))
        {
            /* La fin de la chaîne correspond à un élément du contexte, on
            ne le conserve pas dans le contexte */
            context_loc.erase(remove(context_loc.begin(), context_loc.end(), context_loc[i]), context_loc.end());

            i--;
        }

        i++;
    }


    // Enregistrement
    cutoff = C;

    if (int(context_loc.size()) == 0)
    {
        // L'algorithme n'a pas pu construire le contexte
        cout << "Unable to build context, try with another cutoff or sample." << endl;

        exit(EXIT_FAILURE);
    }

    context = context_loc;

    alphabet_size = int(E.size());

    alphabet = E;

    c_max_i_inter = context[0].Rsequence(); // <- erreur de segmentation

    order = c_max_i_inter.size();

    donnees = X;
}

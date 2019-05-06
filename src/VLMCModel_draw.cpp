#include "VLMC.hpp"
#include <fstream>

void VLMCModel::drawContextTree(string filename)
{
    /*
    Cette fonction édite un fichier de configuration pour le programme Graphviz
    puis trace l'arbre de contexte
    https://graphviz.org/

    L'image créée est filename.jpg
    */

    // Varialbe intermédiaire de stockage
    deque<int> sequence, context_j_sequence;

    // Variables de boucle
    int i, j;

    // Variables de numérotation
    int k = 1;
    int l = 1;

    // Variable intermédiare
    bool B = false;

    // Ouverture du fichier de configuration
    ofstream configfile;

    configfile.open("config_draw_tree.dot", ios::out);

    if (configfile.bad())
    {
        cout << "Unable to open config file for drawing context tree" << endl;

        exit(EXIT_FAILURE);
    }

    configfile << "graph G {" << endl;

    for (i = 0; i < int(context.size()); i++)
    {
        sequence = context[i].Rsequence();

        // On vérifie si cette séquence n'a pas déjà été tracée
        for (j = 0; j < i; j++)
        {
            context_j_sequence = context[j].Rsequence();

            if (equal(sequence.begin(), sequence.end(), context_j_sequence.end() - sequence.size(), context_j_sequence.end()))
            {
                // Déjà tracée
                B = true;

                // Pas la peine de poursuivre
                break;
            }
        }

        if (B == false)
        {
            configfile << "\".\" -- ";

            for (j = int(sequence.size()) - 1; j >= 0; j--)
            {
                if (j == 0)
                {
                    configfile << "a" << k;
                }
                else
                {
                    configfile << "a" << k << " -- ";
                }

                k++;
            }

            configfile << ";" << endl;

            for (j = int(sequence.size()) - 1; j >= 0; j--)
            {
                configfile << "a" << l << " [label = \"" << sequence[j] << "\"]" << endl;

                l++;
            }
        }

        B = false;
    }

    configfile << "}" << endl;

    // Fermeture du fichier
    configfile.close();

    // Execution de la commande de tracé
    string command = "dot -Tjpg -o " + filename + ".jpg config_draw_tree.dot";
    system(command.c_str());
}

#include "VLMC.hpp"
#include <fstream>

class Noeud
{
public:
    Noeud(vector<int> const& branche);

    string getNom();
    string getNomNoeudAuDessus();
    string getLabel();
private:
    string nom;
    string nom_noeud_au_dessus;
    string label;
};

Noeud::Noeud(vector<int> const& branche)
{
    /*
    Cette méthode reçoit une branche partant du premier noeud jusqu'au noeud
    dont il est question dans cet objet et génère le noeud correspondant
    */
    int j;

    label = to_string(branche[0]);

    if (branche.size() == 1)
    {
        // C'est un noeud de base
        nom_noeud_au_dessus = "\".\"";

        nom = "n_" + label + "_";
    }
    else
    {
        nom_noeud_au_dessus = "n_";
        nom = "n_";

        for (j = 0; j < int(branche.size()); j++)
        {
            if (j != 0)
            {
                nom_noeud_au_dessus = nom_noeud_au_dessus + to_string(branche[j]) + "_";
            }

            nom = nom + to_string(branche[j]) + "_";
        }
    }
}

string Noeud::getNom()
{
    return nom;
}

string Noeud::getNomNoeudAuDessus()
{
    return nom_noeud_au_dessus;
}

string Noeud::getLabel()
{
    return label;
}

void VLMCModel::drawContextTree(string filename)
{
    /*
    Cette fonction édite un fichier de configuration pour le programme Graphviz
    puis trace l'arbre de contexte
    https://graphviz.org/

    L'image créée est filename.jpg
    */

    // Varialbe intermédiaire de stockage
    deque<int> sequence;

    // Variables de boucle
    int i, j;

    // Variables de numérotation
    int k = 1;

    // Variable intermédiare
    bool B = false;
    string to_write;
    string line;

    // Structure purement informatique de l'arbre
    vector<Noeud> tree;
    vector<int> branche({1});

    // Ouverture du fichier de configuration
    ofstream configfile;
    ifstream config_file_read;

    for (j = 0; j <= order; j++)
    {
        for (i = 0; i < int(context.size()); i++)
        {
            sequence = context[i].Rsequence();

            if (int(sequence.size()) >= k)
            {
                if (j <= int(sequence.size()))
                {
                    branche = vector<int>(sequence.end()-j-1, sequence.end());
                }

                tree.push_back(Noeud(branche));
            }
            else
            {
                /* Au vu de l'ordre dans lequel nous parcourons les branches
                on sait que les prochaines branches seront trop petites pour être
                parcourues on peut donc stopper la boucle */
                break;
            }
        }

        // Pour ne plus gèrer les termes de taille trop petite
        k++;
    }

    configfile.open("config_draw_tree.dot", ios::out);

    if (configfile.bad())
    {
        cout << "Unable to open config file for drawing context tree" << endl;

        exit(EXIT_FAILURE);
    }

    configfile << "graph G {" << endl;

    Noeud noeud(vector<int>(1,1));

    for (i = 0; i < int(tree.size()); i++)
    {
        noeud = tree[i];

        B = false;

        config_file_read.open("config_draw_tree.dot", ios::in);

        to_write = noeud.getNomNoeudAuDessus() + " -- " + noeud.getNom() + ";";

        while (getline(config_file_read, line))
        {
            // La ligne qu'on s'apprête à écrire est déjà présente
            if (line == to_write)
            {
                B = true;
                break;
            }
        }

        config_file_read.close();

        if (B == false)
        {
            configfile << noeud.getNomNoeudAuDessus() << " -- " << noeud.getNom() << ";" << endl;

            configfile << noeud.getNom() << " [label = \"" << noeud.getLabel() << "\"]" << endl;
        }
    }

    configfile << "}" << endl;

    // Fermeture du fichier
    configfile.close();

    // Execution de la commande de tracé
    string command = "dot -Tjpg -o " + filename + ".jpg config_draw_tree.dot";
    system(command.c_str());
}

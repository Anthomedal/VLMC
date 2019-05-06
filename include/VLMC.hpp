/*
	=== Français ===
	Auteur : Anthony Gerber-Roth
	Date : Février 2019
	Contexte : Projet de TER, M1 Mathématiques et Applications
	But : Implémenter l'algorithme du contexte pour une Chaîne de Markov à Longueur Variable

	Référence bibTex :
		@article{10.2307/120101,
		ISSN = {00905364},
		URL = {http://www.jstor.org/stable/120101},
		abstract = {We study estimation in the class of stationary variable length Markov chains (VLMC) on a finite space. The processes in this class are still Markovian of high order, but with memory of variable length yielding a much bigger and structurally richer class of models than ordinary high-order Markov chains. From an algorithmic view, the VLMC model class has attracted interest in information theory and machine learning, but statistical properties have not yet been explored. Provided that good estimation is available, the additional structural richness of the model class enhances predictive power by finding a better trade-off between model bias and variance and allowing better structural description which can be of specific interest. The latter is exemplified with some DNA data. A version of the tree-structured context algorithm, proposed by Rissanen in an information theoretical set-up is shown to have new good asymptotic properties for estimation in the class of VLMCs. This remains true even when the underlying model increases in dimensionality. Furthermore, consistent estimation of minimal state spaces and mixing properties of fitted models are given. We also propose a new bootstrap scheme based on fitted VLMCs. We show its validity for quite general stationary categorical time series and for a broad range of statistical procedures.},
		author = {Peter Buhlmann and Abraham J. Wyner},
		journal = {The Annals of Statistics},
		number = {2},
		pages = {480--513},
		publisher = {Institute of Mathematical Statistics},
		title = {Variable Length Markov Chains},
		volume = {27},
		year = {1999}
		}

	=== English ===
	Author : Anthony Gerber-Roth
	Date : February 2018
	Context : Master project
	Goal : Implementation of context algorithm for Variable Length Markov Chain

	bibTex reference :
		@article{10.2307/120101,
		ISSN = {00905364},
		URL = {http://www.jstor.org/stable/120101},
		abstract = {We study estimation in the class of stationary variable length Markov chains (VLMC) on a finite space. The processes in this class are still Markovian of high order, but with memory of variable length yielding a much bigger and structurally richer class of models than ordinary high-order Markov chains. From an algorithmic view, the VLMC model class has attracted interest in information theory and machine learning, but statistical properties have not yet been explored. Provided that good estimation is available, the additional structural richness of the model class enhances predictive power by finding a better trade-off between model bias and variance and allowing better structural description which can be of specific interest. The latter is exemplified with some DNA data. A version of the tree-structured context algorithm, proposed by Rissanen in an information theoretical set-up is shown to have new good asymptotic properties for estimation in the class of VLMCs. This remains true even when the underlying model increases in dimensionality. Furthermore, consistent estimation of minimal state spaces and mixing properties of fitted models are given. We also propose a new bootstrap scheme based on fitted VLMCs. We show its validity for quite general stationary categorical time series and for a broad range of statistical procedures.},
		author = {Peter Buhlmann and Abraham J. Wyner},
		journal = {The Annals of Statistics},
		number = {2},
		pages = {480--513},
		publisher = {Institute of Mathematical Statistics},
		title = {Variable Length Markov Chains},
		volume = {27},
		year = {1999}
		}
*/

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

#include <vector>
#include <iostream>
#include "conteneurs.hpp"
#include "Probability.hpp"
#include <cmath>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

class VLMCModel
{
/*
Cette classe permet de construire un modèle de VLMC à partir de données existantes
elle met en oeuvre l'algorithme du contexte et des méthodes d'apprentissages
pour déterminer la VLMC la plus proche des données envoyées en argument
*/
public:
    /* Possibilité de déclarer le modèle avec ou sans
    données initiales */
    VLMCModel(vector<int> const& X, double const& C);
    VLMCModel();

    // Calcul des probabilités de transition
    double TransitionProbability(int x, vector<int> const& y);

    // Simulation de la VLMC
    vector<int> Simulate(int length);

    // Méthodes de renvoie des attributs
    vector<SequenceNombre> const& getContext() const;
    double const& getCutoff() const;
    int const& getOrder() const;

    // Méthode de modification du cutoff
    void setCutoff(double const& c);

    // Affichage du context
    void printContext();

    // Fonction permettant de tracer l'arbre contexte
    void drawContextTree(string filename);
private:
    // ARGUMENTS
    // Le cutoff utilisé pour gèrer les algorithmes
    double cutoff;

    // Le context estimé
    vector<SequenceNombre> context;

    // Ordre de la VLMC
    int order;

    // Taille de l'alphabet utilisé
    int alphabet_size;

    // Alphabet des valeurs possibles
    vector<int> alphabet;

    // On conserve les données initiales dans l'objet
    vector<int> donnees;

    // METHODES
    // Simulation de la VLMC
    int SimulateValue(vector<int> const& recent_past);
};

class VLMC
{
/*
Cette classe correspond à une VLMC théorique dont le contexte est explicitement
défini par l'utilisateur. Sa principale utilité est de simuler des valeurs suivant
la loi d'une VLMC
*/
public:
    /* Possibilité de déclarer le modèle avec ou sans
    données initiales */
    VLMC(vector<vector<int>> const& context_init, vector<int> const& alphabet_init);
    VLMC(VLMCModel const& V); // Non définie

    // Réglage des valeurs des probabilités de transition
    void setProbabilities(vector<int> const& context_element, int point, double probability_value);
    void setProbabilities(int point, double probability_value);

    // Calcul des probabilités de transition
    double TransitionProbability(int x, vector<int> const& y);

    // Simulation de la VLMC
    vector<int> Simulate(int length);

    // Méthodes de renvoie des attributs
    vector<vector<int>> const& getContext() const;
    int const& getOrder() const;

    // Affichage du context
    void printContext();

    // Fonction permettant de tracer l'arbre contexte
    void drawContextTree(string filename);
private:
    // ARGUMENTS
    // Le context estimé
    vector<vector<int>> context;

    // Ordre de la VLMC
    int order;

    // Taille de l'alphabet utilisé
    int alphabet_size;

    // Alphabet des valeurs possibles
    vector<int> alphabet;

    // Distribution de probabilités
    vector<Probability> P;

    // METHODES
    // Simulation de la VLMC
    int SimulateValue(vector<int> const& recent_past);

    /* Les fonctions calculant les probabilités de transition définie comme règles
    de la classe */
    double p(int x, vector<int> y);
    double p(int x);
};


// Utiliaires
void Afficher(vector<int> const& w);

void Afficher(deque<int> const& w);

void Afficher(vector<vector<int>> const& w);

void Afficher(vector<SequenceNombre> const& w);

int Count(vector<int> const& X, deque<int> const& w);

int Count(vector<int> const& X, vector<int> const& w);

double Uniform();

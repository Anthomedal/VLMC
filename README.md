# VLMC
This project is an implementation of the context algorithm for Variable Length Markov Chains (VLMC).
This method has been introduced in the following publication: 

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
		
(bibTeX)

# Warning 
This library has been developed to work on Debian with the GCC compiler. 
It is up to you to adapt the compilation commands to run it on another operating system or compiler.

# Installation 
- Download
- Make sure Graphviz is installed 
- Run compilation : make compile 
- Make sure everything works : make test 

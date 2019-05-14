# VLMC
This project is an implementation of the context algorithm for Variable Length Markov Chains (VLMC).
This method has been introduced in the following publication: 

Peter Buhlmann and Abraham J. Wyner. Variable length markov chains. The Annals of Statistics ,
27(2) :480-513, 1999.

# Warning 
This library has been developed to work on Debian with the GCC compiler. 
It is up to you to adapt the compilation commands to run it on another operating system or compiler.

# Installation 
- Download
- Make sure Graphviz is installed (https://graphviz.org/)
- Run compilation : make compile 
- Make sure everything works : make test 

# Parallel computing
You can use the VLMC library in parallel computing in order to gain in execution speed on certain computing steps. To compile the library in parallel computing mode :
- Make sure openmp is installed (https://www.openmp.org/)
- make compile_parallel
- Test : make test_parallel

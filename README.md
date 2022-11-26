# GraphRanker
**GraphRanker** is a C project realized for the *Algorithms and Principles of Computer Science* (*Algoritmi e Principi dell'Informatica*) course at Politecnico di Milano. The focus is on the algorithm's runtime and space optimization.
## Problem Description
The goal is to generate a rank of weighted directed graphs. More precisely, the rank has to keep track of the *k* "best" graphs.\
## Input
The program reads from the standard input (see following sections for more details):
- two parameters, only once (on the first row of the file)
  - *d* -> number of nodes of every graph
  - *k* -> lenght of the rank
- a sequence of commands among:
  - **AggiungiGrafo** (meaning *AddGraph*) followed by adjacency matrix
  - **TopK**
### AggiungiGrafo 
- This command indicates that a new graph has to be added to the ones that have to be considered to generate the ranking. It's followed by the adjacency matrix of the graph itself. 
- The nodes of the graph are labelled with an integer index between *0* and *d-1*.
- The weights of the graph have values in the interval *[0, 2<sup>32</sup> - 1]*

### TopK
- Every graph from the beginning of the program to the **TopK** command has to be considered. Every graph has to be labelled with an integer index corresponding to the number of graphs that have been read before it. 
- **TopK** requires that the *k* indeces are printed of the graphs with the lower values according to the following metric:\
  *Sum of the shortest paths between node 0 and every other node of the graph*
- If there are graphs with the same metric value, their priority is assigned according to the reading order (meaning that, the ones who were read first have higher priority).
- The k indeces have to printed in a single line in any order. 

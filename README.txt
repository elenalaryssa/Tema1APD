Culea Elena-Laryssa 335CC

Serial:
Am folosit doua matrici,una pt a verifica vecinii si
una in care fac modificari(matrix[][], temp_matrix[][]).
Pentru fiecare element contorizez intr-o variabila nr de vecini "ALIVE".
In functie de numarul de vecini "ALIVE" aplic regulile stabilite de Conway in Game of Life si fac modificari in matricea temp_matrix.
Dupa ce termin verficarea si modificarea tuturor elementelor din matrice
bordez matricea temp_matrix si copiez temp_matrix[][] in matrix[].

Paralel:
Am folosit pragma omp parrallel private(i,j) shared(neigh, matrix, temp_matrix) imediat dupa for-ul pentru iteratii.
Am paralelizat:
-copierea matricilor cu ajutorul clauzei collapse(2)
-pentru verificare&modificare am folosit  pragma omp for private(j) reduction(+:neigh)
-pentru bordare am folosit pragma omp for



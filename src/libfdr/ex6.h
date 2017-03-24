
/*
  matrix.txt
    3
    0 1 0
    1 0 1
    0 0 1

  list.txt, undirected graph
    5 6
    1 2 3 4 5
    1 2 
    2 5
    2 3
    3 4
    4 5
    1 5
*/

#include "jrb.h"

JRB LoadMatrix(const char* fname);

JRB LoadList(const char* fname);
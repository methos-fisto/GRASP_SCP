#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <float.h>

#include "Grasp.h"
#include "Solution.h"
#include "time.h"
//#include "rnd.c"

class Solution;

Solution* construct(int**& mat_contrainte, int*& tab_couts, const double& alpha, int& nbC, int& nbN, const int&);

#endif

#include "improve.h"

int min_z(const int nbVars, const int *sol, const int *costs) {
	int z = 0;
	
	for (int i = 0; i < nbVars; i++) {
		if (sol[i] == 1) {
			z += costs[i];
		}
	}
	
	return z;
}

void 10exchange(int *sol, int i)
{
	sol[i] = 0;
}

void 11exchange(int *sol, int i, int j)
{
	sol[i] = 0;
	sol[j] = 1;
}

/**
 *	Improve locally our WSCP solution by working on neighbours of sel, with a
 *	1-0 exchange algorithm.
 *
 *	@param int   number of constraints
 *	@param int   number of variables
 *	@param int*  Costs array
 *	@param int** Constraints matrix
 *	@param int*  solution to work on
 *	@param int   objective value with current solution
 */
int* improve_10(
	  const int nbCnst, const int nbVars
	, const int *costs, const int **cnst
	, int *sol, const int z
) {
	int i = 0, z = INT_MAX;
	int *res = new int[nbVars];
	
	// 1-0 exchange
	for (i = 0; i < nbVars; i++) {
		if (sol[i] == 1) {
			sol[i] = 0;
			
			if (admissible(nbVars, nbCnst, cnst, sol)) {
				for (j = 0; j < nbVars; j++) {
					res[j] = sol[j];
				}
			}
		
			sol[i] = 1;
		}
	}
	
	return res;
}

/**
 *	Now with a 1-1 exchange,
 *	
 *	@params cf. above
 */
int* improve_10(
	  const int nbCnst, const int nbVars
	, const int *costs, const int **cnst
	, int *sol, const int z
) {
	int i = 0;
	int *res = new int[nbVars];
	
	// 1-0 exchange
	for (i = 0; i < nbVars; i++) {
		sol[i] = 0;
		
		if (min_z(nbVars, sol, costs) < z) {
			for (j = 0; j < nbVars; j++) {
				res[j] = sol[j];
			}
		}
		
		sol[i] = 1;
	}
	
	return res;
}

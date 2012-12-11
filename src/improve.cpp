#include "improve.h"

/**
 *	Calculates the value of the objective function for a given solution.
 *
 *	@param int  number of variables
 *	@param int* costs array
 *	@param int* selected solution
 */
int min_z(int nbVars, int *&costs, int *&sol) {
	int z = 0;
	
	for (int i = 0; i < nbVars; i++) {
		if (sol[i] == 1) {
			z += costs[i];
		}
	}
	
	return z;
}

/**
 *	Determines a solution's admissibility by verifying each constraints is
 *	respected.
 *
 *	@param int   number of constants
 *	@param int   number of variables
 *	@param int** constraint matrix
 *	@param int*  solution
 */
bool admissible(int nbVars, int nbCnst, int **&cnst, int *&sol)
{
	int i = 0, j = 0;
	int respect = 0;
	bool admissible = true;
	
	for (i = 0; i < nbCnst; i++) {
		respect = 0;
		
		for (j = 0; j < nbVars; j++) {
			respect += cnst[i][j] * sol[j];
		}
		
		if (respect == 0) {
			admissible = false;
		}
	}
	
	return admissible;
}

/**
 *	Interest function U(x), divides the number of appearance of a var in the
 *	constraints matrix by its cost.
 *
 *	@param int   id of the variable
 *	@param int   costs of the variable
 *	@param int   nb of constraints
 *	@param int** constraints matrix
 */
double interest(int id, int cost, int nbCnst, int **&cnst)
{
	int nb = 0, i = 0;
	
	for (i = 0; i < nbCnst; i++) {
		nb += cnst[i][id];
	}
	
	return (double) nb / cost;	
}

/**
 *	Copies a solution in a holder.
 *
 *	@param int  number of vars
 *	@param int* current solution
 *	@param int* solution to modify
 */
void copy(int nbVars, int *sol, int *res)
{
	for (int i = 0; i < nbVars; i++) {
		res[i] = sol[i];
	}
}

/**
 *	Improve locally our WSCP solution by working on neighbours of sol, with a
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
	  int nbCnst, int nbVars
	, int *&costs, int **&cnst
	, int *sol, int first
) {
	int i = 0, z = 0, current = first;
	int *res = new int[nbVars];
	
	copy(nbVars, sol, res);
	
	// 1-0 exchange
	for (i = 0; i < nbVars; i++) {
		if (sol[i] == 1) {
			sol[i] = 0;
			
			z = min_z(nbVars, costs, sol);
			
			if (admissible(nbVars, nbCnst, cnst, sol)
				&& z < current
			) {
				copy(nbVars, sol, res);
				current = z;
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
int* improve_11(
	  int nbCnst, int nbVars
	, int *costs, int **cnst
	, int *sol, int first
) {
	int i = 0, j = 0, z = 0, current = first;
	int *res = new int[nbVars];
	
	copy(nbVars, sol, res);
	
	// 1-1 exchange
	for (i = 0; i < nbVars; i++) {
		if (sol[i] == 1) {
			sol[i] = 0;
			
			for (j = 0; j < nbVars; j++) {
				if (sol[j] == 0) {
					sol[j] = 1;
					
					z = min_z(nbVars, costs, sol);
			
					if (admissible(nbVars, nbCnst, cnst, sol)
						&& z < current
					) {
						copy(nbVars, sol, res);
						current = z;
					}
					
					sol[j] = 0;
				}
			}
			
			sol[i] = 1;
		}
	}
	
	return res;
}

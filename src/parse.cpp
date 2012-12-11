#include "parse.h"

/**
 *	Parse a formatted file for the WSCP problem.
 *
 *	@param ifstream* file to parse
 *	@param int       number of constants
 *	@param int       number of variables
 *	@param int*      costs of the variables
 *	@param int**     constraint matrix
 */
void parse(std::ifstream *&f, int &nbCnst, int &nbVars, int *&costs,  int **&cnst)
{
	int i = 0, j = 0, a = 0, n = 0;
	
	*f >> nbCnst;
	*f >> nbVars;
	
	// Costs array
	costs = new int[nbVars];
	// Constraints matrix
	cnst  = new int*[nbCnst];
	
	for (i = 0; i < nbCnst; i++) {
		cnst[i] = new int[nbVars];
	}
	
	// Fill costs
	for (j = 0; j < nbVars; j++) {
		*f >> costs[j];
	}
	
	// Fill matrix
	for (i = 0; i < nbCnst; i++) {
		// Number of non zeros
		*f >> n;
		// First non zero
		*f >> a;
		
		for (j = 0; j < nbVars; j++) {
			if (j == a - 1) {
				// Non-zero
				cnst[i][j] = 1;
				
				if (--n > 0) {
					// Next non-zero
					*f >> a;
				}
			} else {
				cnst[i][j] = 0;
			}
		}
	}
}

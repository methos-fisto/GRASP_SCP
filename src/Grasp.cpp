#include "Grasp.h"

Grasp::Grasp(double alpha, int n, int nbVars, int nbCnst, int *costs, int **cnst)
{
	_n = n;
	_a = alpha;
	
	_nbVars = nbVars;
	_nbCnst = nbCnst;
	
	_costs  = costs;
	_cnst   = cnst;
	
	_rcl    = new RCL();
	
	_type   = T_MAX;
	_strat  = S_10;
}

void Grasp::solve()
{
	// s0  is our optimum
	// sol is our current solution
	Solution *sol = new Solution(_nbVars), *s0 = new Solution(_nbVars);
		
	do {
		// Construction
		sol = construct(_cnst, _costs, _a, _nbCnst, _nbVars);
		
		if (sol->val() > s0->val()) {
			delete s0;
			s0 = sol;
		}
		
		// Improvement
		switch (_strat) {
			case S_10 :
				sol = exchange_10(s0);
				break;
			
			case S_11 :
				sol = exchange_10(s0);
				break;
			
			case S_10_11 :
				sol = exchange_10(s0);
				break;
			
			case S_11_10 :
				sol = exchange_10(s0);
				break;
				
			default :
				throw "Unknown type in Grasp::solve().\n";
		}
	
		if (sol->val() > s0->val()) {
			delete s0;
			s0 = sol;
		}
	} while (--_n >= 0);
	
}

Solution* Grasp::exchange_10(Solution *sol)
{
	int i = 0, z = sol->val();
	Solution *res = sol;
	
	// 1-0 exchange
	for (i = 0; i < sol->size(); i++) {
		if (sol->at(i) == 1) {
			sol->set(i, 0, _costs[i]);
			
			if (sol->admissible(_nbVars, _nbCnst, _cnst)
				&& z < sol->val()
			) {
				res = sol;
			}
		
			sol->set(i, 1, _costs[i]);
		}
	}
	
	return res;
}

Solution* Grasp::exchange_11(Solution *sol)
{
	int i = 0, j = 0, z = sol->val();
	Solution *res = sol;
	
	// 1-0 exchange
	for (i = 0; i < sol->size(); i++) {
		if (sol->at(i) == 1) {
			// Start 10
			sol->set(i, 0, _costs[i]);
			
			for (j = 0; j < sol->size(); j++) {
				if (sol->at(j) == 0) {
					sol->set(j, 1, _costs[j]);
					
					if (sol->admissible(_nbVars, _nbCnst, _cnst)
						&& z < sol->val()
					) {
						res = sol;
					}
					
					sol->set(j, 0, _costs[j]);
				}
			}
			
			// Revert 10
			sol->set(i, 1, _costs[i]);
		}
	}
	
	return res;
}

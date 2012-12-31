#include "Grasp.h"

Grasp::Grasp(double alpha, int n, int nbVars, int nbCnst, int *costs, int **cnst)
{
	_n = n;
	_a = alpha;
	
	_nbVars = nbVars;
	_nbCnst = nbCnst;
	
	_costs  = costs;
	_cnst   = cnst;
	
	_type   = T_MAX;
	_strat  = S_10;
}

void Grasp::solve()
{
	int id = 0;
	// s0  is our optimum
	// sol is our current solution
	Solution      *sol  = new Solution(_nbVars), s0;
	std::ofstream *init = new std::ofstream(), *local = new std::ofstream();
	
	// Clear files because we append afterward
	init->open("res/initial.dat");
	init->close();
	local->open("res/local.dat");
	local->close();
	
	// First solution
	sol = construct(_cnst, _costs, _a, _nbCnst, _nbVars);
	
	do {
		++id;
		
		// Construction
		sol = construct(_cnst, _costs, _a, _nbCnst, _nbVars);
		
		// Plot different initial solutions
		init->open("res/initial.dat", std::ios_base::app);
		*init << id << '\t' << sol->val() << '\n';
		init->close();
		
		// Improvement
		switch (_strat) {
			case S_10 :
				sol = exchange_10(sol);
				break;
			
			case S_11 :
				sol = exchange_11(sol);
				break;
			
			case S_10_11 :
				sol = exchange_10(sol);
				sol = exchange_11(sol);
				break;
			
			case S_11_10 :
				sol = exchange_11(sol);
				sol = exchange_10(sol);
				break;
				
			default :
				throw "Unknown type in Grasp::solve().\n";
		}
		
		// Value after local optimization
		local->open("res/local.dat", std::ios_base::app);
		*local << id << '\t' << sol->val() << '\n';
		local->close();
	
		if (s0.val() == 0 || sol->val() < s0.val()) {
			s0 = *sol;
		}
		
		delete sol;
	} while (--_n > 0);
	
	std::cout << s0;
}

Solution* Grasp::exchange_10(Solution *&sol)
{
	Solution *res = new Solution(sol->size());
	
	// 1-0 exchange
	for (int i = 0; i < sol->size(); i++) {
		if (sol->at(i) == 1) {
			sol->set(i, 0, _costs[i]);
			
			if (sol->admissible(_nbVars, _nbCnst, _cnst)
				&& (res->val() == 0 || sol->val() < res->val())
			) {
				// We need to copy only the content
				*res = *sol;
			}
		
			sol->set(i, 1, _costs[i]);
		}
	}
	
	// No solution found
	if (res->val() == 0) {
		return sol;
	} else {
		return res;
	}
}

Solution* Grasp::exchange_11(Solution *&sol)
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
						z   = sol->val();
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

#include "Grasp.h"

Grasp::Grasp(double alpha, int n, int type, int nbVars, int nbCnst, int *costs, int **cnst)
{
	_n = n;
	_a = alpha;
	
	_nbVars = nbVars;
	_nbCnst = nbCnst;
	
	_costs  = costs;
	_cnst   = cnst;
	
	_type   = type;
	_strat  = S_10;
	
	_alphas = new double[_STEP];
	_probas = new double[_STEP];
	
	for (int i = 1; i < _STEP; i++) {
		_alphas[i] = (1.0 / _STEP) * i;
		_probas[i] = 1.0 / (_STEP - 1);
	}
	
	_total = _STEP - 1;
}

double Grasp::alpha() const
{
	return _a;
}

/****************************************
******** Reactive GRASP methods *********
****************************************/

void Grasp::setAlpha(double alpha, double proba)
{
	// Dual index
	int id = alpha * _STEP, i = 0;
	
	if (id > 0) {
		_total      = 0.0;
		_probas[id] = proba;
	
		for (i = 1; i < _STEP; i++) {
			_total += _probas[i];
		}
		
		_total *= _STEP;
	}
	
	// std::cout << "Renew alpha = " << alpha << " (id = " << id << ") with proba = " << proba << '\n';
	
	_selectAlpha();
}

void Grasp::_selectAlpha()
{
	double limit = rand() / (RAND_MAX / _total + 1), r = 0.0;
	int    i     = 1;
	
	while (r < limit && i < _STEP) {
		_a = _alphas[i];
		r += _probas[i] * _STEP;
		++i;
		
		// std::cout << "\tTmp alpha = " << _a << " - r = " << r << '\n';
	}
	
	// std::cout << "New alpha = " << _a << " (" << limit << " - " << _total << ")\n";
}

/****************************************
*************** Resolution **************
****************************************/

double Grasp::solve(int r)
{
	int id = 0, min = INT_MAX, max = 0, sum = 0, n = _n;
	// s0  is our optimum
	// sol is our current solution
	Solution      *sol  = new Solution(_nbVars), s0;
	std::ofstream *init = new std::ofstream(), *local = new std::ofstream()
	           , *final = new std::ofstream();
	
	if (r == 0) {
		// Clear files because we append afterward
		init->open("res/initial.dat");
		init->close();
		local->open("res/local.dat");
		local->close();
		final->open("res/final.dat");
		final->close();
	}
	
	do {
		++id;
		
		// Construction
		sol = construct(_cnst, _costs, _a, _nbCnst, _nbVars, _type);
		
		// Plot different initial solutions
		if (r == 0) {
			init->open("res/initial.dat", std::ios_base::app);
			*init << id << '\t' << sol->val() << '\n';
			init->close();
		}
		
		// Improvement
		switch (_strat) {
			case S_10 :
				sol = _exchange_10(sol);
				break;
			
			case S_11 :
				sol = _exchange_11(sol);
				break;
			
			case S_10_11 :
				sol = _exchange_10(sol);
				sol = _exchange_11(sol);
				break;
			
			case S_11_10 :
				sol = _exchange_11(sol);
				sol = _exchange_10(sol);
				break;
				
			default :
				throw "Unknown type in Grasp::solve().\n";
		}
		
		// Value after local optimization
		if (r == 0) {
			local->open("res/local.dat", std::ios_base::app);
			*local << id << '\t' << sol->val() << '\n';
			local->close();
		}
		
		if (sol->val() < min) {
			min = sol->val();
			
			s0 = *sol;
		}
		
		if (sol->val() > max) {
			max = sol->val();
		}
		
		sum += sol->val();
		
		delete sol;
	} while (--n > 0);
	
	final->open("res/final.dat", std::ios_base::app);
	*final << r << '\t' << min << '\n';
	final->close();
	
	std::cout << "Solution avec un alpha = " << _a << '\n';
	std::cout << s0 << '\n';
	
	// std::cout << "\t(" << (double) (sum / _n) << " - " << max << ") / (" << min << " - " << max << ")\n";
	
	return (double) ((sum / _n) - max) / (min - max);
}

Solution* Grasp::_exchange_10(Solution *&sol)
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

Solution* Grasp::_exchange_11(Solution *&sol)
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

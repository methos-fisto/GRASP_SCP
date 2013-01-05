#ifndef GRASP_H
#define GRASP_H

#include <vector>
#include <fstream>
#include <climits>

#include "Solution.h"
#include "construct.h"

class Solution;

class Grasp
{
	private :
		int    _n, _nbVars, _nbCnst, _type, _strat;
		int   *_costs;
		int  **_cnst;
		double _a;
		
		// Reactive GRASP data
		double _total, *_alphas, *_probas;
		
		Solution* _exchange_10(Solution*&);
		Solution* _exchange_11(Solution*&);
		
		void _selectAlpha();
		
		static const int _STEP = 20;
		
	public :
		// Types for the restricted candidates list
		static const int T_MAX = 0, T_MIN = 1;
		// Reactive or manual GRASP
		static const int G_MANUAL = 0, G_REACTIVE = 1;
		// Strategy for improving current solution
		static const int S_10 = 0, S_11 = 1, S_10_11 = 2, S_11_10 = 3;
	
		Grasp(double, int, int, int, int, int*, int**);
		
		double alpha() const;
		
		void setAlpha(double, double);
		
		double solve(int);
};

#endif

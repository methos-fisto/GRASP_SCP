#ifndef GRASP_H
#define GRASP_H

#include <map>
#include <fstream>

#include "Solution.h"
#include "RCL.h"
#include "construct.h"

class Solution;
class RCL;

class Grasp
{
	private :
		int    _n, _nbVars, _nbCnst, _type, _strat;
		int   *_costs;
		int  **_cnst;
		double _a;
		RCL   *_rcl;
		
	public :
		// Types for the restricted candidates list
		static const int T_MAX = 0, T_MIN = 1;
		// Strategy for improving current solution
		static const int S_10  = 0, S_11  = 1, S_10_11 = 2, S_11_10 = 3;
	
		Grasp(double, int, int, int, int*, int**);
		
		void solve();
		
		Solution* exchange_10(Solution*);
		Solution* exchange_11(Solution*);
		
		double _interest(const int);
};

#endif

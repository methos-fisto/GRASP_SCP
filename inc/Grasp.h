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
		// In order :
		//	- number of iterations
		//	- number of variable
		//	- number of constraint
		//	- type of alpha, cf. T_*
		//	- strategy for neighbourhood exploration, cf. S_*
		int    _n, _nbVars, _nbCnst, _type, _strat;
		// Costs of the variables in the objective function
		int   *_costs;
		// Constraints' matrix
		int  **_cnst;
		// Current alpha
		double _a;
		
		// Reactive GRASP data
		double _total, *_alphas, *_probas;
		
		/**
		 *	1-0 exchange for neighbourhood improvement. Change a set variable
		 *	into a free one and checks admissibility, solution improvement is
		 *	guaranteed by the problem's model.
		 *	Complexity : O(n)
		 *	
		 *	@param Solution* solution to work on
		 */
		Solution* _exchange_10(Solution*&);
		/**
		 *	1-1 exchange for neighbourhood improvement. Change a set variable
		 *	into a free one then check all combinations of changing a free one
		 *	into a set one ; update if solution is admissible and better.
		 *	Complexity : O(n^2)
		 *	
		 *	@param Solution* solution to work on
		 */
		Solution* _exchange_11(Solution*&);
		
		/**
		 *	Select a new alpha among the list. Generate a random value in range
		 *	[1, SUM(Pk)].
		 */
		void _selectAlpha();
		
		// alpha step = 1 / _STEP 
		static const int _STEP = 20;
		
	public :
		// Types for the restricted candidates list :
		//	- threshold = alpha * max
		//	- threshold = min + alpha * (max - min)
		static const int T_MAX = 0, T_MIN = 1;
		// Reactive or manual GRASP
		static const int G_MANUAL = 0, G_REACTIVE = 1;
		// Strategy for improving current solution
		//	- 1-0 exchange
		//	- 1-1 exchange
		//	- 1-0 followed by a 1-1
		//	- 1-1 followed by a 1-0
		static const int S_10 = 0, S_11 = 1, S_10_11 = 2, S_11_10 = 3;
		
		/**
		 *	Constructor.
		 *
		 *	@param double alpha for the first run (or kept if manual)
		 *	@param int    number of iterations
		 *	@param int    alpha type
		 *	@param int    number of variables
		 *	@param int    number of constraints
		 *	@param int*   variables' coefs
		 *	@param int**  constraints' matrix
		 */
		Grasp(double, int, int, int, int, int*, int**);
		
		/**
		 *	Getter for _a.
		 *
		 *	@return double
		 */
		double alpha() const;
		
		/**
		 *	Set a new alpha based on the last result we had.
		 *
		 *	@param double last alpha
		 *	@param double results quality
		 */
		void setAlpha(double, double);
		
		/**
		 *	Solves an instance using the GRASP method of constructing multiple
		 *	solutions at random using a Restricted Candidate List (RCL). The RCL
		 *	is created using the utility of each variable (determined by the
		 *	type of threshold T_* selected). Then the solution is greedily
		 *	created by picking a variable at random and adding it to the
		 *	solution ; the RCL is re-built at each step.
		 *
		 *	@param int number of the current run
		 *
		 *	@return double the quality of the alpha
		 */
		double solve(int);
};

#endif

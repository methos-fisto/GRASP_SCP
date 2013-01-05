#ifndef SOLUTION_H
#define SOLUTION_H

#include <cstddef>
#include <iostream>

class Solution
{
	private :
		//	- Number of set vars in the solution
		//	- Variables' coefs
		int _size, _val;
		//	- Set variables.
		int *_sol;
	
	public :
		/** 
		 *	Constructor, initialize an empty solution.
		 *
		 *	@param int size of the solution
		 */
		Solution(int);
		
		// - Getters
		/**
		 *	Size.
		 *
		 *	@return int
		 */
		int size() const;
		/**
		 *	Value of the solution.
		 *
		 *	@return int
		 */
		int val()  const;
		/**
		 *	Set variables.
		 *
		 *	@return int
		 */
		const int* sol() const;
		
		// - Accessors
		/**
		 *	Value of a given variable in the solution.
		 *
		 *	@param int id of the variable
		 *
		 *	@return int value [0,1]
		 */
		int at(const int) const;
		
		/**
		 *	Value of a given variable in the solution, operator definition.
		 *
		 *	@param int id of the variable
		 *
		 *	@return int value [0,1]
		 */
		int operator [] (const int) const;
		
		/**
		 *	Solution admissibility.
		 *
		 *	@param number of variables
		 *	@param number of constraints
		 *	@param constraints' matrix
		 */
		bool admissible(int, int, int**);
		/**
		 *	Set or free a variable, updating the solution's value.
		 *
		 *	@param int id of the variable
		 *	@param int value to set (0 = free, 1 = set)
		 *	@param int coef of the variable
		 */
		void set(const int, const int, int);
};

std::ostream& operator << (std::ostream&, const Solution&);

#endif

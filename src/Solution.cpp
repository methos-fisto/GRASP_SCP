#include "Solution.h"

Solution::Solution(int nbVars, int *sol, int *costs)
{
	int i = 0;

	_size = nbVars;
	
	// Solution value
	_val   = 0;
	_sol   = new int[nbVars];
	
	for (i = 0; i < nbVars; i++) {
		_sol[i]   = sol[i];
		
		if (sol[i] == 1) {
			_val += costs[i];
		}
	}
}

Solution::Solution(int nbVars)
{
	_size = nbVars;
	
	// Solution value
	_val   = 0;
	_sol   = new int[nbVars];
	
	for (int i = 0; i < nbVars; i++) {
		_sol[i] = 0;
	}
}

Solution::Solution()
{
	_val  = 0;
	_size = 0;
	_sol  = NULL;
}

int Solution::val() const
{
	return _val;
}

int Solution::at(const int i) const
{
	return _sol[i];
}

int Solution::size() const
{
	return _size;
}

const int* Solution::sol() const
{
	return _sol;
}

int Solution::operator [] (const int i) const
{
	return _sol[i];
}

bool Solution::admissible(int nbVars, int nbCnst, int **cnst)
{
	int  i = 0, j = 0, respect = 0;
	bool admis = true;
	
	for (i = 0; i < nbCnst; i++) {
		respect = 0;
		
		for (j = 0; j < nbVars; j++) {
			if (_sol[j] == 1) {
				respect += cnst[i][j];
			}
		}
		
		if (respect == 0) {
			admis = false;
		}
	}
	
	return admis;
}

void Solution::set(const int i, const int val, int cost)
{
	_sol[i] = val;
	
	if (val == 0) {
		_val -= cost;
	} else {
		_val += cost;
	}
}

std::ostream& operator << (std::ostream &os, const Solution &s)
{
	os << "Solution : ";
	
	for (int i = 0; i < s.size(); i++) {
		if (s[i]) {
			os << 'x' << i + 1 << ", ";
		}
	}
	
	os << "valeur : " << s.val();
	
	return os << '\n';
}

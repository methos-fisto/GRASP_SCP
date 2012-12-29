#ifndef SOLUTION_H
#define SOLUTION_H

#include <cstddef>
#include <iostream>

class Solution
{
	private :
		int _size, _val;
		int *_sol;
	
	public :
		Solution(int, int*, int*);
		Solution(int);
		Solution();
		
		int size() const;
		int val()  const;
		const int* sol() const;
		
		int at(const int) const;
		
		int operator [] (const int) const;
		
		bool admissible(int, int, int**);
		void set(const int i, const int val, int);
};

std::ostream& operator << (std::ostream&, const Solution&);

#endif

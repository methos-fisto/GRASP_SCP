#ifndef RCL_H
#define RCL_H

#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

class RCL {
	private :
		std::vector<std::pair<int, double> > _list;
	
	public :
		int operator [] (const int) const;
		int at(const int) const;
		int size() const;
		
		int head() const;
		int tail() const;
		int get()  const;
		
		void clear();
		void add(const int, const double);
		
		// std::vector<std::pair<int, double> >::iterator begin();
		// std::vector<std::pair<int, double> >::iterator end();
};

std::ostream& operator << (std::ostream&, const RCL&);

#endif

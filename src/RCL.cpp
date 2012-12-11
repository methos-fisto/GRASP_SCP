#include "RCL.h"

/**
 *	Access operator.
 */
int RCL::operator [] (const int i) const
{
	return _list[i].first;
}

/**
 *	Getter for element at position i.
 */
int RCL::at(const int i) const
{
	return _list[i].first;
}

/**
 *	Size of the internal list.
 */
int RCL::size() const
{
	return _list.size();
}

/**
 *	First element of the list.
 */
int RCL::head() const
{
	return _list.front().first;
}

/**
 *	Last element of the list.
 */
int RCL::tail() const
{
	return _list.back().first;
}

/**
 *	Gets an element at random in the list.
 */
int RCL::get() const
{
	int num = rand() % _list.size();
	
	return _list[num].first;
}

void RCL::clear()
{
	_list.clear();
}

/**
 *	Adds an element to the list.
 */
void RCL::add(const int i, const double u)
{
	if (_list.empty()) {
		_list.push_back(std::pair<int, double> (i, u));
	} else {
		std::vector<std::pair<int, double> >::iterator it = _list.begin();
	
		// We order variables by their interest, putting the most interesting first
		while (it->second > u && it != _list.end()) {
			++it;
		}
	
		_list.insert(it, std::pair<int, double> (i, u));
	}
}

std::ostream& operator << (std::ostream &os, const RCL &rcl)
{
	int i = 0;

	os << "RCL : ";
	
	for (i = 0; i < rcl.size() - 1; i++) {
		os << 'x' << rcl.at(i) + 1 << ", ";
	}
	
	if (rcl.size() > 0) {
		os << 'x' << rcl.tail() + 1 << ".\n";
	}
	
	return os;
}

/*
std::vector<std::pair<int, double> >::iterator RCL::begin()
{
	return _list.begin();
}

std::vector<std::pair<int, double> >::iterator RCL::end()
{
	return _list.end();
}

std::ostream& operator << (std::ostream &os, const RCL &rcl)
{
	std::vector<std::pair<int, double> >::iterator it = rcl.begin();
	
	do {
		os << 'x' << it->first << ',';
		++it;
	} while (it != rcl.end());
	
	return os << 'x' << it->first;
}
*/

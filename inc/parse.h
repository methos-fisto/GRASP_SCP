#ifndef PARSE_H
#define PARSE_H

#include <fstream>

/**
 *	Parse input file into given parameters.
 *
 *	@param ifstream* file to parse
 *	@param int       number of vars
 *	@param int       number of constraints
 *	@param int*      variables' coefs
 *	@param int**     constraints' coefs
 */
void parse(std::ifstream*&, int&, int&, int*&,  int**&);

#endif

#include "scp.h"

/**
 *	Main.
 *
 *	@param int
 *	@param char**	
 *
 *	@return int 1 if success, 0 otherwise
 */
int main(int argc, char** argv)
{
	std::ifstream *f = NULL;
	
	if (argc != 2) {
		std::cout << "Ce programme s'appelle : ./scp <fichier>" << std::endl;
		
		return 0;
	} else {
		f = new std::ifstream(argv[1]);
		
		if (!f->good()) {
			std::cout << "Fichier " << argv[1] << " inconnu." << std::endl;
			
			return 0;
		}
	}
	
	int nbCnst = 0, nbVars = 0;
	int *costs = NULL;
	int **cnst = NULL;
	
	parse(f, nbCnst, nbVars, costs, cnst);
	
	int i = 0, j = 0;
	
	std::cout << "Costs : ";
	for (j = 0; j < nbVars; j++) {
		std::cout << costs[j] << ' ';
	}
	std::cout << std::endl;
	
	std::cout << "Constraints : " << std::endl;
	for (i = 0; i < nbCnst; i++) {
		for (j = 0; j < nbVars; j++) {
			std::cout << cnst[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	
	double alpha = 0.0;
	int    n     = 0;
	char   in[4];
	
	std::cout << "Sélectionnez alpha : ";
	std::cin >> in;
	alpha = atof(in);
	
	std::cout << "Sélectionnez n : ";
	std::cin >> in;
	n = atoi(in);
	
	int *solution = NULL;
	
	construct(cnst, costs, alpha, solution, nbCnst, nbVars);
	
	return 1;
}

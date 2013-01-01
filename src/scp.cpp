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
	
	f->close();
	
	double alpha = 0.0;
	int    n     = 0, t = 0;
	char   in[4];
	
	std::cout << "Sélectionnez alpha : ";
	std::cin >> in;
	alpha = atof(in);
	
	std::cout << "Sélectionnez n     : ";
	std::cin >> in;
	n = atoi(in);
	
	std::cout << "Sélectionnez le type (0 = max, 1 = min) : ";
	std::cin >> in;
	t = atoi(in);
	
	srand(time(NULL));
	
	Grasp grasp = Grasp(alpha, n, t, nbVars, nbCnst, costs, cnst);
	// Solution *sol  = new Solution(nbVars, solution, costs);
	
	for (int i = 0; i < 25; i++) {
		grasp.solve(i);
	}
	
	return 1;
}

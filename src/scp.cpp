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
	
	double last = 0.0, alpha = 0.0;
	int    n = 0, type = 0, manual = 0, i = 0;
	char   in[4];
	
	std::ofstream *g = new std::ofstream();
	
	g->open("res/alpha.dat");
	
	std::cout << "Sélectionnez le type de GRASP (0 = manuel, 1 = auto) : ";
	std::cin >> in;
	manual = atoi(in);
	
	std::cout << "Sélectionnez le type de alpha     (0 = max, 1 = min) : ";
	std::cin >> in;
	type = atoi(in);
	
	if (manual == Grasp::G_MANUAL) {
		std::cout << "Sélectionnez alpha : ";
		std::cin >> in;
		alpha = atof(in);
	}
	
	std::cout << "Sélectionnez la longueur d'un run                    : ";
	std::cin >> in;
	n = atoi(in);
	
	srand(time(NULL));
	
	Grasp grasp = Grasp(alpha, n, type, nbVars, nbCnst, costs, cnst);
	
	for (i = 1; i < 25; i++) {
		if (manual == Grasp::G_REACTIVE) {
			grasp.setAlpha(grasp.alpha(), last);
		}
		
		last = grasp.solve(i);
	
		*g << i << '\t' << grasp.alpha() << '\n';
	}
	
	g->close();
	
	return 1;
}

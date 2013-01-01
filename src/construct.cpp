#include "construct.h"

Solution* construct(
	int**& mat_contrainte, int*& tab_couts
	, const double& alpha, int& nbC, int& nbN
	, const int &type
) {
	int i = 0, j = 0, respect = 0, presence = 0;
	bool admissible = false;
	double *utilite = new double[nbN];
	double  umax    = 0.0, max = 0.0, min = DBL_MAX;
	
	std::set<int> a_traiter;
	std::vector<int> RCL;
	std::set<int>::iterator it;
	
	Solution* solution = new Solution(nbN);
	
	for(i = 0; i < nbC; i++){
		a_traiter.insert(i);
	}
	
	while( !admissible ){
		//utilité
		// utilite = new double[nbN];
		max     = 0.0;
		min     = DBL_MAX;
		
		for(j = 0 ; j < nbN ;j++){
			presence = 0;
			
			for(it = a_traiter.begin(); it != a_traiter.end(); it++){
				i = *it;
				if(mat_contrainte[i][j] == 1){
					presence++;
				}
			}
			
			// std::cout << 'x' << j + 1 << "\tpresence = " << presence << "\tcout = " << tab_couts[j] << "\tuti = " << (double) presence/ (double) tab_couts[j] << std::endl;
			utilite[j] = (double) presence / (double) tab_couts[j];
			
			if (utilite[j] > max) {
				max = utilite[j];
			}
			
			if (utilite[j] < min) {
				min = utilite[j];
			}
		}
		//sélection
		// std::cout << "Umax = " << max;
		
		if (type == Grasp::T_MAX) {
			umax = alpha * max;
		} else { // type == Grasp::T_MIN
			umax = min + alpha * (max - min);
		}
		
		// std::cout << "\tSeuil = " << max;
		// std::cout << "\tRCL = ";
		for(j = 0 ; j < nbN ;j++) {
			if(utilite[j] >= umax) {
				RCL.push_back(j);
				// std::cout << j + 1 << " ";
			}
		}
		
		// std::cout << "\nChoisi = ";
		j = rand() % RCL.size();
		// std::cout << RCL.at(j) + 1 << '\n';
		i = RCL.at(j);
		solution->set(i, 1, tab_couts[i]);
		
		RCL.clear();
		
		//admissibilité
		a_traiter.clear();
		for( i = 0; i < nbC; i++){
			respect = 0;
			for( j = 0; j < nbN; j++){
				respect += mat_contrainte[i][j] * solution->at(j);
			}
			
			if(respect == 0){
				a_traiter.insert(i);
			}
		}
		
		if(a_traiter.size() == 0){
			admissible = true;
		} else {
			// std::cout << '\n';
		}
	}
	
	// std::cout << "Premiere solution : ";
	max = solution->val();
	// std::cout << "Pour un cout de " << max << "\n";
	
	return solution;
}

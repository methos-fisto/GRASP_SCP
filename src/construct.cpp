#include "construct.h"

Solution* construct(
	int**& mat_contrainte, int*& tab_couts
	, const double& alpha, int& nbC, int& nbN
) {
	int i, j, respect, presence;
	bool admissible = false;
	double* utilite;
	double max;
	std::set<int> a_traiter;
	std::vector<int> RCL;
	std::set<int>::iterator it;
	
	for(i = 0; i < nbC; i++){
		a_traiter.insert(i);
	}
	
	Solution* solution = new Solution(nbN);
	
	srand(time(NULL));
	
	while( !admissible ){
		//utilité
		utilite = new double[nbN];
		for(j = 0 ; j < nbN ;j++){
			presence =0;
			for(it = a_traiter.begin(); it != a_traiter.end(); it++){
				i = *it;
				if(mat_contrainte[i][j] == 1){
					presence++;
				}
			}
			// std::cout << 'x' << j + 1 << "\tpresence = " << presence << "\tcout = " << tab_couts[j] << "\tuti = " << (double) presence/ (double) tab_couts[j] << std::endl;
			utilite[j] = (double) presence / (double) tab_couts[j];
		}
		//sélection
		max = 0;
		for(j = 0 ; j < nbN ;j++){
			if(utilite[j] > max){
				max = utilite[j];
			}
		}
		// std::cout << "Umax = " << max;
		max = alpha*max;
		// std::cout << "\tSeuil = " << max;
		// std::cout << "\tRCL = ";
		for(j = 0 ; j < nbN ;j++){
			if(utilite[j] >= max){
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
		delete[] utilite;
		
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
	// std::cout << "\nPour un cout de " << max << "\n";
	
	return solution;
}

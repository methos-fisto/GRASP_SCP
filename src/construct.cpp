#include "construct.h"

Solution* construct(
	int**& mat_contrainte, int*& tab_couts
	, const double& alpha, int& nbC, int& nbN
) {
	int i = 0, j = 0, respect = 0, presence = 0;
	bool admissible = false;
	double* utilite;
	double max = 0.0;
	
	std::set<int> a_traiter;
	std::vector<int> RCL;
	std::set<int>::iterator it;
	
	Solution* solution = new Solution(nbN);
	
	for(i = 0; i < nbC; i++){
		a_traiter.insert(i);
	}
	
	while( !admissible ){
		//utilit�
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
		//s�lection
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
		
		//admissibilit�
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

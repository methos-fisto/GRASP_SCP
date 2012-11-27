void construct(int**& mat_contrainte, int*& tab_couts, double& alpha, int*& solution, int& nbC, int& nbN){

	int i, j, respect;
	bool admissible = false;
	double* utilite;
	double max;
	set<int> a_traiter;
	vector<int> RCL;
	set<int>::iterator it;
	for(i = 0; i < nbC; i++){
		a_traiter.insert(i);
	}
	solution = new int[nbN];
	for(i = 0; i < nbN; i++){
		solution[i] = 0;
	}
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
			utilite[j] = presence/tab_couts[j];
		}
		//sélection
		max = 0;
		for(j = 0 ; j < nbN ;j++){
			if(utilite[j] > max){
				max = utilite[j];
			}
		}
		std::cout << "\nUmax = " << max;
		max = alpha*max;
		std::cout << "\nseuil = " << max;
		std::cout << "\nRCL = ";
		for(j = 0 ; j < nbN ;j++){
			if(utilite[j] >= max){
				RCL.push_back(j);
				std::cout << j + 1 << " ";
			}
		}
		std::cout << "\nChoisi = ";
		j = rand() % RCL.size();
		std::cout << RCL.at(j);
		solution[RCL.at(j)]= 1;
		RCL.clear();
		delete[] utilite;
		
		//admissibilité
		a_traiter.clear();
		for( i = 0; i < nbC; i++){
			respect = 0;
			for( j = 0; j < nbN; j++){
				respect += mat_contrainte[i][j]*solution[j]
			}
			
			if(respect == 0){
				a_traiter.insert(i);
			}
		}
		
		if(a_traiter.size() == 0){
			admissible = true;
		}
	}
	
	std::cout << "Premiere solution :\n";
	max = 0;
	for(j = 0; j < nbN; j++){
		if(solution[j] == 1){
			std::cout<< "x" << j+1 << "\n";
			max += tab_couts[j];
		}
	}
	std::cout << "\nPour un cout de " << max << "\n";
}
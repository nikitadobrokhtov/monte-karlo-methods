#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <sstream>
#include <string>

using namespace std;

void print_lattice(const vector<vector<int>>& lattice){
	int len = lattice.size();
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			cout << lattice[i][j] << " ";
		}
		cout << endl;
	}
}


int generate_number(){
	int myArray[2] = { 1, -1 };
	int randomIndex = rand() % 2;
	return myArray[randomIndex];
}



vector<vector<int>> init_lattice (int n){

	//Create a nxn lattice with random spin configuration

	srand(time(0));
	vector<vector<int>> lattice;	

	for (int i = 0; i < n; i++){
		vector<int> row;
		for(int j = 0; j < n; j++){
			row.push_back(generate_number());
		}
		lattice.push_back(row);
	}
	return lattice;
}

int deltaE(int S0, int Sn, int J, int H){

	// Energy difference for a spin flip

	return 2 * S0 * (H + J * Sn);
}


vector<int> ising(int n, unsigned long long nsteps, int H, int J, int T){
	vector<vector<int>> lattice = init_lattice(n);
	int energy = 0;
	vector<int> energies;


	for (int step; step < nsteps; step++){

		int i = rand() % n;
		int j = rand() % n;
		
		// Periodic Boundary Condition
		int Sn = lattice[(n + i - 1) % n][j] + lattice[(i + 1) % n][j] +  lattice[i][(n + j - 1) % n] + lattice[i][(j + 1) % n];


		int dE = deltaE(lattice[i][j], Sn, J, H);

		if(dE < 0 || ((double)rand()/(double)RAND_MAX) < exp(-1 * (double)dE / (double)T)){
			lattice[i][j] = -lattice[i][j];
			energy += dE;
			if(step % 1000 == 0){
				energies.push_back(energy);
			}
		}
	}

	return energies;
}


//prints [low,high]
//rand()%(high- low + 1) + low << endl;


int main(){
	srand(time(0));
	//n, nsteps, H, J, T - arguments for ising

	//auto t1 = chrono::high_resolution_clock::now(); 
	vector<int> energies = ising(1000, 1000000000, 0, 1, 1);
	//auto t2 = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::seconds>( t2 - t1 ).count();
	//cout << duration;

	for(int i = 0; i < energies.size(); i++){
		cout << energies[i] << endl;
	}




	return 0;
}




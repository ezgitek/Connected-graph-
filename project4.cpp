/*
Student Name: Ezgi Tekdemir
Student Number: 2014400090
Project Number: 4
Operating System: Virtual Machine
Compile Status: Compiling
Program Status: Working
Notes: 
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

int NUM_OF_CITIES;
int NUM_OF_ROADS;
int NUM_OF_INFECTED;
int TIME;

vector<int>* vertices;
vector <int> infected;
bool* isInfected;
bool* marked;
int connected_states = 0;

void importData (char* inputFile){
	ifstream in (inputFile);
	in >> NUM_OF_CITIES;
	in >> NUM_OF_ROADS;
	in >> NUM_OF_INFECTED;
	in >> TIME;

	isInfected = new bool[NUM_OF_CITIES+1];
	marked = new bool [NUM_OF_CITIES+1];
	vertices = new vector<int> [NUM_OF_CITIES+1];
	vertices[0].push_back(-1); //dummy 

	for(int i=0; i<NUM_OF_ROADS; i++){
		int a; int b;
		in >> a;
		in >> b;

		vertices[a].push_back(b);
		vertices[b].push_back(a);
	}

	for(int i=0; i<NUM_OF_INFECTED; i++){
		int inf;
		in >> inf;
		infected.push_back(inf);
		isInfected[inf] = true;
	}
}

void DFS (int vertex){

if(!marked[vertex]){
	marked[vertex] = true;

		for(unsigned int i=0; i<vertices[vertex].size(); i++){
			if((!isInfected[vertices[vertex][i]]) && (!marked[vertices[vertex][i]])){
				DFS(vertices[vertex][i]);
			}
		}
}

}

void printOutput (char* outputFile){

		ofstream out (outputFile);

	for(int i=0; i<TIME; i++){
		
		vector <int> currently_infected;

		for(unsigned int j=0; j<infected.size(); j++){
			for(unsigned int k=0; k<vertices[infected[j]].size(); k++){

				int neighbour = vertices[infected[j]][k];

				if((!isInfected[neighbour])){
					isInfected[neighbour] = true;
					currently_infected.push_back(neighbour);
				}

			}	
		}
		infected.insert(infected.end(), currently_infected.begin(), currently_infected.end());
		
		if(infected.size() == (unsigned int) NUM_OF_CITIES){
			out << 0 << endl;
			return;
		}
	}

	for(int i=1; i<=NUM_OF_CITIES; i++){

		if(!isInfected[i] && !marked[i]){
			DFS(i);
			connected_states++;
		}else{
			continue;
		}
	}

	out << connected_states << endl;

}

int main(int argc, char *argv[]) {
	importData(argv[1]);
	printOutput(argv[2]);

	return 0;
}
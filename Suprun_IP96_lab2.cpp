#include<iostream>
#include<ctime>
#include<random>
#include<iomanip>
#include<vector>

using namespace std;

class Graph{
 public:
 //functions
   Graph(int number);
   void initMatrix();
   void initPheramons();
   void generDistances();
   void output();

//variaties 
int numberNodes;
int** distanceMatrix;
double** pheramonsMatrix;
};


class Ant{
public:
//functions
 Ant();

//variaties
vector<int>nodesTaboo;
};

class ColonAnts{
public:
 double alpha = 3;//
 double beta = 2;//
 double evaporate = 0.7;//коефіцієнт випаровування
 double tauStart = 1;//початковий рівень феромону
 int eliteAnts = 10;
 int traditionalAnts = 35;
double pheromonsByOne = 5;
double pheromonsByElite = 10;
};

Graph::Graph(int number){
  numberNodes = number;
  initMatrix();
  generDistances();
  output();
}

void Graph::initMatrix(){
    srand(time(NULL));
    distanceMatrix = new int*[numberNodes];
    for(int i =0; i < numberNodes; i++){
        distanceMatrix[i] = new int[numberNodes];
    }
}

void Graph::initPheramons(){
    srand(time(NULL));
    pheramonsMatrix = new double*[numberNodes];
    for(int i =0; i < numberNodes; i++){
        pheramonsMatrix[i] = new double[numberNodes];
    }
}

void Graph::generDistances(){
    for(int i =0; i < numberNodes; i++){
        for(int j =0; j < numberNodes; j++){
            distanceMatrix[i][j] = rand()%40;
            if(i==j)
            distanceMatrix[i][j]=0;
        }
    }
}

void Graph::output(){
    for(int i =0; i < numberNodes; i++){
        for(int j =0; j < numberNodes; j++){
            cout<<setw(5)<<distanceMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
  Graph graph(7);
}
#include<iostream>
#include<ctime>
#include<random>
#include<iomanip>

using namespace std;

class Graph{
 public:
 //functions
   Graph(int number);
   void initMatrix();
   void generDistances();
   void output();

//variaties 
int numberNodes;
int** distanceMatrix;
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

void Graph::generDistances(){
    for(int i =0; i < numberNodes; i++){
        for(int j =0; j < numberNodes; j++){
            distanceMatrix[i][j] = rand()%100;
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
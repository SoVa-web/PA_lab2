#include<iostream>
#include<ctime>
#include<random>
#include<iomanip>
#include<vector>

using namespace std;

class Graph{
   
 public:
 //functions
   Graph(){};
   Graph(int number);
   void initMatrix();
   void initPheramons();
   void generDistances();
   void initVision();
   void output();

//variaties 
int numberNodes;
int** distanceMatrix;
double** pheramonsMatrix;
double** visionMaxtrix;
};

class Ant{
public:
//functions
 Ant(){};

//variaties
vector<int>nodesTaboo;
 bool areYouElyte;
 double alpha = 3;//
 double beta = 2;//
 double evaporate = 0.7;//коефіцієнт випаровування
 double tauStart = 1;//початковий рівень феромону
 int eliteAnts = 10;
 int traditionalAnts = 35;
double pheromonsByOne = 5;
double pheromonsByElite = 10;
};


class AntAlgorithm{
public:
//func
AntAlgorithm(Graph graph,  int number);
AntAlgorithm(Ant ant);
void greedySearch();
//var
double optimL;
double minL;
Graph graph;
 int numberAnts;
 Ant* ants;
};


AntAlgorithm::AntAlgorithm(Graph graph,  int number){
this->graph = graph;
numberAnts = number;
greedySearch();
}

AntAlgorithm::AntAlgorithm(Ant ant){
ants = new Ant[numberAnts];
 for(int i =1; i < numberAnts+1; i++){
   if(numberAnts-ant.eliteAnts)
     ants[i-1].areYouElyte  = false;
    else
     ants[i-1].areYouElyte  = true;
  }
}

void AntAlgorithm::greedySearch(){
    this->minL = 0;
    vector<int> way;
    vector<int> nodes;
    bool visited[graph.numberNodes];
    for(int i =0; i<graph.numberNodes; i++){
        visited[i] = true;
    }
    int next = 0;
    visited[next] = false;
    way.push_back(next);
    while (way.size()<graph.numberNodes){
        for(int i =0; i < graph.numberNodes; i++){
            if(next != i && visited[i] ){
              nodes.push_back(i);
            }
        }
        int dist = graph.distanceMatrix[next][nodes[0]];
        int k =next;
       for(int i =0; i < nodes.size(); i++){
          if(dist >= graph.distanceMatrix[next][nodes[i]]){
              dist = graph.distanceMatrix[next][nodes[i]];
              k = nodes[i];
          }
       }
       next =k;
        visited[next] = false;
        way.push_back(next);
        minL+=graph.distanceMatrix[way.size()-2][way.size()-1];
        nodes.clear();
    }
    minL+=graph.distanceMatrix[way.size()-1][0];
    way.push_back(way[0]);
    cout<<"Lmin"<<minL<<endl;
    cout<<"Way: ";
    for(int i =0 ;i < way.size(); i++){
        cout<<way[i]<<"-->";
    }
    way.clear();
}

Graph::Graph(int number){
  numberNodes = number;
  initMatrix();
  generDistances();
  initPheramons();
  initVision();
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
    for(int i =0; i < numberNodes; i++){
        for(int j=0; j < numberNodes; j++){
            pheramonsMatrix[i][j] =1+ rand()%10;
            pheramonsMatrix[i][j]/=10;
            if(i == j){
                 pheramonsMatrix[i][j]=0;
            }
        }
    }
}

void Graph::initVision(){
    srand(time(NULL));
    visionMaxtrix = new double*[numberNodes];
    for(int i =0; i < numberNodes; i++){
       visionMaxtrix[i] = new double[numberNodes];
    }
    for(int i =0; i < numberNodes; i++){
        for(int j=0; j < numberNodes; j++){ 
            if(i != j){
                visionMaxtrix[i][j] = 1.0/distanceMatrix[i][j];
            }else{
                 visionMaxtrix[i][j]=0;
            }
        }
    }
    for(int i =0; i < numberNodes; i++){
        for(int j=0; j < numberNodes; j++){ 
            cout<<setw(10)<<visionMaxtrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::generDistances(){
    for(int i =0; i < numberNodes; i++){
        for(int j =0; j < numberNodes; j++){
            distanceMatrix[i][j] = 1 + rand()%40;
            distanceMatrix[j][i] = distanceMatrix[i][j];
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
  Ant ant;
  int numberAnts = ant.traditionalAnts+ant.eliteAnts;
  AntAlgorithm algorithm(graph, numberAnts);
  AntAlgorithm algo(ant);
}
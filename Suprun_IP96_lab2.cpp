#include<iostream>
#include<ctime>
#include<random>
#include<iomanip>
#include<vector>
#include<cmath>

using namespace std;



class Ant{
public:
//functions
 Ant(){};

//variaties
vector<int>way;
int optL =0;;
bool areYouElyte;
double deltaTau =0;
};

class Algorithm{
 public:
 Algorithm(Ant ant, int number);
   void initMatrix();
   void initPheramons();
   void generDistances();
   void initVision();
   void output();
   void greedySearch();
   void placingAnts();
   void algorithm();
   int probability(int i, vector<int> j);
   double tau(int minL, int optL, bool elit);

   
   //variaties 
int numberNodes;
int** distanceMatrix;
double** pheramonsMatrix;
double** visionMaxtrix;
double minL;
 int numberAnts;
 Ant* ants;
 int* placeAnts;
 double alpha = 3;//
 double beta = 2;//
 double evaporate = 0.7;//коефіцієнт випаровування
 double tauStart = 1;//початковий рівень феромону
 int eliteAnts = 10;
 int traditionalAnts = 35;
double pheromonsByOne = 5;
double pheromonsByElite = 10;
const int iter = 10;
};

Algorithm::Algorithm(Ant ant, int number){
    numberNodes = number;
  initMatrix();
  generDistances();
  initPheramons();
  initVision();
  output();
  numberAnts = eliteAnts+traditionalAnts;
  greedySearch();
  ants = new Ant[numberAnts];
 for(int i =0; i < numberAnts; i++){
   if(numberAnts-eliteAnts)
     ants[i].areYouElyte  = false;
    else
     ants[i].areYouElyte  = true;
  }
}

void Algorithm::algorithm(){
   for(int i =0; i< iter; i++){//time life
      for(int j =0; j < numberAnts; j++){//cycle for ants
           vector<int> nodes;
           bool visited[numberNodes];
           for(int j =0; j < numberNodes; j++){
              visited[i] = true;
           }
            int next = 0;
            visited[next] = false;
            ants[j].way.push_back(next);
    while (ants[j].way.size()<numberNodes){
        for(int k =0; k < numberNodes; k++){
            if(next != k && visited[k] ){
              nodes.push_back(k);
            }
        }
        int prob = probability(next, nodes);//next node
        next = prob;
        visited[next] = false;
        ants[j].way.push_back(next);
        ants[j].optL+=distanceMatrix[ants[j].way.size()-2][ants[j].way.size()-1];
        nodes.clear();
    }
    ants[j].optL+=distanceMatrix[ants[j].way.size()-1][0];
    ants[j].way.push_back(ants[j].way[0]);
      ants[j].deltaTau = tau(minL, ants[j].optL, ants[j].areYouElyte);
      }//end cycle of  ants
      //оновлення параметрів
   }
}

double Algorithm::tau(int minL, int optL, bool elit ){
    double delta =0;

    return delta;
}

int Algorithm::probability(int i, vector<int> j){
 double sum = 0;
 for(int k =0; k < j.size(); k++){
    sum+=pow(pheramonsMatrix[i][j[k]], alpha )*pow(visionMaxtrix[i][j[k]], beta);
 }
 vector<double> prob;
 for(int k =0; k < j.size(); k++){
     int a = (pow(pheramonsMatrix[i][j[k]], alpha )*pow(visionMaxtrix[i][j[k]], beta))/sum;
 }
 double b = prob[0];
 int maximum = 0; 
 for(int k =0; k < prob.size(); k++){
     if(b<=prob[k]){
         b = prob[k];
         maximum = k;
     }
 }
return j[maximum];
}

void Algorithm::placingAnts(){
    placeAnts = new int[eliteAnts+traditionalAnts];
    for(int i =0; i < numberAnts; i++){
        placeAnts[i] = rand()%numberNodes;
        cout<<placeAnts[i]<<" ";
    }
}

void Algorithm::initMatrix(){
    srand(time(NULL));
    distanceMatrix = new int*[numberNodes];
    for(int i =0; i < numberNodes; i++){
        distanceMatrix[i] = new int[numberNodes];
    }
}

void Algorithm::initPheramons(){
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

void Algorithm::initVision(){
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

void Algorithm::generDistances(){
    for(int i =0; i < numberNodes; i++){
        for(int j =0; j < numberNodes; j++){
            distanceMatrix[i][j] = 1 + rand()%40;
            distanceMatrix[j][i] = distanceMatrix[i][j];
            if(i==j)
            distanceMatrix[i][j]=0;
        }
    }
}

void Algorithm::output(){
    for(int i =0; i < numberNodes; i++){
        for(int j =0; j < numberNodes; j++){
            cout<<setw(5)<<distanceMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Algorithm::greedySearch(){
    this->minL = 0;
    vector<int> way;
    vector<int> nodes;
    bool visited[numberNodes];
    for(int i =0; i<numberNodes; i++){
        visited[i] = true;
    }
    int next = 0;
    visited[next] = false;
    way.push_back(next);
    while (way.size()<numberNodes){
        for(int i =0; i < numberNodes; i++){
            if(next != i && visited[i] ){
              nodes.push_back(i);
            }
        }
        int dist = distanceMatrix[next][nodes[0]];
        int k =next;
       for(int i =0; i < nodes.size(); i++){
          if(dist >= distanceMatrix[next][nodes[i]]){
              dist = distanceMatrix[next][nodes[i]];
              k = nodes[i];
          }
       }
       next =k;
        visited[next] = false;
        way.push_back(next);
        minL+=distanceMatrix[way.size()-2][way.size()-1];
        nodes.clear();
    }
    minL+=distanceMatrix[way.size()-1][0];
    way.push_back(way[0]);
    cout<<"Lmin"<<minL<<endl;
    cout<<"Way: ";
    for(int i =0 ;i < way.size(); i++){
        cout<<way[i]<<"-->";
    }
    way.clear();
}


int main(){
  Ant ant;
  Algorithm algo(ant, 46);
  algo.placingAnts();
}
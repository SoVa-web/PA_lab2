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
   double tau( int optL, bool elit);

   
   //variaties 
int numberNodes;
int** distanceMatrix;
double** pheramonsMatrix;
double** visionMaxtrix;
double minL;
 int numberAnts;
 Ant* ants;
 int* placeAnts;
 vector<int>way0;
 double alpha = 3;//
 double beta = 2;//
 double evaporate = 0.7;//коефіцієнт випаровування
 double tauStart = 1;//початковий рівень феромону
 int eliteAnts = 10;
 int traditionalAnts = 35;
const int iter = 10;
};

Algorithm::Algorithm(Ant ant, int number){
    numberNodes = number;
  initMatrix();
  generDistances();
  initPheramons();
  initVision();
  //output();
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
           for(int k =0; k < numberNodes; k++){
              visited[k] = true;
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
      ants[j].deltaTau = tau( ants[j].optL, ants[j].areYouElyte);
      }//end cycle of  ants
      int L = ants[0].optL;
      int index = 0;
      for(int k =0; k < numberAnts; k++){
          if(L>=ants[k].optL){
              L=ants[k].optL;
              index = k;
          }
      }
      way0 = ants[index].way;
      minL = L;
      int sumTau = 0;
      for(int k =0; k < numberAnts; k++){
          sumTau+=ants[k].deltaTau;
      }
      for(int j =0; j <numberNodes; j++){
          for(int k =0; k < numberNodes; k++){
             if(j!=k){
                 pheramonsMatrix[j][k] = (1-evaporate)*pheramonsMatrix[j][k]+sumTau;
             }
          }
      }
      //оновлення параметрів
      for(int k =0; k < numberAnts; k++){
           ants[k].way.clear();
      }
   }
   cout<<"minLFinl: "<<minL;
}

double Algorithm::tau( int optL, bool elit ){
    double delta =0;
    if(elit){
        delta = (2*this->minL)/optL;
    }else{
        delta = this->minL/optL;
    }
    return delta;
}

int Algorithm::probability(int i, vector<int> j){
 double sum = 0;
 for(int k =0; k < j.size(); k++){
    sum+=pow(pheramonsMatrix[i][j[k]], alpha )*pow(visionMaxtrix[i][j[k]], beta);
 }
 vector<double> prob;
 for(int k =0; k < j.size(); k++){
     double a = (pow(pheramonsMatrix[i][j[k]], alpha )*pow(visionMaxtrix[i][j[k]], beta))/sum;
    prob.push_back(a);
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
            pheramonsMatrix[j][i]/=10;
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
    /*for(int i =0; i < numberNodes; i++){
        for(int j=0; j < numberNodes; j++){ 
            cout<<setw(10)<<visionMaxtrix[i][j]<<" ";
        }
        cout<<endl;
    }*/
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
    vector<int> nodes;
    bool visited[numberNodes];
    for(int i =0; i<numberNodes; i++){
        visited[i] = true;
    }
    int next = 0;
    visited[next] = false;
    way0.push_back(next);
    while (way0.size()<numberNodes){
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
        way0.push_back(next);
        minL+=distanceMatrix[way0.size()-2][way0.size()-1];
        nodes.clear();
    }
    minL+=distanceMatrix[way0.size()-1][0];
    way0.push_back(way0[0]);
    cout<<"Lmin"<<minL<<endl;
    cout<<"Way: ";
    for(int i =0 ;i < way0.size(); i++){
        cout<<way0[i]<<"-->";
    }
}


int main(){
  Ant ant;
  Algorithm algo(ant, 300);
  algo.placingAnts();
  algo.algorithm();
}
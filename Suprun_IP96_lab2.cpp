#include<iostream>
#include<ctime>
#include<random>
#include<iomanip>
#include<vector>
#include<cmath>
#include<list>

using namespace std;





class Algorithm{
 public:
 Algorithm( int number);
   void initMatrix();
   void initPheramons();
   void generDistances();
   void initVision();
   void output();
   void greedySearch();
   void placingAnts();
   void algorithm();
   int probability(int i, vector<int> j);
   double tau(  double optL, bool elit);

   
   //variaties 
int numberNodes;
int** distanceMatrix;
double** pheramonsMatrix;
double** visionMaxtrix;
double minL;
double* optL;
double* deltaTau;
 int numberAnts;
 //Ant* ants;
 int* placeAnts;
 bool* areYouElyte;
 vector<int>way0;
 int eliteAnts = 10;
 vector<vector<int>> way;
 double alpha = 3;//
 double beta = 2;//
 double evaporate = 0.7;//коефіцієнт випаровування
 
 int traditionalAnts = 35;
 int iter = 1000;
};

Algorithm::Algorithm( int number){
    numberNodes = number;
  initMatrix();
  generDistances();
  initPheramons();
  initVision();
  //output();
  numberAnts = eliteAnts+traditionalAnts;
  greedySearch();
  areYouElyte = new bool[numberAnts];
  optL = new double[numberAnts];
  deltaTau = new double[numberAnts];
 for(int i =0; i < numberAnts; i++){
     deltaTau[i] =0;
     optL[i]=0;
   if(i < numberAnts-eliteAnts)
     areYouElyte[i]  = false;
    else
     areYouElyte[i]  = true;
  }
  for(int i =0; i < numberAnts; i++){
      vector<int> path;
    way.push_back(path);
  }
}

void Algorithm::algorithm(){
   for(int i =0; i< iter; i++){//time life
      for(int j =0; j < numberAnts; j++){//ccoutycle for ants
           vector<int> nodes;
           bool visited[numberNodes];
           for(int k =0; k < numberNodes; k++){
              visited[k] = true;
           }
            int next = placeAnts[j];
            visited[next] = false;
            way[j].push_back(next);
    while (way[j].size()<numberNodes){
        for(int k =0; k < numberNodes; k++){
            if(next != k && visited[k] ){
              nodes.push_back(k);
            }
        }
        int prob = probability(next, nodes);//next node
        next = prob;
        visited[next] = false;
        way[j].push_back(next);
        nodes.clear();
    }
    way[j].push_back(way[j][0]);
   /* for(int l =0; l < way[j].size(); l++){
        cout<<way[j][l]<<"->";
    }*/
    for(int l=0; l < way[j].size()-1;l++){
         optL[j]+=(distanceMatrix[way[j][l]][way[j][l+1]]);
    }
   // cout<<optL[j]<<endl;
      deltaTau[j] = tau( optL[j], areYouElyte[j]);
      }//end cycle of  ants
      int L = optL[0];
      int index = 0;
      for(int k =0; k < numberAnts; k++){
          if(L>=optL[k]){
              L=optL[k];
              index = k;
          }
      }
      way0 = way[index];
      minL = L;
      int sumTau = 0;
      for(int k =0; k < numberAnts; k++){
          sumTau+=deltaTau[k];
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
           way[k].clear();
           optL[k] = 0;
      }
   }
   cout<<"minLFinl: "<<minL;
}

double Algorithm::tau( double optL, bool elit ){
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
    sum+=(pow(pheramonsMatrix[i][j[k]], alpha )*pow(visionMaxtrix[i][j[k]], beta));
 }
 vector<double> prob;
 for(int k =0; k < j.size(); k++){
     double a = (pow(pheramonsMatrix[i][j[k]], alpha )*pow(visionMaxtrix[i][j[k]], beta))/sum;
    prob.push_back(a);//cout<<"prob"<<a<<endl;
 }
 //cout<<"next"<<endl;
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
}


int main(){
  Algorithm algo(200);
  algo.placingAnts();
  algo.algorithm();
}
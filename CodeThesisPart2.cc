
//Iterated Public Goods Game, Envy, and Economic Bubbles: Code for Well-Mixed Model
// SimulationLOD : Defines the entry point for the console application.
//This is a simulation of iterated prisoners dilemma where the agents comptete to literally evolve their strategies over time. See complete paper here: https://www.dropbox.com/s/au6tp6dyi9eauzn/Thesis_PhilipGeurin_v6.doc?dl=0

// SimulationMixed.cpp : Defines the entry point for the console application.
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <math.h>
using namespace std;
//int xm[]={-1,0,1,1,1,0,-1,-1};
//int ym[]={-1,-1,-1,0,1,1,1,0};
int xz[]={0,1,0,-1};
int yz[]={1,0,-1,0};
double payofftable[4][4],realpayofftable[4][4];
class tagent{
    public:
    double FakeMoney,realmoney,punfair,penvy;
    //vector<double> slist;
    void setup(void);
    void inherit(tagent *giver, double mutationrate);
    void trade(tagent *trader);
};
 
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    FILE *f;
    int god;
    int a,b,c,d,z;
    int NumRuns=1024;
    double k=1;
    int count;
    double sum,TopMoney;
    int TopMoneyA,TopMoneyB;
    double punfairtotal,penvytotal,PerceivedMoneyTotal,moneytotal;
    vector<vector<tagent>> agents;
    //int countmax=10;// # of runs before reproduce
    int countmax=(int) atoi(argv[5]);
    double replacementrate = 0.02;
    double mutationrate = 0.02;
//make table
 
    double gamma=(double) atof(argv[2]);
    double r=(double) atof(argv[3]);
    double eps=(double) atof(argv[4]);
 
    payofftable[0][0]=0;
    payofftable[0][1]=0;
    payofftable[0][2]=gamma;
    payofftable[0][3]=gamma;
    payofftable[1][0]=0;
    payofftable[1][1]=0;
    payofftable[1][2]=gamma-eps;
    payofftable[1][3]=gamma-eps;
    payofftable[2][0]=-gamma;
    payofftable[2][1]=-gamma;
    payofftable[2][2]=r;
    payofftable[2][3]=r;
    payofftable[3][0]=-gamma;
    payofftable[3][1]=-gamma;
    payofftable[3][2]=r-eps;
    payofftable[3][3]=r-eps;
 
    //keeping track of 'real' money by making it all seperate
    realpayofftable[0][0]=0;
    realpayofftable[0][1]=0;
    realpayofftable[0][2]=gamma;
    realpayofftable[0][3]=gamma;
    realpayofftable[1][0]=0;
    realpayofftable[1][1]=0;
    realpayofftable[1][2]=gamma;
    realpayofftable[1][3]=gamma;
    realpayofftable[2][0]=-gamma;
    realpayofftable[2][1]=-gamma;
    realpayofftable[2][2]=r;
    realpayofftable[2][3]=r;
    realpayofftable[3][0]=-gamma;
    realpayofftable[3][1]=-gamma;
    realpayofftable[3][2]=r;
    realpayofftable[3][3]=r;
 
 
    for (a=0;a<4;a++){
        for (b=0;b<4;b++){
            //payofftable[b][a]=payofftable[a][b]+1;
            printf("%f ",payofftable[a][b]);
        }
        printf("\n");
    }
    printf("\n");
    for (a=0;a<4;a++){
        for (b=0;b<4;b++){
            //payofftable[b][a]=payofftable[a][b]+1;
            printf("%f ",realpayofftable[a][b]);
        }
        printf("\n");
    }
    printf("\n\n");
 
//setup
    srand(time(NULL));
    f=fopen(argv[1],"w+t");
    agents.resize(32);
    for (a=0;a<32;a++){
        agents[a].resize(agents.size());
        for (b=0;b<32;b++){
            agents[a][b].setup();
        }
    }
 
//START THE WORLD
    for (god=0;god<10000;god++){
 
    //Play the music            RANDOMLY, but still the same number of trades
        for (count=0;count<NumRuns;count++){
            a=rand()&31;
            b=rand()&31;
            for (z=0;z<4;z++){ //four trades per person, just like before
                c=rand()&31;
                d=rand()&31;
                agents[a][b].trade(&agents[c][d]);
            }
        }
 
    //1st of may!
        punfairtotal=0.0;
        penvytotal=0.0;
        PerceivedMoneyTotal=0.0;
        moneytotal=0.0;
        //find 'big man on campus'
        TopMoney=0.0;
        for (a=0;a<32;a++){
            for (b=0;b<32;b++){
                if (TopMoney<agents[a][b].FakeMoney){
                    TopMoney=agents[a][b].FakeMoney;
                    TopMoneyA=a;
                    TopMoneyB=b;
                }
            }
        }
 
        //replace with "Big Man"?
        for (a=0;a<32;a++){
            for (b=0;b<32;b++){
                if (replacementrate > (double) rand()/(double) RAND_MAX){
                    if (((double) rand()/(double) RAND_MAX)<(1/(1+exp((agents[a][b].FakeMoney-TopMoney)/k)))){   // This is the mysterious equation, k can be anything between 0.1 and 1
                        agents[a][b].inherit(&agents[TopMoneyA][TopMoneyB],mutationrate);
                    }
                }
            punfairtotal=punfairtotal+agents[a][b].punfair;
            penvytotal=penvytotal+agents[a][b].penvy;
            PerceivedMoneyTotal=PerceivedMoneyTotal+agents[a][b].FakeMoney;
            moneytotal=moneytotal+agents[a][b].realmoney;
            }
        }
        //printf("%i %f %f %f %f %f \n",god,PerceivedMoneyTotal/1024.0,moneytotal/1024.0,punfairtotal/1024.0,penvytotal/1024.0);
        fprintf(f,"%f %f %f %f %f \n",PerceivedMoneyTotal/1024.0,moneytotal/1024.0,punfairtotal/1024.0,penvytotal/1024.0);
    }
    fclose(f);
    return 0;
}
 
 
    ////////////////////////////////////////////////////////////////////////////////////////
 
    void tagent::setup(void){
        FakeMoney=10.0;
        realmoney=10.0;
        punfair=0.00;
        penvy=0.00;
    }
 
    void tagent::inherit(tagent *giver, double mutationrate){
        this->punfair=giver->punfair;
        this->penvy=giver->penvy;
        if (mutationrate>(double) rand()/ (double) RAND_MAX){ //chance to evolve
            this->punfair=((double) rand()/ (double) RAND_MAX);
        }
        if (mutationrate>(double) rand()/ (double) RAND_MAX){
            this->penvy=((double) rand()/ (double) RAND_MAX);
        }
        //this->FakeMoney=0.0; LEAVE THEM THEIR MONEY
    }
 
void tagent::trade(tagent *trader){
    int column;
    int row;
    if (this->punfair > ((double)rand()/(double)RAND_MAX)){
        if (this->penvy > ((double)rand()/(double)RAND_MAX)){
            row=3;
        }
        else{
            row=2;
        }
    }
    else{
        if (this->penvy > ((double)rand()/(double)RAND_MAX)){
            row=1;
        }
        else{
            row=0;
        }
    }
    if (trader->punfair > ((double)rand()/(double)RAND_MAX)){
        if (trader->penvy > ((double)rand()/(double)RAND_MAX)){
            column=3;
        }
        else{
            column=2;
        }
    }
    else{
        if (trader->penvy > ((double)rand()/(double)RAND_MAX)){
            column=1;
        }
        else{
            column=0;
        }
    }
    this->FakeMoney=this->FakeMoney+payofftable[row][column];
    trader->FakeMoney=trader->FakeMoney+payofftable[column][row];
    this->realmoney=this->realmoney+realpayofftable[row][column];
    trader->realmoney=trader->realmoney+realpayofftable[column][row];
}
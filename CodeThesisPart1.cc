


//Iterated Public Goods Game, Envy, and Economic Bubbles: Code for Spatial Model 
// SimulationLOD : Defines the entry point for the console application.
//This is a simulation of iterated prisoners dilemma where the agents comptete to literally evolve their strategies over time. See complete paper here: https://www.dropbox.com/s/au6tp6dyi9eauzn/Thesis_PhilipGeurin_v6.doc?dl=0

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
using namespace std;
//int xm[]={-1,0,1,1,1,0,-1,-1};
//int ym[]={-1,-1,-1,0,1,1,1,0};
int xz[]={0,1,0,-1};
int yz[]={1,0,-1,0};
double payofftable[4][4];
int god=0;
 
class tagent{
    public:
        tagent *ancestor;
        int nrPointingAtMe,born;
    double money,punfair,penvy;
    //vector<double> slist;
    tagent();
    ~tagent();
    void setup(void);
    void inherit(tagent *giver, double mutationrate);
    void trade(tagent *trader);
    void saveLOD(FILE *f);
};
 
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    FILE *f;
    int a,b,c,z;
    int count;
    double sum;
    double punfairtotal,penvytotal,moneytotal;
    vector<vector<tagent*>> agents;
    //int countmax=10;// # of runs before reproduce
    int countmax=(int) atoi(argv[5]);
    double replacementrate = 0.02;
    double mutationrate = 0.02;
    double NumDiscount;
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
 
    //show payofftable
    for (a=0;a<4;a++){
        for (b=0;b<4;b++){
            //payofftable[b][a]=payofftable[a][b]+1;
            printf("%f ",payofftable[a][b]);
        }
        printf("\n");
    }
    printf("\n");
 
//setup
    srand(time(NULL));
    //f=fopen(argv[1],"w+t");
    agents.resize(32);
    for (a=0;a<32;a++){
        agents[a].resize(agents.size());
        for (b=0;b<32;b++){
            agents[a][b]=new tagent;
            agents[a][b]->setup();
        }
    }
 
//START THE WORLD
        //punfairtotal=0.0;
        //penvytotal=0.0;
        //moneytotal=0.0;
        //NumDiscount=0;
    for (god=0;god<50000;god++){
        punfairtotal=0.0;
        penvytotal=0.0;
        moneytotal=0.0;
        NumDiscount=0.0;
    //Play the music
        for (count=0;count<countmax;count++){
            for (a=0;a<32;a++){
                for (b=0;b<32;b++){
                    for (z=0;z<5;z++){
                        agents[a][b]->trade(agents[(a+xz[z])&31][(b+yz[z])&31]);
                    }
                punfairtotal=punfairtotal+agents[a][b]->punfair;
                penvytotal=penvytotal+agents[a][b]->penvy;
                moneytotal=moneytotal+agents[a][b]->money;
                }
            }
        }
 
    //1st of may!
 
        for (a=0;a<32;a++){
            for (b=0;b<32;b++){
                if (replacementrate > (double) rand()/(double) RAND_MAX){
                    //make sure there is dead stuff around it
                    sum=0.0;
                    for (z=0;z<4;z++){
                        if (agents[(a+xz[z])&31][(b+yz[z])&31]->money>0.0){ //only use positive
                            sum=sum+agents[(a+xz[z])&31][(b+yz[z])&31]->money;
                        }
                    }
                    if (sum>0.0){
                        c=0;
                        double rr=(double) rand()/(double) RAND_MAX;
                        while ((agents[(a+xz[c])&31][(b+yz[c])&31]->money/sum)<rr){
                            if (agents[(a+xz[c])&31][(b+yz[c])&31]->money>0.0){ //only use positive
                                rr=rr-(agents[(a+xz[c])&31][(b+yz[c])&31]->money/sum);
                            }
                            c=c+1;
                        }
                        agents[a][b]->nrPointingAtMe--;
                        if(agents[a][b]->nrPointingAtMe==0)
                            delete agents[a][b];
                        agents[a][b]=new tagent;
                        agents[a][b]->inherit(agents[(a+xz[c])&31][(b+yz[c])&31], mutationrate);
                    }
                    else{
                        NumDiscount=NumDiscount+1;
                    }
                }
            }
        }
 
        //if ((god&1023)==1023){
        //  printf("%i %f %f %f %f \n",god,moneytotal/1024.0,punfairtotal/1024.0,penvytotal/1024.0, NumDiscount);
        //  fprintf(f,"%f %f %f %f \n",moneytotal/1024.0,punfairtotal/1024.0,penvytotal/1024.0, NumDiscount);
        //}
    }
    //fclose(f);
    f=fopen(argv[1],"w+t");
    agents[0][0]->saveLOD(f);
    fclose(f);
    return 0;
}
 
    ////////////////////////////////////////////////////////////////////////////////////////
    tagent::tagent(){
        born=god;
        nrPointingAtMe=1;
        ancestor=NULL;
    }
 
    tagent::~tagent(){
        if(ancestor!=NULL){
            ancestor->nrPointingAtMe--;
            if(ancestor->nrPointingAtMe==0)
                delete ancestor;
        }
    }
 
    void tagent::setup(void){
        money=0.0;
        punfair=0.50;
        penvy=0.50;
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
        this->money=0.0;
        ancestor=giver;
        giver->nrPointingAtMe++;
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
    this->money=this->money+payofftable[row][column];
    trader->money=trader->money+payofftable[column][row];
}
 
void tagent::saveLOD(FILE *f){
    if(ancestor!=NULL)
        ancestor->saveLOD(f);
    fprintf(f,"%i   %f  %f  %f\n",this->born,this->punfair,this->penvy,this->money);
}



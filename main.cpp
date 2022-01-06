#include "reqHeaders.h"
ofstream myfile;
#define LEFT_MARGIN 8
#define TOP_MARGIN 10
#define BOTTOM_MARGIN 5
int overflowVertical=0;
int pos;
int currentPointer=0;

int lastRow=0;
int lastCol=0;



/************************/
int windowSize=0;
int winStart=0;
int winEnd=0;
int numItem=0;

/************************/
int commandMode=0;


int headCntSpace=0;
int cntspace=0;

char tmp[256];
char root[256];
char currentDir[256];
char lastDir[256];

string command;
vector<string> pathStack;
int pathStackTopPtr=-1;
vector<string> currDirItem;
std::string sp;

/**********************/

#include"myheaders.h"










int main(){

    
  myfile.open ("example.txt");
    system ("/bin/stty raw");
   setDefaults();

   CLEAR;
   createBorder();
   driver();
   system ("/bin/stty cooked");
   
    


    return 0;
}
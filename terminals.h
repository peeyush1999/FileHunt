#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x));
#define CLEAR std::system("clear");
struct winsize w;


void executeCommand()
{

    std::cout<<"Hello";

}

int keypress()//canonical and non canonical mode
 {
  system ("/bin/stty raw");
  int c;
  system("/bin/stty -echo");
  c = getc(stdin);
  system("/bin/stty echo");
  system ("/bin/stty cooked");
  return c;
}


int getTerminalColumn()
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int getTerminalRow()
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_row);
}

void clearLine(int num)
{
        printf("\033[2K\033[%d;0H",num);
        std::cout<<"#";
        printf("\033[%d;%dH#",num,lastCol);
}

void showCurrentDir()
{
    gotoxy(LEFT_MARGIN,5)
    clearLine(5);
    gotoxy(LEFT_MARGIN,5);
    std::cout<<BROWN_B("Current Directory :  ")<<CYAN(currentDir)<<std::endl;
}
void showHeader()
{
    std::string s="File Explorer For Linux         Developed By:Peeyush Sahu";
    int leftSpace=s.size()-getTerminalColumn();
    leftSpace=abs(leftSpace)/2;
    gotoxy(leftSpace,2);
    std::cout<<GREEN(s);
    //gotoxy(2,2);
    

    if(getcwd(root,sizeof(root))!=NULL)
    {
        gotoxy(LEFT_MARGIN,4);
        std::cout<<BROWN_B("Root Directory :     ")<<CYAN(root);
        gotoxy(LEFT_MARGIN,6);
        std::cout<<RED("Press '")<<YELLOW("q")<<RED("' to exit; ")<<RED(" Arrow Keys to Navigate :")<<YELLOW(" \u2191 , \u2193 , \u2190 , \u2192  ")<<RED("    Home:")<<YELLOW(" h ")<<RED("  Backspace: ")<<YELLOW("\u219E ")<<std::endl;

        showCurrentDir();
    }
    else
    {
        std::cout<<RED("error");
    }
    gotoxy(LEFT_MARGIN,6);
    headCntSpace = abs(getTerminalColumn())/8;
    cntspace = abs(getTerminalColumn())/6.5;
        gotoxy(LEFT_MARGIN,TOP_MARGIN-1); 
       std::cout<<BROWN_B("File Name");
       
       gotoxy(LEFT_MARGIN+cntspace,TOP_MARGIN-1); 
       std::cout<<BROWN_B("File Size");

       gotoxy(LEFT_MARGIN+2*cntspace,TOP_MARGIN-1); 
       std::cout<<BROWN_B("User");

       gotoxy(LEFT_MARGIN+3*cntspace,TOP_MARGIN-1); 
       std::cout<<BROWN_B("Group");

       gotoxy(LEFT_MARGIN+4*cntspace,TOP_MARGIN-1); 
       std::cout<<BROWN_B("Permissions");

       gotoxy(LEFT_MARGIN+5*cntspace,TOP_MARGIN-1); 
       std::cout<<BROWN_B("Last Modified");
}

void setPointer(std::string op)
{
    if(op=="UP")
    {
        /*currentPointer--;
        if(currentPointer<TOP_MARGIN)
            currentPointer=TOP_MARGIN;
        */
        currentPointer--;
        
        if(currentPointer<winStart)
            {
                winStart--;
                winEnd=winStart + windowSize-1;

                if(currentPointer<0)
                {
                currentPointer=0;
                winStart=0;
                winEnd=windowSize;
                }
            }
            
//numItem<<" "<<currentPointer<<" "<<winStart<<" "<<winEnd<<" "<<windowSize;            
        
    }
    else if(op=="DW")
    {
        /*currentPointer++;
        if(currentPointer>getTerminalRow()-BOTTOM_MARGIN)
            currentPointer=getTerminalRow()-BOTTOM_MARGIN;
        */
        currentPointer++;
        
        if(currentPointer>(getTerminalRow()-BOTTOM_MARGIN-TOP_MARGIN-1-1))
        {
            winStart++;
            winEnd = winStart + windowSize-1;
            if(currentPointer>=numItem)
            {
               currentPointer=numItem-1;
               winEnd=numItem;
               winStart=std::max(0,winEnd-(getTerminalRow()-BOTTOM_MARGIN-TOP_MARGIN-1));
                
            }
        }
        if(currentPointer>=numItem)
            {
               currentPointer=numItem-1;
            }

    }

    if(commandMode)
        {
         gotoxy(20,getTerminalRow()-1);   
        }
    else
    {
        gotoxy(getTerminalColumn(),getTerminalRow());
    }


}

void showCommandMode()
{
    gotoxy(2,lastRow-1);  
    clearLine(lastRow-1);
    gotoxy(2,lastRow-1);
    std::cout<<BROWN_B("  Command Mode : ");

    gotoxy(0,lastRow-2);
    std::cout<<"#";
    for(int i=1;i<lastCol-1;i++)
    std::cout<<WHITE("-");
    std::cout<<"#";

    gotoxy(20,getTerminalRow()-1);

}

void createBorder()
{
    int row=getTerminalRow();
    int col=getTerminalColumn();

    if(lastRow==row && lastCol==col)
    {
        return;
    }

    CLEAR;
    lastRow=row;
    lastCol=col;
    //calculating windows size;
    windowSize=row-BOTTOM_MARGIN-TOP_MARGIN;
    
    //CLEAR;
    gotoxy(0,0);
    //Print top row
    for(int i=0;i<col;i++)
        std::cout<<("#");

    //calling show header
    showHeader();

    
    //Print top row
    gotoxy(2,3);
    for(int i=1;i<col-1;i++)
        std::cout<<WHITE("-");

    gotoxy(2,7);
    for(int i=1;i<col-1;i++)
        std::cout<<WHITE("-");

    //print bottom row
    gotoxy(0,row);
    for(int i=0;i<col;i++)
    std::cout<<("#");

    //right border
    for(int i=0;i<row;i++)
    {
        gotoxy(col,i);
        std::cout<<("#");
    }
    
    //left border
    for(int i=0;i<row;i++)
    {
        gotoxy(0,i);
        std::cout<<("#");
    }

    currentPointer=0;
    
}

void updateWindow()
{
    windowSize=getTerminalRow()-BOTTOM_MARGIN-TOP_MARGIN;
    winStart=0;
}

void setDefaults()
{
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); 
   windowSize=getTerminalRow()-BOTTOM_MARGIN-TOP_MARGIN;
   winStart=0;


   getcwd(root,sizeof(root));
   strcpy(currentDir,root);
   strcpy(lastDir,"");
   string tmp(currentDir);
   pathStack.push_back(tmp);
   pathStackTopPtr++;
}
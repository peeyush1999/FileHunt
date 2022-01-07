void normal()
{	int num;

	num=keypress();


	


        /* Clearing Error Panel */
        clearLine(lastRow-1);
        gotoxy(2,lastRow-1);
        

	
        

        if(num==65)//up arrow
        {
           setPointer("UP");
            listDir(currentDir);
        
        }
        else if(num==66)//down arrow
        {
           setPointer("DW");   
            listDir(currentDir);
        
        }
        else if(num==58)// : key
        {
            commandMode=1;
        }
        else if(num==13)//enter key
        {   
            if(currDirItem[currentPointer] == ".")
                {}
            else if(currDirItem[currentPointer]=="..")
            {
                string str(currentDir);
                str = str.substr(0, str.find_last_of("/\\"));
                char *tmp=&str[0];
                strcpy(currentDir,tmp);
                if(strcmp(currentDir,"")==0)
                {
                    strcpy(currentDir,"/");
                }
                currentPointer=0;
                updateWindow();
                updatePathStack(currentDir);

                listDir(currentDir);
                
            }
            else
            {
            string dirName =currDirItem[currentPointer];
            char *tmp=&dirName[0];
            char prevPath[256];
            strcpy(prevPath,currentDir);
            strcat(currentDir,"/");     
            strcat(currentDir,tmp);


            if(stat(currentDir,&checkFile)==0)
            {
                if(checkFile.st_mode & S_IFDIR)//True: Directory
                {
                    updatePathStack(currentDir);
                    currentPointer=0;
                    updateWindow();
                    //myfile<<"Switching to this dir : "<<currentDir<<endl;
                    listDir(currentDir);
                    
                }
                else //if( checkFile.st_mode & S_IFREG )
                {
                    cout<<YELLOW_B("Opening File In Its Default Application!!");
                    
                    char str[1000];
                    strcpy(str,"xdg-open ");
                    strcat(str,"'");
                    strcat(str,currentDir);
                    strcat(str,"'");
                    strcat(str," 2> log.txt");
                    system(str);
                    strcpy(currentDir,prevPath);
                }
            }
            else
            {
                cout<<RED("Error: Check Path!!");
            }
        }      
        }
        else if(num==104)//h 
        {
            strcpy(currentDir,getenv("HOME"));
            //strcpy(currentDir,root);
            updatePathStack(currentDir);
            listDir(currentDir);
        }
        else if(num==68)//left
        {
            pathStackTopPtr--;
            if(pathStackTopPtr<0)
            {
                
                pathStackTopPtr=0;
                
                cout<<RED("Error : No Previous path found!!");
            }
            
            string tmp = pathStack[pathStackTopPtr];
            char *path = &tmp[0];
            currentPointer =0;
            strcpy(currentDir,path);
            listDir(currentDir);


        }
        else if(num==67)//right
        {
            
            pathStackTopPtr++;
            if(pathStackTopPtr>=pathStack.size())
               { 
                 pathStackTopPtr=pathStack.size()-1;
                 cout<<RED("Error : No Next path found!!");
               }
            
            string tmp = pathStack[pathStackTopPtr];
            char *path = &tmp[0];
            currentPointer=0;
            strcpy(currentDir,path);
            listDir(currentDir);
            
        }
        else if(num==127)//BackSpace to exit //one levelup
        {

            string str(currentDir);
            str = str.substr(0, str.find_last_of("/\\"));
            char *tmp=&str[0];
            strcpy(currentDir,tmp);
            if(strcmp(currentDir,"")==0)
            {
                strcpy(currentDir,"/");

            }
            currentPointer=0;
            updateWindow();
            updatePathStack(currentDir);
            listDir(currentDir);
            
            
        }
        else if(num==113 || num==3)//q to exit
        {
            CLEAR;
            gotoxy(0,0);
            exit(0);
        }

}
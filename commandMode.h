


void rename(vector<string> token)
{

    chdir(currentDir);
    string oldName=token[1];
    string newName=token[2];
    
    string homedir = getenv("HOME");

    if(oldName[0]=='~')
        oldName.replace(0,1,homedir);

    if(newName[0]=='~')
        newName.replace(0,1,homedir);

    
    char old_path[256];
    char new_path[256]; 
    realpath(oldName.c_str(), old_path); 
    realpath(newName.c_str(), new_path); 
    
    //strcpy(tmp,resolved_path);

    struct stat one,two; 
    //cout<<old_path<<" "<<new_path<<" ";
    if(stat(old_path,&one)==0)
    {
        if(stat(new_path,&two)!=0)//True: Directory
        {
            
            rename(old_path,new_path);
            cout<<YELLOW("Rename:")<<CYAN(token[1])<<GREEN("->")<<CYAN(token[2]);   
        }
        else
        {
            cout<<RED("Error : Check query for newName!!");
        }
    }
    else
    {
        cout<<RED("Error : Check query for oldName!!");
    }
    
}

void move(vector<string> token)
{
    chdir(currentDir);
    int len = token.size();
    string dest=token[token.size()-1];
    string homedir = getenv("HOME");

    int dcheck=0;
    int fcheck=1;

    if(dest[0]=='~')
        dest.replace(0,1,homedir);


    char dest_path[256];
    
    realpath(dest.c_str(), dest_path); 
    //string finalDest(dest_path);
    

    struct stat one,two; 
    
    if(stat(dest_path,&one)==0 && one.st_mode & S_IFDIR)
    {
        //direcory Exists can move further
        dcheck=1;
    }
    else
    {
        cout<<RED("Error : something wrong with dest directory");
    }


    vector<string> fileList;

    for(int i=1;i<len-1;i++)
    {
        string f=token[i];
        if(f[0]=='~')
            f.replace(0,1,homedir);

        char f_path[256]; 
        realpath(f.c_str(), f_path); 
        
        if(stat(f_path,&two)==0)
        {
            //fileList.push_back(f.substr(0, f.find_last_of("/\\")));
        }
        else
        {
            //Something wrong with file
            cout<<RED("Error: Check File number ")<<RED(i);
            fcheck=0;
            return;
        }

    }

    if(dcheck && fcheck)
    {

        for(int i=1;i<len-1;i++)
        {
            char new_dest_path[256];
            strcpy(new_dest_path,dest_path);
            strcat(new_dest_path,"/");



            string f=token[i];
            if(f[0]=='~')
                f.replace(0,1,homedir);

            char f_path[256]; 
            realpath(f.c_str(), f_path);

            int ls=f.find_last_of("/\\");
            

            string fileName=f.substr(ls+1, f.size()-(ls+1));


            strcat(new_dest_path,fileName.c_str());
            rename(f_path,new_dest_path);
         }

         cout<<YELLOW("All Files Moved Successfully!!");
    }

}








void gotoDir(vector<string> token)
{
    chdir(currentDir);
    string dest=token[1];
    string cd(currentDir);
    string homedir = getenv("HOME");

    if(dest[0]=='~')
        dest.replace(0,1,homedir);

    
    char resolved_path[256]; 
    realpath(dest.c_str(), resolved_path); 
    
    strcpy(tmp,resolved_path);
    

    if(stat(tmp,&checkFile)==0)
    {
        if(checkFile.st_mode & S_IFDIR)//True: Directory
        {
            
            updatePathStack(tmp);
            currentPointer=0;
            updateWindow();
            strcpy(currentDir,tmp);
            currentPointer=0;
            listDir(currentDir);
            gotoxy(4,getTerminalRow()-3);
            cout<<YELLOW("Moved To :")<<CYAN(currentDir);   
        }
        else
        {
            cout<<RED("Path Doesn't Point to Valid Directory");
        }
    }
    else
    {
        cout<<RED("Please Check Your command Again!!");   
    }
}

void createFile(vector<string> token)
{
    chdir(currentDir);
    string dest=token[2];
    string homedir = getenv("HOME");

    if(dest[0]=='~')
        dest.replace(0,1,homedir);

    
    char resolved_path[256]; 
    realpath(dest.c_str(), resolved_path); 
    
    strcpy(tmp,resolved_path);
    
    string cd(tmp);
    cd=cd+'/'+token[1];
    


    if(stat(cd.c_str(),&checkFile)==0)
            {
                if(checkFile.st_mode & S_IFDIR)//True: Directory
                {
                    cout<<RED("Error : Check Command !!");
                }
                else //if( checkFile.st_mode & S_IFREG )
                {
                    cout<<RED("Error : File Already Exists!!");
                }
                return;
            }

    fstream file;
    file.open(cd,ios::out);

    if(!file)
    {
        cout<<RED("Error In Creating File!!");
    }
    else
    {
        cout<<YELLOW("File Created Successfully : ")<<CYAN(cd)<<" ";;
    }
    file.close();
}

void makeDir(vector<string> token)
{
    chdir(currentDir);
    string dest=token[2];
    string homedir = getenv("HOME");

    if(dest[0]=='~')
        dest.replace(0,1,homedir);

    
    char resolved_path[256]; 
    realpath(dest.c_str(), resolved_path); 
    
    strcpy(tmp,resolved_path);
    
    string cd(tmp);
    cd=cd+'/'+token[1];
    
    if(stat(cd.c_str(),&checkFile)==0)
    {
        if(checkFile.st_mode & S_IFDIR)//True: Directory
        {
            cout<<RED("Error: Directory Already Exists");
        }
        else if( checkFile.st_mode & S_IFREG )
        {
            cout<<RED("Error: File with same name Exists");   
        }
        else
        {
            cout<<RED("Unable to process your cmd");
        }
    }
    else
    {
        if(!mkdir(cd.c_str(),0777))
        {
            cout<<YELLOW("Directory successfully created : ")<<CYAN(token[1]);
        }
        else
        {
            cout<<RED("Please check your command again");   
        }
    }
    
}
void deleteFile(vector<string> token)
{
    chdir(currentDir);
    string dest=token[2];
    string homedir = getenv("HOME");

    if(dest[0]=='~')
        dest.replace(0,1,homedir);

    
    char resolved_path[256]; 
    realpath(dest.c_str(), resolved_path); 
    
    strcpy(tmp,resolved_path);
    
    string cd(tmp);
    cd=cd+'/'+token[1];
    
    if(stat(cd.c_str(),&checkFile)==0)
    {
        if(checkFile.st_mode & S_IFDIR)//True: Directory
        {
            cout<<RED("Error: Given represents Direcotry!!,");
        }
        else
        {
            remove(cd.c_str());
            cout<<YELLOW("File removed successfully !!");
        }
    }
    else
    {
         cout<<RED("Error: Please check your command again");   
    }
}

void deleteHelper(string path)
{
    chdir(currentDir);
    int n;
    struct dirent **list=NULL;
    n = scandir(path.c_str(), &list, NULL, alphasort);
    for(int i=2;i<n;i++)
    {
        string tt(list[i]->d_name);
        tt = path+"/"+tt;
        lstat(tt.c_str(), &checkFile);
        
        if(checkFile.st_mode & S_IFDIR)//True: Directory
        {
            
            deleteHelper(path+"/"+list[i]->d_name);
            myfile<<(path+"/"+list[i]->d_name)<<"== "<<endl;
            rmdir(tt.c_str());
        }
        else
        {
            myfile<<"---->"<<(path+"/"+list[i]->d_name)<<" #"<<endl;
            remove(tt.c_str());
        }
    
            
    }

}
void deleteDir(vector<string> token)
{
    chdir(currentDir);
    string dest=token[2];
    string homedir = getenv("HOME");



    if(dest[0]=='~')
        dest.replace(0,1,homedir);

    
    char resolved_path[256]; 

    if(dest[0]=='.' && dest.size()==1)
    {
        string tmp(currentDir);
        dest=tmp;
    }

    realpath(dest.c_str(), resolved_path); 
    
    //cout<<"RP:"<<resolved_path<<" ";
    strcpy(tmp,resolved_path);
    
    string cd(tmp);
    //cd = cd.substr(0, cd.find_last_of("/\\"));
    cd=cd+'/'+token[1];
    myfile<<"Deleting this path : "<<cd<<" "<<endl;;
    if(stat(cd.c_str(),&checkFile)==0)
    {
        if(checkFile.st_mode & S_IFDIR)//True: Directory
        {
            
            myfile<<"starting from : "<<cd<<endl;
            deleteHelper(cd);
            rmdir(cd.c_str());

            cout<<YELLOW("Successfully Removed the Direcotry");
        }
        else
        {
            cout<<RED("Error: Given Name Belongs to file!!");
        }
    }
    else
    {
         cout<<RED("Error: Please check your command again");   
    }
}


void copyHelper(string path,string newPath)
{
    chdir(currentDir);
    int n;
    struct dirent **list=NULL;
    myfile<<" Scanning : "<<path<<endl;
    n = scandir(path.c_str(), &list, NULL, alphasort);
    for(int i=2;i<n;i++)
    {
        string tt(list[i]->d_name);
        string np=newPath;
        if(np[np.size()-1]=='/')
            np.pop_back();

        np=np+"/"+tt;
        int flag=0;

        tt = path+"/"+tt;
        lstat(tt.c_str(), &checkFile);
        
        

        if(checkFile.st_mode & S_IFDIR)//True: Directory
        {

            myfile<<"@@@@@ "<<(tt)<<endl<<np<<endl;
            myfile <<endl<<endl;
        
           if(!mkdir(np.c_str(),0000))
           {
                if(!chmod(np.c_str(), checkFile.st_mode))
                {
                    myfile<<"updated permissions:"<<endl;
                    flag=1;
                }
           }
           else
           {
            myfile<<" \n Errro: mkdir \n";
           }

            if(flag)
                copyHelper(tt,np);
            
            
        }
        else
        {            
            string line;
            ifstream ini_file {tt};
            ofstream out_file {np};

            myfile<<"\n------\n";
            myfile<<tt<<"  \n "<<np;
            myfile<<"\n------\n";
            if(ini_file && out_file)
            {
         
                while(getline(ini_file,line))
                {
                    out_file << line<<'\n';
                }
            } else {
                //Something went wrong
                printf("Cannot read File");
            }
            ini_file.close();
            out_file.close();

            if(!chmod(np.c_str(), checkFile.st_mode))
            {
                myfile<<"updated permissions:"<<endl;
                flag=1;
            }
            
            myfile<<"---->"<<(path+"/"+list[i]->d_name)<<"==="<<np<<endl;
        }
    
            
    }

}
void copyDir(vector<string> token)
{
    chdir(currentDir);
    int len = token.size();
    string dest=token[token.size()-1];
    string homedir = getenv("HOME");

    int dcheck=0;
    int fcheck=1;

    if(dest[0]=='~')
        dest.replace(0,1,homedir);


    char dest_path[256];
    
    realpath(dest.c_str(), dest_path); 
    string finalDest(dest_path);
    
    //cout<<dest_path<<" ";
    struct stat one,two; 
    
    if(stat(dest_path,&one)==0 && one.st_mode & S_IFDIR)
    {
        //direcory Exists can move further
        dcheck=1;
    }
    else
    {
        cout<<RED("Error : something wrong with dest directory");
    }


    vector<string> fileList;

    for(int i=1;i<len-1;i++)
    {
        string f=token[i];
        if(f[0]=='~')
            f.replace(0,1,homedir);

        char f_path[256]; 
        realpath(f.c_str(), f_path); 
        myfile<<"@@@@@@@@@@@ copy this file ----   "<<f<<endl;
        myfile<<"@@@@@@@@@@@ copy this file    "<<f_path<<endl;
        myfile<<stat(f_path,&two)<<endl;
        if(stat(f_path,&two)==0)
        {
            //fileList.push_back(f.substr(0, f.find_last_of("/\\")));
        }
        else
        {
            //Something wrong with file
            cout<<RED("Error: Check File number ")<<RED(i);
            fcheck=0;
            return;
        }

    }

    if(dcheck && fcheck)
    {
        int flagg=0;
        for(int i=1;i<len-1;i++)
        {
            char new_dest_path[256];
            strcpy(new_dest_path,dest_path);
            strcat(new_dest_path,"/");



            string f=token[i];
            if(f[0]=='~')
                f.replace(0,1,homedir);

            

            char f_path[256]; 
            realpath(f.c_str(), f_path);


             myfile<<"@@@@@@@@@@@ pasting here    "<<new_dest_path<<endl;
             myfile<<"@@@@@@@@@@@ fpath    "<<f_path<<endl;



            int ls=f.find_last_of("/\\");
            

            string fileName=f.substr(ls+1, f.size()-(ls+1));
             myfile<<"@@@@@@@@@@@ file  name here    "<<fileName<<endl;

            
            


             if(stat(f_path,&one)==0 )
                {
                   if(one.st_mode & S_IFDIR)
                   {
                        strcat(new_dest_path,fileName.c_str());
                        strcat(new_dest_path,"/");
                        myfile<<"@@@@@@@@@@@ final Dest path here    "<<new_dest_path<<endl;

                       string aa(f_path);
                       string bb(new_dest_path);
                       
                       int mkdirResult=mkdir(new_dest_path,0000) ;
                       myfile<<"mkdir val "<<mkdirResult<<endl;
                       if(!mkdirResult)
                       {
                            if(!chmod(new_dest_path, one.st_mode))
                            {
                                myfile<<"Successfully updated the permissions"<<endl;
                            }
                       }
                       else
                       {
                             myfile<<"\ncp___Error: unable to make dir "<<new_dest_path<<endl;
                       }



                       copyHelper(aa,bb);
                       flagg=1;
                 }
                else
                {

                     strcat(new_dest_path,fileName.c_str());
                     
                     if(stat(new_dest_path,&one)==0 )
                     {
                        cout<<RED("File With same name already exists!!");
                        return;
                     }

                     string aa(f_path);
                     string bb(new_dest_path);
                     //cout<<new_dest_path;
                     string line;
                     ifstream ini_file {aa};
                     ofstream out_file {bb};
                     myfile<<"origin: "<<f_path<<endl;
                     myfile<<"destin: "<<new_dest_path<<endl;
                 
                    if(ini_file && out_file)
                    {
                 
                        while(getline(ini_file,line))
                        {
                            out_file << line<<'\n';
                        }

                        flagg=1;
                    } else {
                        //Something went wrong
                        if(!ini_file)
                        {
                            cout<<RED("Check Source file name");
                        }
                        if(!out_file)
                        {
                            cout<<RED("Check Directory name");
                        }
                    }
                    ini_file.close();
                    out_file.close();

                   // chmod(bb.c_str(), 0000);
                    chmod(bb.c_str(), one.st_mode );//& ~S_IFMT
                
                //    cout<<RED("File already Exists");
                  //  return;
                }

            }
                   
                    
                

            
            
         }

         if(flagg==1)
         {
            cout<<YELLOW("All Files Copied Successfully!!");
         }
         
    }
}

int globSearch=0;

void searchHelper(string path,string name)
{
    struct dirent **namelist=NULL;
    //cout<<path;
    path=path+"/";
    int n = scandir(path.c_str(), &namelist, NULL, alphasort);

    myfile<<"Search -: "<<path<<endl;

    if (n == -1) 
    {
       cout<<RED("scandir : ")<<RED("EXIT_FAILURE");
    }
   for(int i=0;i<n;i++)
   {
        if(!strcmp(namelist[i]->d_name,"."))
            continue;
        if(!strcmp(namelist[i]->d_name,".."))
            continue;

        char resolved_path[256]; 
        realpath(path.c_str(), resolved_path); 
        strcat(resolved_path,"/");
        strcat(resolved_path,namelist[i]->d_name);

        string tmp(namelist[i]->d_name);

        myfile<<"------>"<<tmp<<endl; 

        if(!strcmp(namelist[i]->d_name,name.c_str()))
            {
                //return true;
                globSearch=1;
            }

        
        if(stat(resolved_path, &checkFile)==0)
        {
            if(S_ISDIR(checkFile.st_mode))//True: Directory
                    {
                        //recursively iterating over directory
                        
                        //path = path + namelist[i]->d_name;
                        //myfile<<endl<<"------"<<S_ISDIR(checkFile.st_mode)<<"--------------------"<<path<<endl<<endl;
                        //return searchHelper(path, name);
                        searchHelper(path + namelist[i]->d_name, name);

                    }
          

            
        }
        else
        {
           // myfile<<"INvalid input path"<<endl;
        }
               
         

   }
   free(namelist);
   //return false;
}
        
void search(vector<string> token)
{
    globSearch=0;
    string name=token[1];
    string mpath(currentDir);
    searchHelper(mpath,name);
    if(globSearch)
    {
        cout<<YELLOW("True");
    }
    else
    {
        cout<<RED("False");
    }

}



void parseCommand(string cmd)
{
    vector<string> token;
    string s;
    for(char x:cmd)
    {
        if(x==' ')
        {
            if(!s.empty())
                token.push_back(s);
            s.clear();
        }
        else
        {
            s=s+x;
        }
    }
    if(!s.empty())
        token.push_back(s);

	
	gotoxy(4,getTerminalRow()-3);
    clearLine(getTerminalRow()-3);
    gotoxy(4,getTerminalRow()-3);
    
    if(token.size()==0)
        return;
    if(token[0]=="create_dir")
    {
        makeDir(token);
    }
    else if(token[0]=="create_file")
    {
        createFile(token);
    }
    else if(token[0]=="goto")
    {
        gotoDir(token);
    }
    else if(token[0]=="delete_dir")
    {
        deleteDir(token);
    }
    else if(token[0]=="delete_file")
    {
        deleteFile(token);
    }
    else if(token[0]=="copy")
    {
        copyDir(token);
    }
    else if(token[0]=="move")
    {
        move(token);
    }
    else if(token[0]=="rename")
    {
        rename(token);
    }
    else if(token[0]=="search")
    {
        search(token);
    }

}

void commandM()
{
	int num=0;
	command="";
	
	while(true)
	{	
		showCommandMode();
		cout<<command;
        num=keypress();

        if(num==27)
        {
            num=keypress();

            if(num==91)
                {
                    num=keypress();
                    if(num==65)//up
                    {
                        num=1235;
                    }
                    else if(num==66)//down
                    {
                        num=1236;
                    }
                    else if(num==67)//right
                    {
                        num=1237;
                    }
                    else if(num==68)//left
                    {
                        num=1238;
                    }
                }
            else
            {
                commandMode=0;
            }
        }
       
        

        
        if(num==127)//backspace
        {
        	if(command.size()>0)
        		command.pop_back();
        }

        else if(num==13)//enter Key
        {
        	parseCommand(command);
        	command.clear();
        }
        else if(num==27)
        {
        	commandMode=0;

        	break;
        }
        else  if(num==1235)//up arrow
        {
           //setPointer("UP");
            //listDir(currentDir);
            //cout<<RED("UP");
        
        }
        else if(num==1236)//down arrow
        {
         //  setPointer("DW");   
           // listDir(currentDir);
        
        }
        else if(num==1237)//right
        {

        }
        else if(num==1238)//left
        {

        }
        else
        {
        	char ch;
        	ch=num;
        	command.push_back(ch);
        	
        }

        
        
   }

gotoxy(4,getTerminalRow()-3);
clearLine(getTerminalRow()-3);
gotoxy(4,getTerminalRow()-3);
   gotoxy(0,lastRow-2);
   std::cout<<"#";
   for(int i=1;i<lastCol-1;i++)
   std::cout<<WHITE(" ");
   std::cout<<"#";
   gotoxy(0,lastRow-1);
   std::cout<<"#";
   for(int i=1;i<lastCol-1;i++)
   std::cout<<WHITE(" ");
   std::cout<<"#";

   gotoxy(getTerminalColumn(),getTerminalRow());

}

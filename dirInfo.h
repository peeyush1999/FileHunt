struct stat statbuf,checkFile;  
struct dirent **namelist=NULL;


string oneLevelUp(string path)
{
    string str(currentDir);
    str = str.substr(0, str.find_last_of("/\\"));
    if(str=="")
    {
        str="/";
    }

    return str;
    
}

void updatePathStack(char *path)
{
    string s(path);

    if(pathStackTopPtr==pathStack.size()-1)
    {
        pathStack.push_back(s);   
    }
    else
    {
        pathStack[pathStackTopPtr+1]=s;
        
   }
   pathStackTopPtr++;
}

string getUsername(uid_t u)
{
    struct passwd *pw = getpwuid(u);
    if(pw==0)
        return "";

    string uname(pw->pw_name);
    return uname;
}


string getGrpname(gid_t g)
{
    struct group *gr = getgrgid(g);
    if(gr==0)
        return "";

    string gname(gr->gr_name);
    return gname;
}


string getTime(time_t t)
{
    struct tm *ts;
    char       buf[80];
    ts = localtime(&t);
    strftime(buf, sizeof(buf), "%a %b %d, %Y %H:%M:%S %Z", ts);
    string time(buf);
    return time; 
}

string FormatBytes(long long bytes)
{
    char str[32];
    const char *sizes[5] = { "B", "KB", "MB", "GB", "TB" };
 
    int i;
    double dblByte = bytes;
    for (i = 0; i < 5 && bytes >= 1024; i++, bytes /= 1024)
        dblByte = bytes / 1024.0;
 
    sprintf(str, "%.2f", dblByte);
 
    strcat(strcat(str, " "), sizes[i]);
    string s(str);
    return s;
}

string getPermissions(mode_t perm)
{
    char modeval[9];
    modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
    modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
    modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
    modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
    modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
    modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
    modeval[6] = (perm & S_IROTH) ? 'r' : '-';
    modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
    modeval[8] = (perm & S_IXOTH) ? 'x' : '-';

    string ans;
    ans+=modeval[0];
    ans+=modeval[1];
    ans+=modeval[2];
    ans+=modeval[3];
    ans+=modeval[4];
    ans+=modeval[5];
    ans+=modeval[6];
    ans+=modeval[7];
    ans+=modeval[8];

    return ans;
}


void listDir(char *path)
{   
	int n;
    showCurrentDir();

    if(strcmp(path,"")==0)
    {
        strcpy(currentDir,"/");
        strcpy(path,"/");
    }

    n = scandir(path, &namelist, NULL, alphasort);


	if(strcmp(path,lastDir)==0 && (currentPointer>winStart &&  currentPointer<min(numItem,(winStart + windowSize-1))-1))
	{

		for(int i=TOP_MARGIN;i<getTerminalRow()-BOTTOM_MARGIN;i++)
	    {   
	        gotoxy(4,i);
	        printf("    ");
	    }
	    gotoxy(4,currentPointer-winStart+TOP_MARGIN);
    	std::cout<<RED(">->");
    	if(!commandMode) 
	    {
	    	gotoxy(2,getTerminalRow()-1);
	    }
	    else
	    {
	     	gotoxy(20,getTerminalRow()-1);   
	    }
     //std::cout<<numItem<<" "<<currentPointer<<" "<<winStart<<" "<<(winStart + windowSize-1)<<" "<<windowSize<<" "<<(winStart + windowSize-2);


		return;

	}

	strcpy(lastDir,path);
    for(int i=TOP_MARGIN;i<getTerminalRow()-BOTTOM_MARGIN;i++)
    {   
        gotoxy(LEFT_MARGIN,i)
        printf("\033[2K\033[%d;0H",i);
        cout<<"#";
        printf("\033[%d;%dH#",i,lastCol);
    }
    gotoxy(4,currentPointer-winStart+TOP_MARGIN);
    std::cout<<RED(">->");


    currDirItem.clear();
    myfile<<"Switched to this dir -: "<<path<<endl;

    numItem=n;
    if (n == -1) 
    {
       //perror("scandir");
       //exit(EXIT_FAILURE);
       cout<<RED("scandir : ")<<RED("EXIT_FAILURE");
       return;
    }

   int line=TOP_MARGIN;
   gotoxy(LEFT_MARGIN,line);

   for(int i=0;i<n;i++)
   {
   		string tmp(namelist[i]->d_name);
       	stat(namelist[i]->d_name, &statbuf);
       	currDirItem.push_back(tmp);

   }

   for(int i=winStart;i<min((winStart + windowSize-1),n);i++) {
    

       gotoxy(LEFT_MARGIN,line);
       line++;
       //string tmp(namelist[i]->d_name);
        char f_path[256];
        strcpy(f_path,currentDir);
        strcat(f_path,"/");
        strcat(f_path,namelist[i]->d_name);
        struct stat ptr;

       if(stat(f_path, &ptr)==0)
       {
        //myfile<<f_path<<" "<<getPermissions(ptr.st_mode)<<endl;
       }
       else
       {
       // myfile<<f_path<<" "<<"failed"<<endl;        
       }

       //currDirItem.push_back(tmp);
       
       gotoxy(LEFT_MARGIN,TOP_MARGIN+i-winStart); 
       //cout<<CYAN(namelist[i]->d_name);
       string nname(namelist[i]->d_name);
       if(nname.size()>20)
        cout<<CYAN(nname.substr(0,20)+"...");
       else
        cout<<CYAN(nname);

       gotoxy(LEFT_MARGIN+cntspace,TOP_MARGIN+i-winStart); 
       cout<<FormatBytes(ptr.st_size);

       gotoxy(LEFT_MARGIN+2*cntspace,TOP_MARGIN+i-winStart); 
       cout<<getUsername(ptr.st_uid);

       gotoxy(LEFT_MARGIN+3*cntspace,TOP_MARGIN+i-winStart); 
       cout<<getGrpname(ptr.st_gid);

       gotoxy(LEFT_MARGIN+4*cntspace,TOP_MARGIN+i-winStart); 
       cout<<CYAN(getPermissions(ptr.st_mode));
       //string perm=getPermissions(ptr.st_mode);
       //cout<<YELLOW(perm.substr(0,3))<<BLUE(perm.substr(3,3))<<CYAN(perm.substr(3,3));

       gotoxy(LEFT_MARGIN+5*cntspace,TOP_MARGIN+i-winStart); 
       cout<<getTime(ptr.st_mtime);

       free(namelist[i]);
   }
   //cout<<commandMode<<" "<<num<<" "<<pathStackTopPtr;
   free(namelist);


   	//setting pointer to last location where error and banner can be shown
    if(!commandMode) 
    {
    	gotoxy(2,getTerminalRow()-1);
    }
    else
    {
     	gotoxy(20,getTerminalRow()-1);   
    }
    //std::cout<<numItem<<" "<<currentPointer<<" "<<winStart<<" "<<(winStart + windowSize-1)<<" "<<windowSize;
}








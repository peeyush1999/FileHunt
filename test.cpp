#include<stdio.h>
#include <sys/ioctl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pwd.h>
#include <grp.h>
#include <bits/stdc++.h>
#include <termios.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "mycolors.h"
#include <bits/stdc++.h>
using namespace std;
int main(void) {
    

    system ("/bin/stty raw min 0 time 2");
    system ("/bin/stty -echo");
    while (1) {
        int c;
        
        c = getc(stdin);

        if(c==-1)
        {
          continue;
        }




        
        printf("%c", c);
        printf("\n------------\n");
    }
system ("/bin/stty echo");
  system ("/bin/stty cooked");
    return 0;
}

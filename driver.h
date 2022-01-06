
void driver()
{
    
    while(true)
    {
        //CLEAR;

        createBorder();
        listDir(currentDir);
        
        if(commandMode)
        {
            showCommandMode();
            commandM();
        }
        else
        {
            normal();

        }
        
        
        
              
    }    

}
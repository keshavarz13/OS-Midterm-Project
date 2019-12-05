
// C program to illustrate 
// command line arguments 

#include "types.h"
#include "user.h"
  
int main(int argc,char* argv[]) 
{ 
    if(argc>=2) 
    {   
       
        int n  = atoi(argv[1]) ;  
        
        getppid(); 
        getppid(); 
        getppid(); 
        getppid(); 
        printf(1,"result : %d\n",getCount(n));
    } 
    
    

    return 0; 
} 



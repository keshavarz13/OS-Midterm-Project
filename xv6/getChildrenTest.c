#include "types.h"
#include "user.h"

int main(void) {
    int parent = getpid();
    int child1 = fork();
    int child2 = fork(); 

    if(child1 > 0 && child2 > 0) {
        printf("p  : pid : %d , ppid : %d , getchildren : %d " , getpid() ,getppid() , getChildren(getppid())); 
        wait();
        wait();
        
    } else if (child1 > 0 && child2 < 0){
        printf("lc  : pid : %d , ppid : %d , getchildren : %d " , getpid() ,getppid() , getChildren(getppid())); 


    } else if (child1 < 0 && child2 > 0){
        printf("rc  : pid : %d , ppid : %d , getchildren : %d " , getpid() ,getppid() , getChildren(getppid())); 
        wait(); 

    } else {
        printf("rrc :pid : %d , ppid : %d , getchildren : %d " , getpid() ,getppid() , getChildren(getppid())); 
    }
    exit();
}

#include "types.h"
#include "user.h"

int main(void) {
    int child1 = fork();
    int child2 = fork(); 

    if(child1 > 0 && child2 > 0) {
        sleep(10);
        printf(1,"p  : pid : %d , ppid : %d , getchildren : %d \n" , getpid() ,getppid() , getChildren(getppid())); 
        wait();
        wait();
        
    } else if (child1 > 0 && child2 == 0){
        sleep(30);
        printf(1,"lc  : pid : %d , ppid : %d , getchildren : %d \n" , getpid() ,getppid() , getChildren(getppid())); 
        

    } else if (child1 == 0 && child2 > 0){
        sleep(70);
        printf(1,"rc  : pid : %d , ppid : %d , getchildren : %d \n" , getpid() ,getppid() , getChildren(getppid())); 
        wait(); 

    } else {
        sleep(100);
        printf(1,"rrc :pid : %d , ppid : %d , getchildren : %d \n" , getpid() ,getppid() , getChildren(getppid())); 
    

    }
    exit();
}

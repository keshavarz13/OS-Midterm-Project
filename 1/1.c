// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main(int argc, char *argv[])
// {
//     int fd[2];
//     int fd2 [2];
//     int val = 0;

//     // create pipe descriptors
//     pipe(fd);

//     // fork() returns 0 for child process, child-pid for parent process.
//     if (fork() != 0)
//     {
//         // parent: writing only, so close read-descriptor.
//         close(fd[0]);

//         // send the value on the write-descriptor.
//         val = 100;
//         write(fd[1], &val, sizeof(val));
//         printf("I am parent : \n I send value: %d\n", val);

//         // close the write descriptor
//         close(fd[1]);
//     }
//     else
//     {   // child: reading only, so close the write-descriptor
//         close(fd[1]);

//         // now read the data (will block)
//         read(fd[0], &val, sizeof(val));
//         printf("I am child \n I receive value: %d\n", val);

//         // close the read-descriptor
//         close(fd[0]);
//     }
//     return 0;
// }


//--------------------------------
// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

char * toArray(int number)
{
    int n = log10(number) + 1;
    int i;
    char *numberArray = calloc(n, sizeof(char));
    for ( i = 0; i < n; ++i, number /= 10 )
    {
        numberArray[i] = number % 10;
    }
    return numberArray;
}

char concat(char a[], char b[]){
   int lena = strlen(a);
   int lenb = strlen(b);
   char con[lena+lenb];
   con[0] = a;
   con[lena] = b;
   return con;
}

  
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  
    char fixed_str[] = "forgeeks.org"; 
    char input_str[100]; 
    pid_t p; 
    int val; 

    scanf("Enter value : %d" , &val); 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100]; 
  
        close(fd1[0]);  // Close reading end of first pipe 
  
       // send the value on the write-descriptor.
        write(fd1[1], &val, sizeof(val));
        printf("I am parent : \n I send value: %d\n", val);
        close(fd1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        close(fd2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close 
        // reading end. 
        read(fd2[0], concat_str, 100); 
        printf("Concatenated string %s\n", concat_str); 
        close(fd2[0]); 
    } 
  
    // child process 
    else
    { 
        close(fd1[1]);  // Close writing end of first pipe 
  

        // now read the data (will block)
        read(fd1[0], &val, sizeof(val));
        printf("I am child \n I receive value: %d\n", val);
        int i = 0 ; 
        int sum = 0 ; 
        int hold = val ; 
        int digit = 0 ; 

        while (hold > 0 ){
            digit = hold % 10 ; 
            if (hold % 2 == 0 )
                sum += digit; 
            hold /= 0 ; 
        }  


        char con1 = concat(toArray(val) , fixed_str ); 
        char result = concat(con1 , toArray(sum)); 
  
        concat_str[k] = '\0';   // string ends with '\0' 
  
        // Close both reading ends 
        close(fd1[0]); 
        close(fd2[0]); 
  
        // Write concatenated string and close writing end 
        write(fd2[1], concat_str, strlen(concat_str)+1); 
        close(fd2[1]); 
  
        exit(0); 
    } 
} 
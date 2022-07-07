#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
        int sum=0, pdt=1, PID, i;
        if ((PID=fork())==0){    
                printf("child\n"); 
        } 
        if (PID <0) {     
                printf("problem creating a process \n"); 
        } 
        if (PID >0) {     
                        printf("parent\n"); 
        }
}

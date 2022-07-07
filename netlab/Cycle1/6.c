#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void main(){
	int n,sum=0,prd=1,PID,i;


	if((PID=fork())==0){
		printf("child process with PID %d\n",PID);
	}
	sum=0;
	if(PID<0){
		printf("Problem creating process\n");
	}
	
	else if(PID>0){
		
		printf("parent with PID %d\n",PID);

	}

}

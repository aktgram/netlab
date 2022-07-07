#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void main(){
	int n,sum=0,PID,i;
	printf("Enter number of integers\n");
	scanf("%d",&n);
	int A[n];
	for (int i=0;i<n;i++){
		scanf("%d",&A[i]);
	}
	if((PID=fork())==0){
		for(int i=0;i<n;i++){
			if(A[i]%2==1)
				sum+=A[i];
		}
		printf("Odd Sum of child process with PID %d is %d\n",PID,sum);
	}
	sum=0;
	if(PID<0){
		printf("Problem creating process\n");
	}
	else if(PID>0){
		for(i=0;i<n;i++){
			if(A[i]%2==0)
				sum+=A[i];
		}
		printf("Even Sum of parent with PID %d is %d\n",PID,sum);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

void main() {
	int sum=0, pdt=1, PID, i, n;
	printf("Enter a number : "); 
	scanf("%d",&n);
	PID = fork();
	if (PID <0) {
		printf("problem creating a process \n"); 
	} 
	if (PID >0) {
		int flag = 0; 
		printf("Parent Process\n");
		for (i=2;i<=sqrt(n);i++){
			if(n % i == 0){
				flag = 1;
				break;
			}
		}
		if(flag == 1)
			printf("%d is not a prime number\n",n);
		else 
			printf("%d is a prime number\n",n);
	}
}

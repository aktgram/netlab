#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void main(){
	int n,sum=0,prd=1,PID,i;
	char str[30];
	printf("Enter string : ");
	scanf("%[^\n]",str);

	if((PID=fork())==0){
		printf("String in upper case is :");
		for(int i=0;i<strlen(str);i++){
			printf("%c",toupper(str[i]));
		}
		printf("\n");
	}
	if(PID<0){
		printf("Problem creating process\n");
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

void main() {
  char *ip = "127.0.0.1";
  int port = 5543;

  int sockfd,i;
  struct sockaddr_in addr;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd<0) {
    perror("[-]Socket error");
    exit(1);
  }

  memset(&addr,'\0',sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);


  for(i=0;i<5;i++)
  {
    bzero(buffer,1024);
    sprintf(buffer,"%d",i);
    printf("(Client) Data to server : %s",buffer);
    sendto(sockfd,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));

    bzero(buffer,1024);
    addr_size = sizeof(addr);
    recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);

    printf("(Client) Acknowledgment from server: %s\n",buffer);

  }
}



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#define SERV_PORT 5777
main(int argc,char *argv)
{
 	char ch,to[30],from[30],sub[30],msg[150],filename[30],text[150]="";
 	int sockfd;
 	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
   	servaddr.sin_family=AF_INET;
    	servaddr.sin_port=ntohs(SERV_PORT);
    	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("\n From: ");
	gets(from);
	printf(" To: ");
	gets(to);
	printf(" Subject: ");
	gets(sub);
	printf(" Enter Message: ");
	gets(msg);
	printf(" Attach a file (y) or (n) : ");
	scanf("%c",&ch);
	if(ch=='y')
	{
		printf("\nEnter the file name : ");
		scanf("%s",filename);
	}
	strcat(text,"FROM : ");
	strcat(text,from);
	strcat(text,"\nTO : ");
	strcat(text,to);
	strcat(text,msg);
	strcat(text,"\nSUBJECT : ");
	strcat(text,sub);
	strcat(text,"\nMESSAGE : ");
	if(ch=='y')
	{
		strcat(text,"\nATTACHMENT -->");
		strcat(text,filename);
	}
	else
		strcat(text,"\nATTACHMENT -->NONE");
	strcat(text," \0"); 
	write(sockfd,text,strlen(text));
	exit(0);
}

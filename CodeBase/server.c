#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#define MAXLINE 150
#define SERV_PORT 5777
int main(int argc,char *argv)
{
	int i,j,f; ssize_t n;
	char s[100],line[MAXLINE],revline[MAXLINE], filename[30]="";
	int listenfd,connfd,clilen;
	struct sockaddr_in servaddr,cliaddr;
	listenfd=socket(AF_INET,SOCK_STREAM,0); bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);
	bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(listenfd,1);
	for( ; ; )
		{
		strcpy(filename,"");
		i=0;
		clilen=sizeof(cliaddr);
		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		printf("\nConnected to client.");
		printf("\nE-mail from client\n");
		while(1)
		{
			if((n=read(connfd,line,MAXLINE))==0)
			break;
  			line[n-1]='\0';
			puts(line);
		}i=0;
		for(f=0; line[f]!='>'; f++);
		f++;
		for(;line[f]!='\0';f++)
			filename[i++] = line[f];
		if(filename[0]!='N')
		{
			FILE *fp;
			printf("CONTENTS : ");
			fp=fopen(filename,"r");
			while(fgets(s,80,fp)!=NULL)
			{
				printf("%s",s);
			} 
		} 
	}
	return 0;
}
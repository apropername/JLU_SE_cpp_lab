#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<cstdio>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

int main(void){
	int cfd=socket(AF_INET,SOCK_STREAM,0);
	if(cfd==-1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	const unsigned int SEVERZ_PORT=6666;
       	saddr.sin_port=htons(SEVERZ_PORT);
       	inet_pton(AF_INET,"192.168.200.128",&saddr.sin_addr.s_addr);
       	int ret=connect(cfd,(struct sockaddr *)&saddr,sizeof(saddr)); if(ret == -1){
		perror("connect");
		return -1;
	}
	int number=1;
	while(1){
		char buff[1024];
		sprintf(buff,"hello*%d...\n",number++);
		send(cfd,buff,strlen(buff)+1,0);
		memset(buff,0,sizeof(buff));
		int m=recv(cfd,buff,sizeof(buff),0);
		if(m>0){
			cout<<"sever says:"<<buff;
		}
		else if(m==0){
			cout<<"sever disconnects...";
			break;
		}
		else{
			perror("recv");
			break;
		}
		sleep(1);
	}
	close(cfd);
	return 0;
}

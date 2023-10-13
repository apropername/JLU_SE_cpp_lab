#include"Msign.h"
#include"net.h"
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<cstdio>
using namespace std;

int client_start(){
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
       	int ret=connect(cfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(ret == -1){
		perror("connect");
		return -1;
	}
	return cfd;
}


#include"Msign.h"
#include<string>
#include"net.h"
#include<pthread.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<cstdio>
using namespace std;
class sockinfo{
	struct sockaddr_in caddr;
	int fd;
public:
	sockinfo();
	bool isfree();
	struct sockaddr * waddr(){
		return (struct sockaddr*)&caddr;
	}
	void wsock(int);
	in_addr_t* getaddr(){
		return &caddr.sin_addr.s_addr;
	}
	int getport(){
		return caddr.sin_port;
	}
	int getfd(){
		return fd;
	}
};
void sockinfo::wsock(int cfd){
	fd=cfd;
	return;
}
bool sockinfo::isfree(){
	if(fd==-1)
		return true;
	else
		return false;
}
sockinfo::sockinfo(){
	caddr.sin_family=0;
	caddr.sin_port=0;
	caddr.sin_addr.s_addr=0;
	fd=-1;
}
void* working(void*);
const unsigned int SEVERZ_PORT=6666,LISTEN_MAX=30;
vector<sockinfo> infos(LISTEN_MAX*3);
int main(void){
	//1
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1){
		perror("socket");
		return -1;
	}
	//2
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET; saddr.sin_port=htons(SEVERZ_PORT);
       	saddr.sin_addr.s_addr=INADDR_ANY;
       	int ret=bind(fd,(struct sockaddr *)&saddr,sizeof(saddr)); 
	if(ret == -1){
		perror("bind");
		return -1;
	}
	//3
	ret=listen(fd,LISTEN_MAX);
	if(ret == -1){
		perror("listen");
		return -1;
	}
	cout<<"\n服务器启动\n";
	//4 
	socklen_t addrlen=sizeof(struct sockaddr);
	while(1){
		class sockinfo* p;
		for(unsigned int i=0;i<LISTEN_MAX*3;i++){
			if(infos[i].isfree()){
				p=&infos[i];
				break;
			}
		}
		int cfd=accept(fd,p->waddr(),&addrlen);
		if(cfd==-1){
			perror("accept");
			return -1;
		}
		p->wsock(cfd);
		pthread_t tid;
		pthread_create(&tid,NULL,working,p);
		pthread_detach(tid);
	}
	close(fd);
	return 0;
}
void* working(void* arg){
	class sockinfo* p=(struct sockinfo*)arg;
	char ip[32];
	cout<<"client ip:"<<inet_ntop(AF_INET,p->getaddr(),ip,sizeof(ip))<<"  port:"<<ntohs(p->getport())<<endl;
	while(1){
		Msign *buff=(Msign*)malloc(sizeof(Msign));
		int m=recv(p->getfd(),buff,sizeof(Msign),0);
		if(m>0){
			cout<<buff->getID()<<endl<<buff->getsignK()<<endl<<buff->getplatform()<<endl<<buff->getPW();
			free(buff);
	//		send(p->getfd(),buff,sizeof(buff),0);
		}
		else if(m==0){
			cout<<endl<<"client disconnects..."<<endl;
			break;
		}
		else{
			perror("recv");
			break;
		}
	}
	close(p->getfd());
	p->wsock(-1);
	return NULL;
}

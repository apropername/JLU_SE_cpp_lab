#include"Msign.h"
#include<string>
#include"net.h"
#include<pthread.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<cstdio>
#include"exe_sign.h"
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
	in_addr_t* getIPA(){
		return &caddr.sin_addr.s_addr;
	}
	int getport(){
		return caddr.sin_port;
	}
	int getfd(){
		return fd;
	}
};
class IPID{
	static IPID* head[10];
	static IPID* tail[10];
	static int counter;
	unsigned int ID;
	char *IP;//不使用实内存可能出现问题
	IPID* next;
	public:
	IPID();
	IPID(unsigned int,char* );
	unsigned int getID ()const{
		return ID;
	}
	static void init();
	static void finish();
	static int Rcounter(){
		return counter;
	}	
	static void logout(unsigned int);
};
void* working(void*);
const unsigned int SEVERZ_PORT=6666,LISTEN_MAX=30;
sockinfo infos[LISTEN_MAX*3];//必须是全局，因为在working函数中还在使用
int IPID::counter=0;
IPID* IPID::head[10]={NULL};
IPID* IPID::tail[10]={NULL};
using namespace std;
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
	IPID::init();//IPID表的初始化，写作用域只是为了增加易读性
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
	cout<<"client ip:"<<inet_ntop(AF_INET,p->getIPA(),ip,sizeof(ip))<<"  port:"<<ntohs(p->getport())<<endl;
	Msign *buff=(Msign*)malloc(sizeof(Msign));
	int m=recv(p->getfd(),buff,sizeof(Msign),0);
	if(m==0) cout<<endl<<"client disconnects..."<<endl;
	else if (m<0)perror("recv");
	else {
		Esign Smachine;
		Smachine.exe(buff->getID(),buff->getPW(),buff->getsignK(),buff->getplatform());
		unsigned int ID=buff->getID();//为后面登录用
		free(buff);
		int tmp=Smachine.getlastE();
		m=send(p->getfd(),&tmp,sizeof(int),0);
		if(m==-1){
			perror("send");
		}
		else{
			if(tmp==2){
				IPID record(ID,ip);
				cout<<record.getID();
				IPID::logout(record.getID());
			}
		}
	}
	close(p->getfd());
	p->wsock(-1);
	return NULL;
}
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
IPID::IPID():ID(0),IP("\0"),next(NULL){}
IPID::IPID(unsigned int loginID,char *loginIP):ID(loginID),IP(loginIP),next(NULL){//考虑到先登录的更可能先登出，便使用不严格队列进行添加删除
	unsigned int index=loginID;
	tail[index]->next=this;
	tail[index]=this;
	counter++;
}
void IPID::logout(unsigned int logoutID){//结点并非动态申请，靠析构函数释放
	unsigned int index=logoutID%10;
	IPID *r0=head[index];
	IPID *r=head[index]->next;
	while(r!=NULL&&r->ID!=logoutID){
		r0=r;
		r=r->next;
	}
	if(r==NULL) cout<<"\n错误！账号不在连接列表\n";
	else{
		r0->next=r->next;
		r->next=NULL;
	}
}

void IPID::init(){
	for(int i=0;i<10;i++){
		head[i]=new IPID;
		tail[i]=head[i];
	}
}
void IPID::finish(){}

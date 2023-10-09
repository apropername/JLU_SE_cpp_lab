#include"Msign.h"
#include<iostream>
#include<cstdio>
#include<vector>
#include"net.h"
#include"clearin.cpp"
using namespace std;
void start();
int client_start();
int main(){
	cout<<"\n选择服务平台：1.we1 2.we2 3.we3 4.exit"<<endl;
	char platform='\0';
	clearin(platform);
	if(platform=='4') return 0;//
	cout<<"\n选择 I.登录 U.注册 \n或其他键退出"<<endl;
	unsigned int inID=0;
	string inPW;
	char choice='\0';
	clearin(choice);
	switch(choice){
		case 'I':
			cout<<"\n登陆"<<"\n输入ID：";
			clearin(inID);
			while(inID==0){
				cout<<"\n重新输入正确ID：";
				clearin(inID);
			}
			cout<<"\n输入密码：";
			clearin(inPW);
			while(inPW.size()>30){
				cout<<"\n输入过长"<<"\n请重新输入：";
				clearin(inPW);
			}
			break;
		case'U':
			cout<<"\n注册"<<"\n输入ID（9位以内数字串）：";
			clearin(inID);
			while(1){
				if(inID){
					cout<<"格式正确,ID:"<<inID<<endl;
					break;
				}
				else{
					cout<<"\n格式错误，重新设置:";
					clearin(inID);
				}
			}
			while(1){
				cout<<"\n输入密码：";
				clearin(inPW);
				while(inPW.size()>30){
					cout<<"\n输入过长"<<"\n请重新输入：";
					clearin(inPW);
				}
				string check;
				cout<<"\n再次输入密码：";
				clearin(check);
				while(check.size()>30){
					cout<<"\n输入过长"<<"\n请重新输入：";
					clearin(check);
				}
				if(check==inPW){
					cout<<"\n密码设置成功";
					break;
				}
				else{
					cout<<"\n两次密码不一致，重新输入";
				}
			}
			break;
		default:return 0;//
	}
	Msign link(inID,inPW,platform,choice);
	int cfd=client_start();
	if(cfd!=-1) cout<<"\n连接服务器成功";
	int m=send(cfd,&link,sizeof(link),0);
	if(m==-1){
		perror("send");
	}
	close(cfd);
	return 0;
}

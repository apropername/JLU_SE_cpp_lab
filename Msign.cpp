#include"Msign.h"
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
Msign::Msign(){
	FB=0;
}
Msign::Msign(unsigned int id, string pw ,char pf,char choice){
	FB=0;
	ID=id;
	pw.copy(PW,31);
	PF=pf;
	kind=choice;
}
unsigned int Msign::getID(){
	return ID;
}
char* Msign::getPW(){
	return PW;
}
char Msign::getplatform(){
	return PF;
}
char Msign::getsignK(){
	return kind;
}
int* Msign::setFB(){
	return &FB;
}
int Msign::outFB(){
	switch(FB){
		case 0:
			cout<<"\n服务器未执行操作\n";
			break;
		case -1:
			cout<<"\n数据库操作失败\n";
			break;
		case -2:
			cout<<"\n账号不存在\n";
			break;
		case -3:
			cout<<"\n密码错误\n";
			break;
		case -4:
			cout<<"\n该账号已存在\n";
			break;
		case 1:
			cout<<"\n注册成功\n";
			break;
		case 2:
			cout<<"\n登录\n";
			break;
		default:
			cout<<"\n未知错误\n";
	}
	return FB;
}

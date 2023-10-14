#include"exe_sign.h"
#include<mysql/mysql.h>
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
Esign::Esign(){
	lastE=0;
}
int Esign::getlastE(){
	return lastE;
}
int Esign::exe(unsigned int ID,char* PW,char kind,char PF){
	MYSQL mysql;
	mysql_init(&mysql); 
	if(mysql_real_connect(&mysql,"localhost","root","duchenxv","WeXING",3306,NULL,0) == NULL){
		cout << "connect DB fial\n";
		mysql_close(&mysql);
		return lastE=-1;
	}
	string sID=to_string(ID);
	string sPW=PW;
	string test="h";
//	if(sPW==test) cout<<"我傻了"<<endl;
//	if(PW[0]=='h') cout<<"??"<<endl;
	string table;
	if(PF=='1') table="user_info";
	else if(PF=='2') table="We2_Uinfo";
	string sql="SELECT ID,PW FROM "+table+" WHERE ID="+sID+";";
	if (mysql_query(&mysql,sql.c_str())) {
		cout<<"\n查询失败\n";
		mysql_close(&mysql);
		return lastE=-1;
	}
	MYSQL_RES * result = mysql_store_result(&mysql);
	int num=mysql_num_rows(result);
	if (kind == 'U') {
		if(num){
			cout<<"\n账号已存在\n";
			mysql_free_result(result);
			mysql_close(&mysql);
			return lastE=-4;
		}
		sql="INSERT INTO "+table+" (ID,nick_name,Tbirth,PW) VALUES ("+sID+",'null',NOW(),'"+sPW+"');";
		if (mysql_query(&mysql,sql.c_str())) {
			cout<<"\n插入失败\n";
			lastE=-1;
		}
		else lastE=1;
	}
	else if (kind == 'I') {
		if(num==0){
			cout<<"\n账号不存在\n";
			lastE=-2;
		}
		else {
			MYSQL_ROW row=mysql_fetch_row(result);
			if(row[1]==sPW) {
				if(IPID::search(ID)==NULL){
					lastE=2;
				}
				else lastE=-5;
			}
			else lastE=-3;
		}
	}
	else lastE=-6;//不可能到达
	mysql_free_result(result);
	mysql_close(&mysql);
	return lastE;
}

IPID::IPID():ID(0),IP("\0"),next(NULL){}//注册登录皆已经限制了ID!=0
IPID::IPID(unsigned int loginID,char *loginIP):ID(loginID),IP(loginIP),next(NULL){//考虑到先登录的更可能先登出，便使用不严格队列进行添加删除
	unsigned int index=loginID%10;
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
	if(r==NULL) std::cout<<"\n错误！账号不在连接列表\n";//不应该出现的情况
	else{
		r0->next=r->next;
		r->next=NULL;
		counter--;
		if(head[index]->next==NULL) tail[index]=head[index];//如果登出的账号是本链最后一个，要把tail指针复位，否则再添加时tail链将与head分离
	}
}

void IPID::init(){
	for(int i=0;i<10;i++){
		head[i]=new IPID;
		tail[i]=head[i];
	}
}
void IPID::finish(){
	for(int i=0;i<10;i++){
		delete head[i];
	}
}
IPID* IPID::search(unsigned int OID){
	if(Rcounter()){
		IPID *r=head[OID%10]->next;
		while(r!=NULL&&r->ID!=OID) r=r->next;
		return r;
	}
	else return NULL;
}

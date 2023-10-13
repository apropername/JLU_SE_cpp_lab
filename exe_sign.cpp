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
			if(row[1]==sPW) lastE=2;//goto sign in;
			else lastE=-3;
		}
	}
	else lastE=-5;//不可能到达
	mysql_free_result(result);
	mysql_close(&mysql);
	return lastE;
}

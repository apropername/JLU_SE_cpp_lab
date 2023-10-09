#include"exe_sign.h"
#include<mysql/mysql.h>
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
Esign::Esign(){
	lastE=0;
}
int Esign::exe(unsigned int ID,char* PW,char kind,char PF){
	if (kind == 'U') {
		MYSQL mysql;
		mysql_init(&mysql); 
		if(mysql_real_connect(&mysql,"localhost","root","duchenxv","WeXING",3306,NULL,0) == NULL){
			cout << "connect DB fial\n";
			return lastE=-1;
		}
		string sID=to_string(ID);
		string sPW=PW;
		string table;
		if(PF=='1') table="user_info";
		else if(PF=='2') table="We2_Uinfo";

		string sql="SELECT ID FROM "+table+" WHERE ID="+sID+";";
		if (mysql_query(&mysql,sql.c_str())) {
			cout<<"\n查询失败\n";
			return lastE=-1;
		}
		MYSQL_RES * result = mysql_store_result(&mysql);
		int num=mysql_num_rows(result);
		if(num){
			cout<<"\n账号已存在\n";
			return lastE=-2;
		}
		sql="INSERT INTO user_info (ID,nick_name,Tbirth,PW) VALUES ("+sID+",'null',NOW(),'"+sPW+"');";
		if (mysql_query(&mysql,sql.c_str())) {
			cout<<"\n插入失败\n";
			return lastE=-1;
		}
		else return lastE=1;
	}
	else if (kind == 'I') {
		return lastE=0;
	}
	else return lastE=0;;
}

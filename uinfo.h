#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
//#include<arpa/inet.h>
//#include<unistd.h>
using namespace std;
class date{
	unsigned short year;
	unsigned short month;
	unsigned short day;
public:
	date(unsigned short year,unsigned short month,unsigned short day);
	void reset();
	void print();
};
class region{
	string name;
	vector<region *> subr;//树
public:
	region(int num,string nameD);
	void link(region* const sub);
	~region();
};
class uinfo{
	unsigned int ID;
	string nickname;
	date birth;
	date Tbirth;
	vector<region*> location;
public:
	uinfo(string ,unsigned short ,unsigned short ,unsigned short ,unsigned short ,unsigned short ,unsigned short ,unsigned int );//读取数据库的账号信息
	uinfo(unsigned int  ID);//创号，或将参数成flag
	void set();//登录后修改可改信息
	void print();
};

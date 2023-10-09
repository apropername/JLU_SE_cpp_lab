#include"uinfo.h"
#include<ctime>
#include"clearin.cpp"
region::region(int num,string nameD):name(nameD),subr(num){//merely change
   }
date::date(unsigned short year,unsigned short month,unsigned short day):year(year),month(month),day(day){}//注册时间由服务器写
uinfo::uinfo(string nickD,unsigned short Tyear,unsigned short Tmonth,unsigned short Tday,unsigned short year,unsigned short month,unsigned short day,unsigned int idD):ID(idD),birth(year,month,day),Tbirth(Tyear,Tmonth,Tday),nickname(nickD){//登陆时从服务器读取账号
}
void date::print(){
	cout<<year<<"年"<<month<<"月"<<day<<"日";
	return;
}
void date::reset(){
	cout<<"\n输入年";
	unsigned short tmp=0;
	clearin(tmp);
	year=tmp;
	cout<<"\n输入月";
	clearin(tmp);
	while(tmp<1||tmp>12){
		cout<<"\n月份数据违规，重新输入：";
		clearin(tmp);
	}
	month=tmp;
	cout<<"\n输入日";
	clearin(tmp);
	while(tmp<1||tmp>31){
		cout<<"\n日期数据违规，重新输入：";
		clearin(tmp);
	}
	day=tmp;
	return;
}
void uinfo::set(){
	char choice='\n';
	while(1){
		cout<<"\n选择要设置的信息：1.昵称 2.生日 3.所在地"<<endl<<"0.返回\n";
		clearin(choice);//不知道为什么ignore会导致需要输入两遍
		switch(choice){
			case '1':
				cout<<"\n输入新昵称：";
				{//防止编译器因局部变量报错
					string tmp;
					clearin(tmp);
					while(tmp.size()>30){
						cout<<"\n输入过长"<<"\n请重新输入：";
						clearin(tmp);
					}
					nickname=tmp;
				}
				break;
			case '2':
				birth.reset();
				break;
			case '3':
				//待办
				break;
			case '0':
				return;
			default:
				cout<<"\n重新输入：";
		}
	}
	return;
}
void uinfo::print(){
	cout<<endl<<nickname<<endl<<ID;
	cout<<"\n生日：";
	birth.print();
	cout<<"\n账号创建日：";
	Tbirth.print();
	//cout<<住址
	return;
}
int main(){
	return 0;
}

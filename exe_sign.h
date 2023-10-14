#ifndef _EXE_SIGN_H_
#define _EXE_SIGN_H_
class Esign {
	int lastE;//0未执行，-1数据库操作失败，1注册成功,2准备登陆,-2登录账号不存在,-3登录密码错误,-4注册账号已存在
public:
	Esign();
	int exe(unsigned int ,char*,char,char);
	int getlastE();
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
	static void init();
	static void finish();
	static IPID* search(unsigned int);
	static int Rcounter(){
		return counter;
	}	
	static void logout(unsigned int);
};
#endif

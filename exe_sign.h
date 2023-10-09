#ifndef _EXE_SIGN_H_
#define _EXE_SIGN_H_
class Esign {
	int lastE;//0未执行，-1失败，1成功
public:
	Esign();
	int exe(unsigned int ,char*,char,char);
};
#endif

#ifndef SIGN_H
#define SIGN_H
#include<string>
using namespace std;
class Msign{
	unsigned int ID;
	char PW[31];
	char PF;
	char kind;
	int FB;
public:
	Msign();
	Msign(unsigned int,string,char,char);
	unsigned int getID();
	char* getPW();
	char getplatform();
	char getsignK();
	int *setFB();
	int outFB();
};

#endif

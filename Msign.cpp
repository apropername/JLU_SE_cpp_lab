#include"Msign.h"
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
Msign::Msign(unsigned int id, string pw ,char pf,char choice){
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

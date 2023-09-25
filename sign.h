#ifndef SIGN_H
#define SIGN_H
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
class startup{
	unsigned int ID;
	string password;
public:
	startup();
	void guidance();
};
class link{
public:
	void signin();
	void signup();
};
#endif

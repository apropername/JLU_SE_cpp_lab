#ifndef CLEAR_CPP
#define CLEAR_CPP
#include<iostream>
#include<limits>
using namespace std;
template <typename T>
void clearin(T &tmp){
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
	cin>>tmp;
}
#endif

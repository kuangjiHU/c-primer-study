#pragma once
#include<iostream>
#include"speaker.h"
using namespace std;

class MyPrint {
public:
	void operator()(int val);
	void operator()(pair<const int, Speaker>& sk);
	
};


#include<iostream>
#include<ctime>
#include"speechManager.h"

#define CLEAR_SCREEN system("pause");\
					 system("cls");


#define GET_INPUT(tip, arg) cout << tip << ":"<<endl;\
							cout << ">>>";\
							cin >> arg;
using namespace std;





int main() {

	// 随机数种子
	srand((unsigned int)time(NULL));
	SpeechManager sm;

	//打印12名选手进行测试
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "编号："<< it->first 
			<< "姓名："<<it->second.m_Name
			<< "分数：" << it->second.m_Score[0]<< endl;
	}*/

	/*for_each(sm.m_Speaker.begin(), sm.m_Speaker.end(), MyPrint());
	cout << endl;*/

	int choice=0;
	while (true) {
		sm.showMenu();
		GET_INPUT("请输入选项", choice);
		switch (choice)
		{
		case 0:
			// 退出功能
			sm.exitSystem();
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.cleanRecord();
			break;
		default:
			break;
		}
	
	}
	CLEAR_SCREEN;
	return 0;
}
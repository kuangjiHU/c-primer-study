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

	// ���������
	srand((unsigned int)time(NULL));
	SpeechManager sm;

	//��ӡ12��ѡ�ֽ��в���
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "��ţ�"<< it->first 
			<< "������"<<it->second.m_Name
			<< "������" << it->second.m_Score[0]<< endl;
	}*/

	/*for_each(sm.m_Speaker.begin(), sm.m_Speaker.end(), MyPrint());
	cout << endl;*/

	int choice=0;
	while (true) {
		sm.showMenu();
		GET_INPUT("������ѡ��", choice);
		switch (choice)
		{
		case 0:
			// �˳�����
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
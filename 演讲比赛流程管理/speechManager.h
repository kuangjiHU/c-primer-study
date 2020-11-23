#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<algorithm>
#include<numeric>

#include<fstream>
#include"myPrint.h"
//#include"Speaker.h"

using namespace std;
// �ݽ������࣬���������������û��򽻵�	
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	// �˵�
	void showMenu();
	// �˳���
	void exitSystem();
	// ��ʼ��,����
	void initSpeach();
	// ����ѡ��
	void createSpeaker();
	// ��ʼ����
	// ��������������
	void startSpeech();
	// ��ǩ
	void startSpeechDraw();
	// ����
	void SpeechContest();
	// ��ʾ��������
	void showScore();
	// �����¼
	void saveRecord();
	// �鿴������¼
	void loadRecord();
	// ��ʾ
	void showRecord();


	//����
	~SpeechManager();

	// ��Ա����
	// ��һ�ֱ���ѡ�ֱ������
	vector<int> v1;
	// ��һ�ֱ�����������
	vector<int> v2;

	// ʤ��ǰ��������
	vector<int>vVictory;
	// ��ű�ţ���Ӧ�����ѡ��
	map<int, Speaker> m_Speaker;
	// ��¼��������
	int m_Index;
	//
	bool fileIsEmpty;
	// ��������¼
	map<int, vector<string>> m_Record;
};

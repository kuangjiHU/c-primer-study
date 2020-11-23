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
// 演讲管理类，控制整个流程与用户打交道	
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	// 菜单
	void showMenu();
	// 退出：
	void exitSystem();
	// 初始化,容器
	void initSpeach();
	// 创建选手
	void createSpeaker();
	// 开始比赛
	// 比赛的整个流程
	void startSpeech();
	// 抽签
	void startSpeechDraw();
	// 比赛
	void SpeechContest();
	// 显示比赛分数
	void showScore();
	// 保存记录
	void saveRecord();
	// 查看比赛记录
	void loadRecord();
	// 显示
	void showRecord();


	//析构
	~SpeechManager();

	// 成员属性
	// 第一轮比赛选手编号容器
	vector<int> v1;
	// 第一轮比赛晋级容器
	vector<int> v2;

	// 胜利前三名容器
	vector<int>vVictory;
	// 存放编号，对应具体的选手
	map<int, Speaker> m_Speaker;
	// 记录比赛轮数
	int m_Index;
	//
	bool fileIsEmpty;
	// 存放往届记录
	map<int, vector<string>> m_Record;
};

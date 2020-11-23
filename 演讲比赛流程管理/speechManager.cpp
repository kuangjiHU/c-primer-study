#include "speechManager.h"

#define CLEAR_SCREEN system("pause");\
					 system("cls");


#define GET_INPUT(tip, arg) cout << tip << ":"<<endl;\
							cout << ">>>";\
							cin >> arg;

// 构造
SpeechManager::SpeechManager() {
	// 初始化容器属性
	this->initSpeach();
	this->createSpeaker();
	this->loadRecord();
}

void SpeechManager::showMenu() {

	cout << "*************************************" << endl;
	cout << "********* 欢迎参加演讲比赛 **********" << endl;
	cout << "*********  1.开始演讲比赛  **********" << endl;
	cout << "*********  2.查看往届记录  **********" << endl;
	cout << "*********  3.清空比赛记录  **********" << endl;
	cout << "*********  0.退出比赛程序  **********" << endl;
	cout << "*************************************" << endl;

}
// 退出系统
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


// 初始化演讲的初始信息
void SpeechManager::initSpeach() {
	// 容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	// 初始化比赛轮次
	this->m_Index = 1;

}

// 创建12选手
void SpeechManager::createSpeaker() {
	string name_seed = "ABCDEFGHIJKL";
	for (int i = 0; i < name_seed.size(); i++) {
		string name = "选手 ";
		name += name_seed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}
		int id = i + 10001;
		// 创建选手的编号并放入v1
		this->v1.push_back(id);
		// 将选手编号以及对应的选手放入 map
		this->m_Speaker.insert(make_pair(id, sp));
	}
	
}

// 开始比赛
void SpeechManager::startSpeech() {
	// 第一轮开始比赛
	// 抽签
	this->startSpeechDraw();
	system("pause");
	// 比赛
	this->SpeechContest();
	system("pause");
	// 显示晋级结果
	this->showScore();
	// 第二轮开始
	this->m_Index++;

	// 抽签
	this->startSpeechDraw();
	system("pause");

	// 比赛
	this->SpeechContest();
	system("pause");

	// 显示晋级结果
	this->showScore();
	
	// 保存到文件中
	// 重置比赛，获取比赛记录
	this->saveRecord();
	this->initSpeach();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕" << endl;
	
	CLEAR_SCREEN;
}

// 抽签
void SpeechManager::startSpeechDraw() {
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1) {
		//第一轮
		random_shuffle(this->v1.begin(), this->v1.end());
		for_each(this->v1.begin(), this->v1.end(), MyPrint());
		cout << endl;
		//cout << "---------------------------------------------------------------------" << endl;
		
	}
	else
	{
		// 第二轮
		random_shuffle(this->v2.begin(), this->v2.end());
		for_each(this->v2.begin(), this->v2.end(), MyPrint());

		cout << endl;
		//cout << "---------------------------------------------" << endl;
	
	}
}

// 比赛
void SpeechManager::SpeechContest() {
	cout << "--—--------第" << this->m_Index << "轮比赛正式开始---------------" << endl;
	vector<int> v_Src; // 比赛选手容器
	// 准备临时的容器，小组的成绩
	multimap<double, int, greater<double>> groupScore;
	int num = 0; // 六个人一组
	
	if (this->m_Index == 1){
		// 遍历
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}
	
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		// 遍历选手编号 
	
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600-1000
			//cout << score << " ";
			d.push_back(score);
		}	
		//cout << endl;
		sort(d.begin(), d.end(),greater<double>());// 降序
		// 去除最高分，去除最低分
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0);
		double avg = sum / (double)d.size();
		// 将分数放入map中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		// 打印平均分
		//cout << "选手编号：" << *it << "姓名："<< this->m_Speaker[*it] .m_Name << "平均分："<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
		// 将分数填入mutimap
		groupScore.insert(make_pair(avg, *it));
		// 每六个人去前三人
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组的比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "选手编号：" << (*it).second << "姓名：" << this->m_Speaker[it->second].m_Name << "平均分：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			// 取走前三的编号
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->m_Index == 1) {
					this->v2.push_back((*it).second);
				}
				else {
					this->vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();
		}
	}
	cout << "-------------已完成第" << this->m_Index << "轮比赛-----------------" << endl;
}

// 显示比赛分数
void SpeechManager::showScore() {
	cout << "--——----------第" << this->m_Index << "轮晋级选手信息如下------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = this->v2;
	}
	else {
		v = this->vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号：" << *it
			<< "姓名：" << this->m_Speaker[*it].m_Name
			<< "得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1]
			<< endl;
	}
	cout << endl;
	CLEAR_SCREEN;
	this->showMenu();

}


// 保存记录
void SpeechManager::saveRecord() {
	ofstream ofs; // 写入文件

	ofs.open("speech.csv", ios::out | ios::app);
	// 写入冠军
	for (vector<int>::iterator it = this->vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1]<<",";
	}
	ofs << endl;
	// 关闭
	ofs.close();
	//完成
	cout << "记录已经保存" << endl;
	// 更改文件状态
	this->fileIsEmpty = false;
}

// 查看比赛记录
void SpeechManager::loadRecord() {
	// 
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	// 文件存在
	//读到文件尾
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout <<"文件为空" <<endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	// 不为空
	this->fileIsEmpty = false;
	//将读取的单个字符放回
	ifs.putback(ch);
	string data;

	int index = 0;
	while (ifs >> data) {
		/*cout << data << endl;*/

		vector<string> v;//存放冠军的字符串
		int pos = -1;// 查询到“，”位置的变量
		int start = 0;
		
		while (true) {
			pos = data.find(',', start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
		cout << it->first << " 冠军编号: " << it->second[0]
			<< "分数：" << it->second[1] << endl;
	}*/
	//CLEAR_SCREEN;
}

// 显示
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第" << i+1 << "届"
				<< "冠军编号" << m_Record[i][0]
				<< "得分：" << m_Record[i][1] << ""
				<< "亚军编号" << m_Record[i][2]
				<< "得分：" << m_Record[i][3] << ""
				<< "季军编号" << m_Record[i][4]
				<< "得分：" << m_Record[i][5] << endl;
		}
	}
	CLEAR_SCREEN;

}

// 清空文件
void SpeechManager::cleanRecord() {
	int select;
	GET_INPUT("是否确认清空--1.是   2.否", select);
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		// 初始化容器属性
		this->initSpeach();
		this->createSpeaker();
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	CLEAR_SCREEN;
}

// 析构
SpeechManager::~SpeechManager() {
	;
}


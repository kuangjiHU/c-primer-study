#include "speechManager.h"

#define CLEAR_SCREEN system("pause");\
					 system("cls");


#define GET_INPUT(tip, arg) cout << tip << ":"<<endl;\
							cout << ">>>";\
							cin >> arg;

// ����
SpeechManager::SpeechManager() {
	// ��ʼ����������
	this->initSpeach();
	this->createSpeaker();
	this->loadRecord();
}

void SpeechManager::showMenu() {

	cout << "*************************************" << endl;
	cout << "********* ��ӭ�μ��ݽ����� **********" << endl;
	cout << "*********  1.��ʼ�ݽ�����  **********" << endl;
	cout << "*********  2.�鿴�����¼  **********" << endl;
	cout << "*********  3.��ձ�����¼  **********" << endl;
	cout << "*********  0.�˳���������  **********" << endl;
	cout << "*************************************" << endl;

}
// �˳�ϵͳ
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


// ��ʼ���ݽ��ĳ�ʼ��Ϣ
void SpeechManager::initSpeach() {
	// �����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	// ��ʼ�������ִ�
	this->m_Index = 1;

}

// ����12ѡ��
void SpeechManager::createSpeaker() {
	string name_seed = "ABCDEFGHIJKL";
	for (int i = 0; i < name_seed.size(); i++) {
		string name = "ѡ�� ";
		name += name_seed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}
		int id = i + 10001;
		// ����ѡ�ֵı�Ų�����v1
		this->v1.push_back(id);
		// ��ѡ�ֱ���Լ���Ӧ��ѡ�ַ��� map
		this->m_Speaker.insert(make_pair(id, sp));
	}
	
}

// ��ʼ����
void SpeechManager::startSpeech() {
	// ��һ�ֿ�ʼ����
	// ��ǩ
	this->startSpeechDraw();
	system("pause");
	// ����
	this->SpeechContest();
	system("pause");
	// ��ʾ�������
	this->showScore();
	// �ڶ��ֿ�ʼ
	this->m_Index++;

	// ��ǩ
	this->startSpeechDraw();
	system("pause");

	// ����
	this->SpeechContest();
	system("pause");

	// ��ʾ�������
	this->showScore();
	
	// ���浽�ļ���
	// ���ñ�������ȡ������¼
	this->saveRecord();
	this->initSpeach();
	this->createSpeaker();
	this->loadRecord();

	cout << "����������" << endl;
	
	CLEAR_SCREEN;
}

// ��ǩ
void SpeechManager::startSpeechDraw() {
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1) {
		//��һ��
		random_shuffle(this->v1.begin(), this->v1.end());
		for_each(this->v1.begin(), this->v1.end(), MyPrint());
		cout << endl;
		//cout << "---------------------------------------------------------------------" << endl;
		
	}
	else
	{
		// �ڶ���
		random_shuffle(this->v2.begin(), this->v2.end());
		for_each(this->v2.begin(), this->v2.end(), MyPrint());

		cout << endl;
		//cout << "---------------------------------------------" << endl;
	
	}
}

// ����
void SpeechManager::SpeechContest() {
	cout << "--��--------��" << this->m_Index << "�ֱ�����ʽ��ʼ---------------" << endl;
	vector<int> v_Src; // ����ѡ������
	// ׼����ʱ��������С��ĳɼ�
	multimap<double, int, greater<double>> groupScore;
	int num = 0; // ������һ��
	
	if (this->m_Index == 1){
		// ����
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}
	
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		// ����ѡ�ֱ�� 
	
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600-1000
			//cout << score << " ";
			d.push_back(score);
		}	
		//cout << endl;
		sort(d.begin(), d.end(),greater<double>());// ����
		// ȥ����߷֣�ȥ����ͷ�
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0);
		double avg = sum / (double)d.size();
		// ����������map��
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		// ��ӡƽ����
		//cout << "ѡ�ֱ�ţ�" << *it << "������"<< this->m_Speaker[*it] .m_Name << "ƽ���֣�"<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
		// ����������mutimap
		groupScore.insert(make_pair(avg, *it));
		// ÿ������ȥǰ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��ı������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "ѡ�ֱ�ţ�" << (*it).second << "������" << this->m_Speaker[it->second].m_Name << "ƽ���֣�" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			// ȡ��ǰ���ı��
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
	cout << "-------------����ɵ�" << this->m_Index << "�ֱ���-----------------" << endl;
}

// ��ʾ��������
void SpeechManager::showScore() {
	cout << "--����----------��" << this->m_Index << "�ֽ���ѡ����Ϣ����------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = this->v2;
	}
	else {
		v = this->vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "ѡ�ֱ�ţ�" << *it
			<< "������" << this->m_Speaker[*it].m_Name
			<< "�÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1]
			<< endl;
	}
	cout << endl;
	CLEAR_SCREEN;
	this->showMenu();

}


// �����¼
void SpeechManager::saveRecord() {
	ofstream ofs; // д���ļ�

	ofs.open("speech.csv", ios::out | ios::app);
	// д��ھ�
	for (vector<int>::iterator it = this->vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1]<<",";
	}
	ofs << endl;
	// �ر�
	ofs.close();
	//���
	cout << "��¼�Ѿ�����" << endl;
	// �����ļ�״̬
	this->fileIsEmpty = false;
}

// �鿴������¼
void SpeechManager::loadRecord() {
	// 
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	// �ļ�����
	//�����ļ�β
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout <<"�ļ�Ϊ��" <<endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	// ��Ϊ��
	this->fileIsEmpty = false;
	//����ȡ�ĵ����ַ��Ż�
	ifs.putback(ch);
	string data;

	int index = 0;
	while (ifs >> data) {
		/*cout << data << endl;*/

		vector<string> v;//��Źھ����ַ���
		int pos = -1;// ��ѯ��������λ�õı���
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
		cout << it->first << " �ھ����: " << it->second[0]
			<< "������" << it->second[1] << endl;
	}*/
	//CLEAR_SCREEN;
}

// ��ʾ
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "��" << i+1 << "��"
				<< "�ھ����" << m_Record[i][0]
				<< "�÷֣�" << m_Record[i][1] << ""
				<< "�Ǿ����" << m_Record[i][2]
				<< "�÷֣�" << m_Record[i][3] << ""
				<< "�������" << m_Record[i][4]
				<< "�÷֣�" << m_Record[i][5] << endl;
		}
	}
	CLEAR_SCREEN;

}

// ����ļ�
void SpeechManager::cleanRecord() {
	int select;
	GET_INPUT("�Ƿ�ȷ�����--1.��   2.��", select);
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		// ��ʼ����������
		this->initSpeach();
		this->createSpeaker();
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
	CLEAR_SCREEN;
}

// ����
SpeechManager::~SpeechManager() {
	;
}


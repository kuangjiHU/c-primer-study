#include "myPrint.h"
void MyPrint::operator()(int val) {
	cout << val << " ";
}
void MyPrint::operator()(pair<const int, Speaker>& sk) {
	cout << "��ţ�" << sk.first
		<< "������" << sk.second.m_Name
		<< "������" << sk.second.m_Score[0] << endl;
}
#include "myPrint.h"
void MyPrint::operator()(int val) {
	cout << val << " ";
}
void MyPrint::operator()(pair<const int, Speaker>& sk) {
	cout << "±àºÅ£º" << sk.first
		<< "ÐÕÃû£º" << sk.second.m_Name
		<< "·ÖÊý£º" << sk.second.m_Score[0] << endl;
}
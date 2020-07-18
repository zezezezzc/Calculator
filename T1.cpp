#include <iostream>
#include <string>
#include <vector>
using namespace std;
using std::string;

//������ʽ+�س�����
/*
֧�����ţ��Ӽ��˳�������㣬С���������������
֧�� * / ����
*/

void caculate(vector<float>& v1, vector<char>& v2, int i)	//���һ�η������
{
	switch (v2[i-1])
	{
		case '+': v1[i-1] += v1[i]; break;
		case '-': v1[i-1] -= v1[i]; break;
		case '*': v1[i-1] *= v1[i]; break;
		case '/': v1[i-1] /= v1[i]; break;
	}
	v1.pop_back();
	v2[i-1] = v2[i];	//����ǰ��һ��
	v2.pop_back();
}

void simplify(vector<float>& v1, vector<char>& v2, int i)	//���һ�η������
{
	switch (v2[i])
	{
		case '+': v1[i-1] += v1[i]; break;
		case '-': v1[i-1] -= v1[i]; break;
		case '*': v1[i-1] *= v1[i]; break;
		case '/': v1[i-1] /= v1[i]; break;
	}	
	
	v1.pop_back();
	v2[i] = v2[i+1];	//����ǰ��һ��
	v2.pop_back();	//ɾ��һ���ɵ� 
}

int main() {
	cout << "��ӭʹ�ã��û��س��˳�" << endl;
	cout << "��������ʽ��" << endl;
	string cacul;
	std::vector<float> fnum;
	std::vector<char> csign;
	float res = 0;
	int index;

	while (getline(cin, cacul)) {
		if (cacul.empty())
			break;
		float x = 0.0;
		string s = "";
		fnum.clear();
		csign.clear();
		/* ���м��� */
		for (auto c : cacul) {		//��������() ������������������һ�� 
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
				
				if (!s.empty()) {	//������Ϊ����
					x = stof(s);	//ת��Ϊ������
					fnum.push_back(x);
					s = "";		//���s�д������
					index = fnum.size() - 1;	//����vector�м�������Ԫ�ص��±�
				}

				if (c == '(') {
					csign.push_back(c);
					continue;
				}
				if (c == ')') {
					csign.push_back(c);
					while (csign[index] != '(') {
						simplify(fnum, csign, index);
						index = fnum.size() - 1;	//���¼����±�
					}
					csign.pop_back();
					csign.pop_back();	//ȥ����������
					continue;
				}
				if (c == '*' || c == '/') {
					csign.push_back(c);					
				}
				else {
					if (index == 0) {
						csign.push_back(c);		//���� + �� -
					}
					else {						
						csign.push_back(c);		//���� + �� -
						if (csign[index] != '(') {	//Ҫ����Ƿ��������� 
							while (csign[index-1] == '*' || csign[index-1] == '/') {
								caculate(fnum, csign, index);	//��ǰ����
								index = fnum.size() - 1;	//���¼����±�
							}
						}
					}
				}
			}
			else {
				s += c;
			}
		}
		if (!s.empty()) {//��ʽ�����Ϊ���ֽ���ת��Ϊ������
			x = stof(s);	
			fnum.push_back(x);
			s = "";		//���s�д������
			index = fnum.size() - 1;	//����vector�м�������Ԫ�ص��±�
		}
				
		while (!csign.empty()) {	//����������м���
			index = fnum.size() - 1;	//����ʽ�� ����Ԫ�ص��±�
			caculate(fnum, csign, index);
		}

		res = fnum[0];
		cout << "������Ϊ��" << res << '\n' <<"�û��س������˳���������ʽ��" << endl;
	}

	return 0;
}

/*
int main()
{
	std::vector<float> f{0.05, 0.75};

	for (auto t : f){
		cout << t << endl;
	}
}
*/

/*
	ȡ�����ֺͼ�����ŵ�
*/
// std::vector<float> fnum;
// std::vector<char> csign;
// for(auto c:cacul) {	
// 	if(c=='+'|c=='-'|c=='*'|c=='/'|c=='('|c==')') {
// 		if(s.empty) {
// 			cout << "�������" <<endl;
// 			break;
// 		}
// 		x = stof(s);	//ת��Ϊ������
// 		fnum.push_back(x);		//fnum.pop_back ɾ��ĩβԪ��
// 		csign.push_back(c);
// 	}
// 	else {
// 		s += c;
// 	}
// }
// if((fnum.size()+csign.size())%2==0) {	// �����ͷ��źͲ�Ϊ�������������
// 	cout <<"������ʽ��ƥ�䣬�������룺"<< endl;
// }

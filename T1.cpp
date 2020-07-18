#include <iostream>
#include <string>
#include <vector>
using namespace std;
using std::string;

//输入算式+回车即可
/*
支持括号，加减乘除混合运算，小数与整数混合运算
支持 * / 优先
*/

void caculate(vector<float>& v1, vector<char>& v2, int i)	//完成一次括号化简
{
	switch (v2[i-1])
	{
		case '+': v1[i-1] += v1[i]; break;
		case '-': v1[i-1] -= v1[i]; break;
		case '*': v1[i-1] *= v1[i]; break;
		case '/': v1[i-1] /= v1[i]; break;
	}
	v1.pop_back();
	v2[i-1] = v2[i];	//符号前移一个
	v2.pop_back();
}

void simplify(vector<float>& v1, vector<char>& v2, int i)	//完成一次反向计算
{
	switch (v2[i])
	{
		case '+': v1[i-1] += v1[i]; break;
		case '-': v1[i-1] -= v1[i]; break;
		case '*': v1[i-1] *= v1[i]; break;
		case '/': v1[i-1] /= v1[i]; break;
	}	
	
	v1.pop_back();
	v2[i] = v2[i+1];	//括号前移一个
	v2.pop_back();	//删除一个旧的 
}

int main() {
	cout << "欢迎使用，敲击回车退出" << endl;
	cout << "请输入算式：" << endl;
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
		/* 进行计算 */
		for (auto c : cacul) {		//左、右括号() 会遇到两个符号连在一起 
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
				
				if (!s.empty()) {	//先输入为符号
					x = stof(s);	//转换为浮点数
					fnum.push_back(x);
					s = "";		//清空s中存的数字
					index = fnum.size() - 1;	//符号vector中即将存入元素的下标
				}

				if (c == '(') {
					csign.push_back(c);
					continue;
				}
				if (c == ')') {
					csign.push_back(c);
					while (csign[index] != '(') {
						simplify(fnum, csign, index);
						index = fnum.size() - 1;	//重新计算下标
					}
					csign.pop_back();
					csign.pop_back();	//去除左右括号
					continue;
				}
				if (c == '*' || c == '/') {
					csign.push_back(c);					
				}
				else {
					if (index == 0) {
						csign.push_back(c);		//存入 + 或 -
					}
					else {						
						csign.push_back(c);		//存入 + 或 -
						if (csign[index] != '(') {	//要检测是否在括号内 
							while (csign[index-1] == '*' || csign[index-1] == '/') {
								caculate(fnum, csign, index);	//向前计算
								index = fnum.size() - 1;	//重新计算下标
							}
						}
					}
				}
			}
			else {
				s += c;
			}
		}
		if (!s.empty()) {//若式中最后为数字将其转换为浮点数
			x = stof(s);	
			fnum.push_back(x);
			s = "";		//清空s中存的数字
			index = fnum.size() - 1;	//符号vector中即将存入元素的下标
		}
				
		while (!csign.empty()) {	//从右至左进行计算
			index = fnum.size() - 1;	//计算式中 计算元素的下标
			caculate(fnum, csign, index);
		}

		res = fnum[0];
		cout << "计算结果为：" << res << '\n' <<"敲击回车即可退出或输入算式：" << endl;
	}

	return 0;
}

/* Test
int main()
{
	std::vector<float> f{0.05, 0.75};

	for (auto t : f){
		cout << t << endl;
	}
}
*/

/*
	取出数字和计算符号等
*/
// std::vector<float> fnum;
// std::vector<char> csign;
// for(auto c:cacul) {	
// 	if(c=='+'|c=='-'|c=='*'|c=='/'|c=='('|c==')') {
// 		if(s.empty) {
// 			cout << "输入错误" <<endl;
// 			break;
// 		}
// 		x = stof(s);	//转换为浮点数
// 		fnum.push_back(x);		//fnum.pop_back 删除末尾元素
// 		csign.push_back(c);
// 	}
// 	else {
// 		s += c;
// 	}
// }
// if((fnum.size()+csign.size())%2==0) {	// 变量和符号和不为奇数则输入错误
// 	cout <<"输入算式不匹配，重新输入："<< endl;
// }

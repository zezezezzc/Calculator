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

void caculate(vector<float>& v1, vector<char>& v2, int i, bool flg)	//完成一次计算
{
	int t = i;
	if (!flg) {
		--i;	//无括号时偏移1位;	因为有括号时，符号容器多了一个 ( 
		--t;	//无括号时，t同步偏移 
	}
	else
		--t;	//有括号时与i相差1 
	
	if((i-1)>=0) {
		if (v2[i-1]=='-') {	//判断是否变号 
			if (flg) {	//有括号，对应数字容器差一个下标 
				v1[i] = (-1)*v1[i];
			} 
			else
				v1[i+1] = (-1)*v1[i+1];		//若前一符号为-，则更改最后一个计算数的符号
		}
	}
	switch (v2[i])
	{
		case '+': v1[t] += v1[t+1]; break;
		case '-': v1[t] -= v1[t+1]; break;
		case '*': v1[t] *= v1[t+1]; break;
		case '/': v1[t] /= v1[t+1]; break;
	}
	v1.pop_back();
	v2[i] = v2[i+1];	//符号前移一个
	v2.pop_back();
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
				
				if (!s.empty()) {
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
						caculate(fnum, csign, index, true);
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
								caculate(fnum, csign, index, false);	//优先计算乘除 
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
		if (!s.empty()) {//若输入式中最后为数字将其转换为浮点数
			x = stof(s);	
			fnum.push_back(x);
			s = "";		//清空s中存的数字
			index = fnum.size() - 1;	//符号vector中即将存入元素的下标
		}

		while (!csign.empty()) {	//从右至左进行计算
			index = fnum.size() - 1;	//计算式中计算元素的下标
			caculate(fnum, csign, index, false);
		}

		res = fnum[0];
		cout << "计算结果为：" << res << '\n' <<"敲击回车即可退出或输入算式：" << endl;
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

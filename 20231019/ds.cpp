#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
bool cmpPriority(char top, char cur)//比较当前字符与栈顶字符的优先级，若栈顶高，返回true
{
	if ((top == '+' || top == '-') && (cur == '+' || cur == '-'))
		return true;
	if ((top == '*' || top == '/') && (cur == '+' || cur == '-' || top == '*' || top == '/'))
		return true;
	if (cur == ')')
		return true;
	return false;
}
vector<string> mid2post(string &str)
{

	vector<string>vstr;
	stack<char>cstack;
	for (int i = 0;i<str.size();++i)//扫描字符串
	{
		string temp = "";
		if (str[i] >= '0' && str[i] <= '9')//若是数字
		{
			temp += str[i];
			while (i + 1<str.size() && str[i + 1] >= '0' && str[i + 1] <= '9')
			{
				temp += str[i + 1];//若是连续数字
				++i;
			}
			vstr.push_back(temp);
		}
		else if (cstack.empty() || str[i] == '(')//若栈空或者字符为'('
			cstack.push(str[i]);
		else if (cmpPriority(cstack.top(), str[i]))//若栈顶元素优先级较高，栈顶元素出栈
		{
			if (str[i] == ')')//若当前字符是右括号，栈中元素出栈，入字符串数组中，直到遇到'('
			{
				while (!cstack.empty() && cstack.top() != '(')
				{
					temp += cstack.top();
					cstack.pop();
					vstr.push_back(temp);
					temp = "";
				}
				cstack.pop();
			}
			else//栈中优先级高的元素出栈，入字符串数组，直到优先级低于当前字符
			{
				while (!cstack.empty() && cmpPriority(cstack.top(), str[i]))
				{
					temp += cstack.top();
					cstack.pop();
					vstr.push_back(temp);
					temp = "";
				}
				cstack.push(str[i]);
			}
		}
		else//当前字符优先级高于栈顶元素，直接入栈
			cstack.push(str[i]);
	}
	while (!cstack.empty())//栈中还存在运算符时，出栈，存入字符串数组
	{
		string temp = "";
		temp += cstack.top();
		cstack.pop();
		vstr.push_back(temp);
	}
	return vstr;
}
int calcPostExp(vector<string> vstr)//对后缀表达式进行求值，主要是根据运算符取出两个操作数进行运算
{
	int num, op1, op2;
	stack<int>opstack;
	for (int i = 0;i<vstr.size();++i)
	{
		string temp = vstr[i];
		if (temp[0] >= '0' && temp[0] <= '9')//如果当前字符串是数字，利用字符串流转化为int型
		{
			stringstream ss;
			ss << temp;
			ss >> num;
			opstack.push(num);
		}
		else if (vstr[i] == "+")//若是操作符，取出两个操作数，进行运算，并将结果存入
		{
			op2 = opstack.top();
			opstack.pop();
			op1 = opstack.top();
			opstack.pop();
			opstack.push(op1 + op2);
		}
		else if (vstr[i] == "-")
		{
			op2 = opstack.top();
			opstack.pop();
			op1 = opstack.top();
			opstack.pop();
			opstack.push(op1 - op2);
		}
		else if (vstr[i] == "*")
		{
			op2 = opstack.top();
			opstack.pop();
			op1 = opstack.top();
			opstack.pop();
			opstack.push(op1*op2);
		}
		else if (vstr[i] == "/")
		{
			op2 = opstack.top();
			opstack.pop();
			op1 = opstack.top();
			opstack.pop();
			opstack.push(op1 / op2);
		}
	}
	return opstack.top();//最终的栈顶元素就是求解的结果
}
int main() {
	string s;
	cin >> s;
	cout << calcPostExp(mid2post(s)) << endl;

	return 0;
}

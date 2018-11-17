#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stack>
#include <cctype> //isdigit()用于检查参数是否为十进制数字字符。当参数为数字0~9时，返回非零值，否则返回零。
#include <cstdlib>
#include <math.h>

using namespace std;

//UI
void SetXY(int x, int y);
void DrawK(int x, int y);
void DrawC();
void HideCursor();
char* getans();
//判断
int judge(char *str);
//中序转后序
void translate(string opers, vector<string> &pe);
void printPostorder(vector<string> & pe);
bool isp_Optr(char c);
bool isp_notLow(char a, char b);
//计算
void calResult(vector<string> & pE);
double calRes(double leftnum, double rightnum, char optr);
//操作
void operation();
void showanswer(double *str);

//全局变量
int getx = 40, gety = 3;

//UI
//隐藏控制台的光标 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//设置光标
void SetXY(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawK(int x, int y)
{
	SetXY(0, y); y++;
	printf("┌        ─────────────────────────────┐"); SetXY(0, y); y++;
	printf("│                                     │");		                           	SetXY(0, y); y++;
	printf("└─────────────────────────────────────┘");
}

//打印界面
void DrawC()
{
	int y;

	DrawK(0, 4);
	DrawK(0, 8);
	DrawK(0, 12);
	SetXY(2, 4);
	printf("Formula:");
	SetXY(2, 8);
	printf("Answer :");
	SetXY(2, 12);
	printf("Logging:");
	y = gety;

	SetXY(getx, y); y++;
	printf("┌──┬──┬──┬──┐");	SetXY(getx, y); y++;
	printf("│ C│ %%│ &│ /│");			SetXY(getx, y); y++;
	printf("├──┼──┼──┼──┤");	SetXY(getx, y); y++;
	printf("│ 7│ 8│ 9│ *│");			SetXY(getx, y); y++;
	printf("├──┼──┼──┼──┤");	SetXY(getx, y); y++;
	printf("│ 4│ 5│ 6│ -│");			SetXY(getx, y); y++;
	printf("├──┼──┼──┼──┤");	SetXY(getx, y); y++;
	printf("│ 1│ 2│ 3│ +│");			SetXY(getx, y); y++;
	printf("├──┼──┼──┼──┤");	SetXY(getx, y); y++;
	printf("│ .│ 0│ (│ )│");			SetXY(getx, y); y++;
	printf("├──┴──┴──┴──┤");	SetXY(getx, y); y++;
	printf("│     =     │");			SetXY(getx, y); y++;
	printf("└───────────┘");

	//设置输入光标
	SetXY(2, 5);
}

//检查算式规范
int judge(char *str) {

	//获取数组长度
	int length = strlen(str);

	//判断算式末尾"="的输入
	if (str[length - 1] != '=') {
		cout << "请在算式末尾输入等号！";
		return 0;
	}

	//删除" "前的判断
	for (int i = 0; i < length; i++) {

		//判断数字之间存在运算符
		if (str[i] > 47 && str[i] < 58 && str[i + 1] == ' ') {
			for (int j = i + 1; j < length - 1; j++) {

				//排除数字空格数字的情况
				if (str[j] == ' ' && str[j + 1] > 47 && str[j + 1] < 58) {
					cout << "格式错误1！";
					return 0;
				}
				if (str[j] != ' ') {
					break;
				}
			}
		}

		//判断"sqrt"
		if (str[i] == 's') {

			//防止数组越界
			if (i < length - 7) {
				if (str[i + 1] != 'q' || str[i + 2] != 'r' || str[i + 3] != 't') {
					cout << "未能识别运算符！";
					return 0;
				}
				else {
					if (str[i + 4] != '(') {
						cout << "格式错误4！";
						return 0;
					}
				}
			}

			//将"sqrt"转化为"&"
			str[i] = '&';
			for (int j = i + 1; j < i + 4; j++) {
				str[j] = ' ';
			}
		}
	}

	//删除数组中的空格，并减少数组长度
	for (int i = 0; i < length;) {
		if (str[i] == ' ') {
			for (int j = i; j < length; j++) {
				str[j] = str[j + 1];
			}
			length--;
		}

		if (str[i] != ' ') {
			i++;
		}
	}

	//判断str[0]合法性
	if (str[0] == '(' || str[0] == '+' || str[0] == '&' || (str[0] > 47 && str[0] < 58)) {

	}
	else if (str[0] == '-') {
		//"-"前添"0"
		for (int i = length - 1; i > -1; i--) {
			str[i + 1] = str[i];
		}
		str[0] = '0';
	}
	else {
		cout << "格式错误2！";
		return 0;
	}

	//判断是否有非法字符
	for (int i = 0; i < length; i++) {
		if (str[i] > 122 || str[i] < 37 || str[i] == 39 || str[i] == 44 || str[i] == 58 ||
			str[i] == 59 || str[i] == 60 || str[i] == 62 || str[i] == 63 || str[i] == 64 ||
			str[i] == 91 || str[i] == 92 || str[i] == 93 || str[i] == 95 || str[i] == 96) {
			cout << "请不要输入非法字符！";
			return 0;
		}

		//判断"="的个数
		if (str[i] == '=') {
			if (i != length - 1) {
				cout << "格式错误3！";
				return 0;
			}
		}
	}

	//检验
	int leftcount = 0;
	int rightcount = 0;
	for (int i = 0; i < length; i++) {

		//判断"+","-","*","/","(","^"
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == '^') {

			//符号后面只能是数字或"("或"&"或"-"
			if (str[i + 1] == '(' || (str[i + 1] > 47 && str[i + 1] < 58) || str[i + 1] == '&' || str[i + 1] == '-') {

			}
			else {
				cout << "格式错误5！";
				return 0;
			}
		}

		//判断"."
		if (str[i] == '.') {

			//"."后面只能是数字
			if (str[i + 1] < 48 || str[i] > 57) {
				cout << "格式错误6！";
				return 0;
			}
		}

		//"("计数
		if (str[i] == '(') {
			leftcount++;
		}

		//")"计数并检验
		if (str[i] == ')') {
			rightcount++;

			//")"后面只能是"+","-","*","/",")","=","^","%"
			if (str[i + 1] != ')' && str[i + 1] != '^' && str[i + 1] != '=' && str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '*' && str[i + 1] != '/' && str[i + 1] != '%') {
				cout << "格式错误7！";
				return 0;
			}
		}

		//当")"数量多于"("的时候报错
		if (rightcount > leftcount) {
			cout << "格式错误8！";
			return 0;
		}

		//判断"*","/","%"前面必须有")"或数字
		if (str[i] == '*' || str[i] == '/' || str[i] == '%') {
			if (str[i - 1] != ')' && (str[i - 1] < 48 || str[i - 1] > 57)) {
				cout << "格式错误9！";
				return 0;
			}
		}

		//将负号改为减号
		if (str[i] == '-' && (str[i - 1] < 48 || str[i - 1] > 57)) {
			for (int j = length - 1; j > i - 1; j--) {
				str[j + 1] = str[j];
			}
			str[i] = '0';
		}

		//"&"后面只能是"("
		if (str[i] == '&' && str[i + 1] != '(') {
			cout << "格式错误10！";
			return 0;
		}
	}

	//当"("")"数量不相等的时候报错
	if (leftcount != rightcount) {
		cout << "格式错误11！";
		return 0;
	}

	return 1;
}

//转化为后缀表达式
void translate(string opers, vector<string> & pe)
{
	string st = "";
	stack <char> pes;			//储存运算符号的栈 
	vector<string> pev;			//用来保存后缀表达式
	int i = 0, j = 0, length = opers.length();

	while (i < length)
	{
		if (opers[i] == '&')					//开方符号直接入栈 
		{
			pes.push(opers[i++]);
		}
		else if (opers[i] == '(')
		{
			pes.push(opers[i++]);

			if (opers[i] == '-')	//如果括号后是负数 
			{
				j = i;
				while (i++ < length && isdigit(opers[i])) {}

				if (i < length && opers[i] == '.')
					while (i++ < length && isdigit(opers[i])) {}

				pev.push_back(opers.substr(j, i - j));
			}
		}
		else if (opers[i] == ')')	//如果是右括号)
		{
			while (pes.top() != '(')
			{
				pev.push_back(st + pes.top());
				pes.pop();
			}

			//抛出"("
			pes.pop();

			//如果是开方
			if (pes.top() == '&') {
				pev.push_back(st + pes.top());
				pes.pop();
			}

			i++;
		}

		else if (isp_Optr(opers[i]) || opers[i] == '^')	//如果是运算符号或"^"
		{
			while (!pes.empty() && (isp_notLow(pes.top(), opers[i])))	//比较运算符号优先级
			{
				pev.push_back(st + pes.top());
				pes.pop();
			}
			pes.push(opers[i++]);
		}

		else if (isdigit(opers[i]))	//数字的入栈
		{
			j = i;

			while (i++ < length && isdigit(opers[i])) {}

			if (i < length && opers[i] == '.')
				while (i++ < length && isdigit(opers[i])) {}
			pev.push_back(opers.substr(j, i - j));
		}
		else if (opers[i] == '=')		//等于号判断表达式结束 
			break;
	}

	while (!pes.empty())		//栈中剩余符号处理 
	{
		pev.push_back(st + pes.top());
		pes.pop();
	}

	pe = pev;

	calResult(pe);
}

//打印后缀表达式
void printPostorder(vector<string> & pe) {			//打印vector 
	vector<string> ::iterator it;			//迭代器(iterator)
	cout << endl;
	for (it = pe.begin(); it != pe.end(); it++)
		cout << *it << " ";
	cout << endl << endl;
}

/*
接口函数bool isp_Optr(char c)
判断字符c是否为操作符‘+’，‘-’，‘*’，‘/’，若是则返回true，否则返回false (‘#’表示负号，较为特殊，需单独考虑)
*/
bool isp_Optr(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

/*
接口函数bool isp_notLow(char a, char b)
如果操作符a的优先级不比b低，则返回true，否则返回false
*/
bool isp_notLow(char a, char b)
{
	if (a == '(' || b == '(') return false;
	if ((a == '+' || a == '-') && (b == '*' || b == '/' || b == '%'))
		return false;
	if ((a == '+' || a == '-' || a == '*' || a == '/' || a == '%') && (b == '^'))
		return false;
	return true;
}

/*
接口函数
根据符号对栈里的数字进行计算，并返回结果
*/
double calRes(double leftnum, double rightnum, char optr) {
	double answer;

	switch (optr) {
	case '+': answer = leftnum + rightnum; break;
	case '-': answer = leftnum - rightnum; break;
	case '*': answer = leftnum * rightnum; break;
	case '/': answer = leftnum / rightnum; break;
	case '^': answer = pow(leftnum, rightnum); break;
	case '&': answer = sqrt(rightnum); break;
	case '%': answer = (int)leftnum % (int)rightnum; break;
	}

	return answer;
}

//接口函数，计算后缀表达式
void calResult(vector<string> & pE) {

	stack<double> result;

	double rightnum;
	double leftnum;
	int correction = 1;

	for (vector<string> ::iterator re = pE.begin(); re != pE.end(); re++) {
		if (isdigit((*re)[0]))	//处理表达式中的数字 
		{
			result.push(atof((*re).c_str()));	//atof()将字符串转化为浮点数 ，将数字压入栈中 
		}
		else if (isp_Optr((*re)[0])) {	//处理表达式中的符号
			rightnum = result.top();
			result.pop();
			leftnum = result.top();
			result.pop();

			if ((*re)[0] == '/' && rightnum == 0) {

				//覆盖Logging
				SetXY(2, 13);
				cout << "除数不能为0！";
				correction = 0;
				break;
			}
			else {
				result.push(calRes(leftnum, rightnum, (*re)[0]));
			}

		}
		else if ((*re)[0] == '&') {
			//开方
			rightnum = result.top();
			result.pop();

			if (rightnum < 0) {

				//覆盖Logging
				SetXY(2, 13);
				cout << "根号内不能为负数！";
				correction = 0;
				break;
			}
			else {
				result.push(calRes(0, rightnum, (*re)[0]));
			}

		}
	}

	double answer = 0;

	if (correction == 1) {
		answer = result.top();
		result.pop();
	}

	if (result.empty()) {

	}
	else {
		correction = 0;
	}

	double string[2] = { correction, answer };
	showanswer(string);
}

void showanswer(double *str) {
	if (str[0] == 0) {

	}
	else if (str[0] == 1) {

		//设置答案光标
		SetXY(2, 9);

		//打印答案
		cout << str[1];
	}
}

//操作
void operation() {
	char string1[100];
	gets_s(string1);

	SetXY(2, 13);
	int judgement = 0;
	judgement = judge(string1);
	if (judgement == 1) {
		cout << "success!";

		//获取数组长度
		int length = strlen(string1);

		//删除数组中的空格，并减少数组长度
		for (int i = 0; i < length;) {
			if (string1[i] == ' ') {
				for (int j = i; j < length; j++) {
					string1[j] = string1[j + 1];
				}
				length--;
			}

			if (string1[i] != ' ') {
				i++;
			}
		}

		//输出删除空格后的结果
		SetXY(2, 18);

		//数组转为字符串
		string str;
		str = string1;

		vector<string> p;
		translate(str, p);
	}
	else if (judgement == 0) {
		//cout << "fail!";
	}
}


#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stack>
#include <cctype> //isdigit()���ڼ������Ƿ�Ϊʮ���������ַ���������Ϊ����0~9ʱ�����ط���ֵ�����򷵻��㡣
#include <cstdlib>
#include <math.h>

using namespace std;

//UI
void SetXY(int x, int y);
void DrawK(int x, int y);
void DrawC();
void HideCursor();
char* getans();
//�ж�
int judge(char *str);
//����ת����
void translate(string opers, vector<string> &pe);
void printPostorder(vector<string> & pe);
bool isp_Optr(char c);
bool isp_notLow(char a, char b);
//����
void calResult(vector<string> & pE);
double calRes(double leftnum, double rightnum, char optr);
//����
void operation();
void showanswer(double *str);

//ȫ�ֱ���
int getx = 40, gety = 3;

//UI
//���ؿ���̨�Ĺ�� 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ù��
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
	printf("��        ������������������������������������������������������������"); SetXY(0, y); y++;
	printf("��                                     ��");		                           	SetXY(0, y); y++;
	printf("������������������������������������������������������������������������������");
}

//��ӡ����
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
	printf("�������Щ����Щ����Щ�����");	SetXY(getx, y); y++;
	printf("�� C�� %%�� &�� /��");			SetXY(getx, y); y++;
	printf("�������੤���੤���੤����");	SetXY(getx, y); y++;
	printf("�� 7�� 8�� 9�� *��");			SetXY(getx, y); y++;
	printf("�������੤���੤���੤����");	SetXY(getx, y); y++;
	printf("�� 4�� 5�� 6�� -��");			SetXY(getx, y); y++;
	printf("�������੤���੤���੤����");	SetXY(getx, y); y++;
	printf("�� 1�� 2�� 3�� +��");			SetXY(getx, y); y++;
	printf("�������੤���੤���੤����");	SetXY(getx, y); y++;
	printf("�� .�� 0�� (�� )��");			SetXY(getx, y); y++;
	printf("�������ة����ة����ة�����");	SetXY(getx, y); y++;
	printf("��     =     ��");			SetXY(getx, y); y++;
	printf("��������������������������");

	//����������
	SetXY(2, 5);
}

//�����ʽ�淶
int judge(char *str) {

	//��ȡ���鳤��
	int length = strlen(str);

	//�ж���ʽĩβ"="������
	if (str[length - 1] != '=') {
		cout << "������ʽĩβ����Ⱥţ�";
		return 0;
	}

	//ɾ��" "ǰ���ж�
	for (int i = 0; i < length; i++) {

		//�ж�����֮����������
		if (str[i] > 47 && str[i] < 58 && str[i + 1] == ' ') {
			for (int j = i + 1; j < length - 1; j++) {

				//�ų����ֿո����ֵ����
				if (str[j] == ' ' && str[j + 1] > 47 && str[j + 1] < 58) {
					cout << "��ʽ����1��";
					return 0;
				}
				if (str[j] != ' ') {
					break;
				}
			}
		}

		//�ж�"sqrt"
		if (str[i] == 's') {

			//��ֹ����Խ��
			if (i < length - 7) {
				if (str[i + 1] != 'q' || str[i + 2] != 'r' || str[i + 3] != 't') {
					cout << "δ��ʶ���������";
					return 0;
				}
				else {
					if (str[i + 4] != '(') {
						cout << "��ʽ����4��";
						return 0;
					}
				}
			}

			//��"sqrt"ת��Ϊ"&"
			str[i] = '&';
			for (int j = i + 1; j < i + 4; j++) {
				str[j] = ' ';
			}
		}
	}

	//ɾ�������еĿո񣬲��������鳤��
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

	//�ж�str[0]�Ϸ���
	if (str[0] == '(' || str[0] == '+' || str[0] == '&' || (str[0] > 47 && str[0] < 58)) {

	}
	else if (str[0] == '-') {
		//"-"ǰ��"0"
		for (int i = length - 1; i > -1; i--) {
			str[i + 1] = str[i];
		}
		str[0] = '0';
	}
	else {
		cout << "��ʽ����2��";
		return 0;
	}

	//�ж��Ƿ��зǷ��ַ�
	for (int i = 0; i < length; i++) {
		if (str[i] > 122 || str[i] < 37 || str[i] == 39 || str[i] == 44 || str[i] == 58 ||
			str[i] == 59 || str[i] == 60 || str[i] == 62 || str[i] == 63 || str[i] == 64 ||
			str[i] == 91 || str[i] == 92 || str[i] == 93 || str[i] == 95 || str[i] == 96) {
			cout << "�벻Ҫ����Ƿ��ַ���";
			return 0;
		}

		//�ж�"="�ĸ���
		if (str[i] == '=') {
			if (i != length - 1) {
				cout << "��ʽ����3��";
				return 0;
			}
		}
	}

	//����
	int leftcount = 0;
	int rightcount = 0;
	for (int i = 0; i < length; i++) {

		//�ж�"+","-","*","/","(","^"
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == '^') {

			//���ź���ֻ�������ֻ�"("��"&"��"-"
			if (str[i + 1] == '(' || (str[i + 1] > 47 && str[i + 1] < 58) || str[i + 1] == '&' || str[i + 1] == '-') {

			}
			else {
				cout << "��ʽ����5��";
				return 0;
			}
		}

		//�ж�"."
		if (str[i] == '.') {

			//"."����ֻ��������
			if (str[i + 1] < 48 || str[i] > 57) {
				cout << "��ʽ����6��";
				return 0;
			}
		}

		//"("����
		if (str[i] == '(') {
			leftcount++;
		}

		//")"����������
		if (str[i] == ')') {
			rightcount++;

			//")"����ֻ����"+","-","*","/",")","=","^","%"
			if (str[i + 1] != ')' && str[i + 1] != '^' && str[i + 1] != '=' && str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '*' && str[i + 1] != '/' && str[i + 1] != '%') {
				cout << "��ʽ����7��";
				return 0;
			}
		}

		//��")"��������"("��ʱ�򱨴�
		if (rightcount > leftcount) {
			cout << "��ʽ����8��";
			return 0;
		}

		//�ж�"*","/","%"ǰ�������")"������
		if (str[i] == '*' || str[i] == '/' || str[i] == '%') {
			if (str[i - 1] != ')' && (str[i - 1] < 48 || str[i - 1] > 57)) {
				cout << "��ʽ����9��";
				return 0;
			}
		}

		//�����Ÿ�Ϊ����
		if (str[i] == '-' && (str[i - 1] < 48 || str[i - 1] > 57)) {
			for (int j = length - 1; j > i - 1; j--) {
				str[j + 1] = str[j];
			}
			str[i] = '0';
		}

		//"&"����ֻ����"("
		if (str[i] == '&' && str[i + 1] != '(') {
			cout << "��ʽ����10��";
			return 0;
		}
	}

	//��"("")"��������ȵ�ʱ�򱨴�
	if (leftcount != rightcount) {
		cout << "��ʽ����11��";
		return 0;
	}

	return 1;
}

//ת��Ϊ��׺���ʽ
void translate(string opers, vector<string> & pe)
{
	string st = "";
	stack <char> pes;			//����������ŵ�ջ 
	vector<string> pev;			//���������׺���ʽ
	int i = 0, j = 0, length = opers.length();

	while (i < length)
	{
		if (opers[i] == '&')					//��������ֱ����ջ 
		{
			pes.push(opers[i++]);
		}
		else if (opers[i] == '(')
		{
			pes.push(opers[i++]);

			if (opers[i] == '-')	//������ź��Ǹ��� 
			{
				j = i;
				while (i++ < length && isdigit(opers[i])) {}

				if (i < length && opers[i] == '.')
					while (i++ < length && isdigit(opers[i])) {}

				pev.push_back(opers.substr(j, i - j));
			}
		}
		else if (opers[i] == ')')	//�����������)
		{
			while (pes.top() != '(')
			{
				pev.push_back(st + pes.top());
				pes.pop();
			}

			//�׳�"("
			pes.pop();

			//����ǿ���
			if (pes.top() == '&') {
				pev.push_back(st + pes.top());
				pes.pop();
			}

			i++;
		}

		else if (isp_Optr(opers[i]) || opers[i] == '^')	//�����������Ż�"^"
		{
			while (!pes.empty() && (isp_notLow(pes.top(), opers[i])))	//�Ƚ�����������ȼ�
			{
				pev.push_back(st + pes.top());
				pes.pop();
			}
			pes.push(opers[i++]);
		}

		else if (isdigit(opers[i]))	//���ֵ���ջ
		{
			j = i;

			while (i++ < length && isdigit(opers[i])) {}

			if (i < length && opers[i] == '.')
				while (i++ < length && isdigit(opers[i])) {}
			pev.push_back(opers.substr(j, i - j));
		}
		else if (opers[i] == '=')		//���ں��жϱ��ʽ���� 
			break;
	}

	while (!pes.empty())		//ջ��ʣ����Ŵ��� 
	{
		pev.push_back(st + pes.top());
		pes.pop();
	}

	pe = pev;

	calResult(pe);
}

//��ӡ��׺���ʽ
void printPostorder(vector<string> & pe) {			//��ӡvector 
	vector<string> ::iterator it;			//������(iterator)
	cout << endl;
	for (it = pe.begin(); it != pe.end(); it++)
		cout << *it << " ";
	cout << endl << endl;
}

/*
�ӿں���bool isp_Optr(char c)
�ж��ַ�c�Ƿ�Ϊ��������+������-������*������/���������򷵻�true�����򷵻�false (��#����ʾ���ţ���Ϊ���⣬�赥������)
*/
bool isp_Optr(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

/*
�ӿں���bool isp_notLow(char a, char b)
���������a�����ȼ�����b�ͣ��򷵻�true�����򷵻�false
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
�ӿں���
���ݷ��Ŷ�ջ������ֽ��м��㣬�����ؽ��
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

//�ӿں����������׺���ʽ
void calResult(vector<string> & pE) {

	stack<double> result;

	double rightnum;
	double leftnum;
	int correction = 1;

	for (vector<string> ::iterator re = pE.begin(); re != pE.end(); re++) {
		if (isdigit((*re)[0]))	//������ʽ�е����� 
		{
			result.push(atof((*re).c_str()));	//atof()���ַ���ת��Ϊ������ ��������ѹ��ջ�� 
		}
		else if (isp_Optr((*re)[0])) {	//������ʽ�еķ���
			rightnum = result.top();
			result.pop();
			leftnum = result.top();
			result.pop();

			if ((*re)[0] == '/' && rightnum == 0) {

				//����Logging
				SetXY(2, 13);
				cout << "��������Ϊ0��";
				correction = 0;
				break;
			}
			else {
				result.push(calRes(leftnum, rightnum, (*re)[0]));
			}

		}
		else if ((*re)[0] == '&') {
			//����
			rightnum = result.top();
			result.pop();

			if (rightnum < 0) {

				//����Logging
				SetXY(2, 13);
				cout << "�����ڲ���Ϊ������";
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

		//���ô𰸹��
		SetXY(2, 9);

		//��ӡ��
		cout << str[1];
	}
}

//����
void operation() {
	char string1[100];
	gets_s(string1);

	SetXY(2, 13);
	int judgement = 0;
	judgement = judge(string1);
	if (judgement == 1) {
		cout << "success!";

		//��ȡ���鳤��
		int length = strlen(string1);

		//ɾ�������еĿո񣬲��������鳤��
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

		//���ɾ���ո��Ľ��
		SetXY(2, 18);

		//����תΪ�ַ���
		string str;
		str = string1;

		vector<string> p;
		translate(str, p);
	}
	else if (judgement == 0) {
		//cout << "fail!";
	}
}


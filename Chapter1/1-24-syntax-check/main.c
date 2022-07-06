/*
* 1-24 
* Write a program to check a C program for rudimentary syntax erros like
* unbalanced parentheses, brackets and braces. Don't forget about quotes, 
* both single and double, escape sequences, and comments.
* (This program is hard if you do it in full generality.)
*/

#include <stdio.h>

// ��໺�� 8192 ���ַ�
// ���ڳ����������ʱ��ע�Ϳ�ʼǰ���Ὣ������գ����
// 8192 �ǵ��д�����󳤶ȣ��㹻��
#define MAX_CACHE 8192

#define MAX_STACK 81920

struct CheckPoint {
	int line;
	int pos;
	int content;
};

struct Stack {
	struct CheckPoint cps[MAX_STACK];
	int len;
}stack;

void push(int c, int line, int pos) {
	stack.cps[stack.len].content = c;
	stack.cps[stack.len].line = line;
	stack.cps[stack.len].pos = pos;
	stack.len++;
}

void pop(int c) {
	if (stack.len > 0 && stack.cps[stack.len - 1].content == c) {
		stack.len--;
	}
}


// ״̬��
enum Status {
	NORMAL,			// ����״̬�����������κ�״̬������ͨ�Ĵ���
	SINGLE_QUOTING, // �ַ�����������
	DOUBLE_QUOTING, // �ַ�������������
	SINGLE_QUOTING_BACKSLASHING,		// �ַ��ں���ת���ַ� '\\'
	DOUBLE_QUOTING_BACKSLASHING,		// �ַ����ں���ת���ַ� '\\'
	C_COMMENTING,	// C���ע����
	CPP_COMMENTING, // C++���ע����
};




/*
* ��������ַ�������״̬�����д���
*/
int grammer_check()
{
	char buf[MAX_CACHE];
	int c, i = 0, line = 1, pos = 0;
	enum Status status = NORMAL;
	stack.len = 0;

	while ((c = getchar()) != EOF && i < MAX_CACHE) {
		buf[i++] = c;
		pos++;

		switch (status) {
		case SINGLE_QUOTING:
			if (c == '\\') {
				status = SINGLE_QUOTING_BACKSLASHING;
			} else if (c == '\'') { // �ҵ����ַ������Ľ�β������
				status = NORMAL;
				pop('\'');
			} else if (c == '\n') {
				line++;
				pos = 0;
			}
			break;
		case DOUBLE_QUOTING:
			if (c == '\\') {
				status = DOUBLE_QUOTING_BACKSLASHING;
			} else if (c == '"') { // �ҵ����ַ��������Ľ�β˫����
				status = NORMAL; 
				pop('\"');
			} else if (c == '\n') {
				line++;
				pos = 0;
			}
			break;
		case SINGLE_QUOTING_BACKSLASHING:
			status = SINGLE_QUOTING;
			break;
		case DOUBLE_QUOTING_BACKSLASHING:
			status = DOUBLE_QUOTING;
			break;
		case C_COMMENTING:
			if (c == '/' && i > 1 && buf[i - 2] == '*') { // �ҵ���C���ע�ͽ�β��ע�ͽ���
				status = NORMAL;
				i = 0; // ���¿�ʼ����
			} else if (c == '\n') {
				line++;
				pos = 0;
			}
			break;
		case CPP_COMMENTING:
			if (c == '\n') {
				line++;
				pos = 0;
				if (i > 1 && buf[i - 2] != '\\') { // �ҵ���C++���ע�ͽ�β��\n��ע�ͽ�����������Ҫ������ \ ǿ��ת���� comment 5
					status = NORMAL;
					i = 0;
				}
			}
			break;
		default:
			switch (c) {
			case '\'': // ����״̬�£����������ż���Ϊ��ʼ���ַ���������
				status = SINGLE_QUOTING; 
				push('\'', line, pos - 1);
				break;
			case '"': // ����״̬�£�����˫���ż���Ϊ��ʼ���ַ�����������
				status = DOUBLE_QUOTING;
				push('\"', line, pos - 1);
				break;
			case '/': // ����״̬�£������� // ����Ϊ��ʼ��C++����ע��
				if (i > 1 && buf[i - 2] == '/') {
					status = CPP_COMMENTING;
				}
				break;
			case '*': // ����״̬�£������� /* ����Ϊ��ʼ��C����ע��
				if (i > 1 && buf[i - 2] == '/') {
					status = C_COMMENTING;
				}
				break;
			case '\n': 
				i = 0;
				line++;
				pos = 0;
				break;
			case '(':
				push('(', line, pos - 1);
				break;
			case ')':
				pop('(');
				break;
			case '[':
				push('[', line, pos - 1);
				break;
			case ']':
				pop('[');
				break;
			case '{':
				push('{', line, pos - 1);
				break;
			case '}':
				pop('{');
				break;
			}

			// ״̬�������ı�Ϊע��ʱ����ջ���
			if (status == CPP_COMMENTING || status == C_COMMENTING) {
				i = 0;
			}
		}
	}

	return stack.len == 0;
}

int main()
{
	if (grammer_check()) {
		printf("Grammer correct\n");
	} else {
		printf("There are %d errors:\n", stack.len);
		for (int i = 0; i < stack.len; i++) {
			switch (stack.cps[i].content) {
			case '(':
				printf("line %d pos %d has mismatched parenthesis\n", stack.cps[i].line, stack.cps[i].pos);
				break;
			case '[':
				printf("line %d pos %d has mismatched brackets\n", stack.cps[i].line, stack.cps[i].pos);
				break;
			case '{':
				printf("line %d pos %d has mismatched braces\n", stack.cps[i].line, stack.cps[i].pos);
				break;
			case '\'':
				printf("line %d pos %d has mismatched single quotes\n", stack.cps[i].line, stack.cps[i].pos);
				break;
			case '\"':
				printf("line %d pos %d has mismatched double quotes\n", stack.cps[i].line, stack.cps[i].pos);
				break;
			}
		}
	}
} 

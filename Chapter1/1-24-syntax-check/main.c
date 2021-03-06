/*
* 1-24 
* Write a program to check a C program for rudimentary syntax erros like
* unbalanced parentheses, brackets and braces. Don't forget about quotes, 
* both single and double, escape sequences, and comments.
* (This program is hard if you do it in full generality.)
*/

#include <stdio.h>

// 最多缓存 8192 个字符
// 由于程序读到换行时或注释开始前都会将缓存清空，因此
// 8192 是单行代码最大长度，足够了
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


// 状态机
enum Status {
	NORMAL,			// 正常状态，即非下述任何状态，是普通的代码
	SINGLE_QUOTING, // 字符常量定义中
	DOUBLE_QUOTING, // 字符串常量定义中
	SINGLE_QUOTING_BACKSLASHING,		// 字符内含有转义字符 '\\'
	DOUBLE_QUOTING_BACKSLASHING,		// 字符串内含有转义字符 '\\'
	C_COMMENTING,	// C风格注释中
	CPP_COMMENTING, // C++风格注释中
};




/*
* 逐个读入字符，根据状态机进行处理
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
			} else if (c == '\'') { // 找到了字符常量的结尾单引号
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
			} else if (c == '"') { // 找到了字符串常量的结尾双引号
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
			if (c == '/' && i > 1 && buf[i - 2] == '*') { // 找到了C风格注释结尾，注释结束
				status = NORMAL;
				i = 0; // 重新开始缓存
			} else if (c == '\n') {
				line++;
				pos = 0;
			}
			break;
		case CPP_COMMENTING:
			if (c == '\n') {
				line++;
				pos = 0;
				if (i > 1 && buf[i - 2] != '\\') { // 找到了C++风格注释结尾即\n，注释结束，但这里要考虑以 \ 强制转行如 comment 5
					status = NORMAL;
					i = 0;
				}
			}
			break;
		default:
			switch (c) {
			case '\'': // 正常状态下，读到单引号即认为开始了字符常量定义
				status = SINGLE_QUOTING; 
				push('\'', line, pos - 1);
				break;
			case '"': // 正常状态下，读到双引号即认为开始了字符串常量定义
				status = DOUBLE_QUOTING;
				push('\"', line, pos - 1);
				break;
			case '/': // 正常状态下，读到了 // 即认为开始了C++风格的注释
				if (i > 1 && buf[i - 2] == '/') {
					status = CPP_COMMENTING;
				}
				break;
			case '*': // 正常状态下，读到了 /* 即认为开始了C风格的注释
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

			// 状态从正常改变为注释时，清空缓存
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

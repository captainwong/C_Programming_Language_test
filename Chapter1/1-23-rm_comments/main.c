/*
* 练习1-23 编写一个删除C语言程序中所有的注释语句。
* 要正确处理带引号的字符串与字符常量。
* 在C语言中，注释语句不允许嵌套。
*/

#include <stdio.h>
#include <string.h>
#include "test.h"

// 最多缓存 8192 个字符
// 由于程序读到换行时或注释开始前都会将缓存清空，因此
// 8192 是单行代码最大长度，足够了
#define MAX_CACHE 8192

// 状态机
enum Status {
	NORMAL,			// 正常状态，即非下述任何状态，是普通的代码
	SINGLE_QUOTING, // 字符常量定义中
	DOUBLE_QUOTING, // 字符串常量定义中
	C_COMMENTING,	// C风格注释中
	CPP_COMMENTING, // C++风格注释中
};

/*
* 逐个读入字符，根据状态机进行处理
*/
void rm_comment2()
{
	char buf[MAX_CACHE];
	int c, i = 0;
	enum Status status = NORMAL;

	while ((c = getchar()) != EOF && i < MAX_CACHE - 2) { // -2是因为循环内有可能再手动补 '\0' 或 '%'
		buf[i++] = c;

		switch (status) {
		case SINGLE_QUOTING:
			if (c == '\'' && i > 1 && buf[i - 2] != '\\') { // 找到了字符常量的结尾单引号
				status = NORMAL;
			}
			break;
		case DOUBLE_QUOTING:
			if (c == '"' && i > 1 && buf[i - 2] != '\\') { // 找到了字符串常量的结尾双引号
				status = NORMAL;
			} else if (c == '%') { // 我们自己要输出字符串，如果字符串包含%转义，直接传给printf会缺少参数
				buf[i++] = '%';
			}
			break;
		case C_COMMENTING:
			if (c == '/' && i > 1 && buf[i - 2] == '*') { // 找到了C风格注释结尾，注释结束
				status = NORMAL; 
				i = 0; // 重新开始缓存
			}
			break;
		case CPP_COMMENTING:
			if (c == '\n' && i > 1 && buf[i - 2] != '\\') { // 找到了C++风格注释结尾即\n，注释结束，但这里要考虑以 \ 强制转行如 comment 5
				status = NORMAL; 
				i = 0; // 重新开始缓存
			}
			break;
		default:
			switch (c) {
			case '\'': // 正常状态下，读到单引号即认为开始了字符常量定义
				status = SINGLE_QUOTING;
				break;
			case '"': // 正常状态下，读到双引号即认为开始了字符串常量定义
				status = DOUBLE_QUOTING;
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
			case '\n': // 读完一行，打印一行
				buf[i] = '\0';
				printf(buf);
				i = 0;
				break;
			}

			// 状态从正常改变为注释时，将注释开始前的内容打印，并清空缓存
			if (status == CPP_COMMENTING || status == C_COMMENTING) {
				buf[i - 2] = '\0'; // 不要输出 // 或 /*
				printf(buf);
				i = 0;
			}
		}
	}

	// 考虑读完了但文件结尾没有换行
	buf[i] = '\0';
	printf(buf); // 完结撒花
}

int main()
{
	rm_comment2();

	return 0;
}

/*
* 练习1-23 编写一个删除C语言程序中所有的注释语句。
* 要正确处理带引号的字符串与字符常量。
* 在C语言中，注释语句不允许嵌套。
*/

#include <stdio.h>
#include <string.h>
#include "test.h"

#define MAX_CACHE 8192

void rm_comment()
{
	char buf[MAX_CACHE];
	// 字符串常量，注释，注释风格
	int quoting = 0, commenting = 0, cppcomment = 0;
	int c, i = 0;

	while ((c = getchar()) != EOF && i < MAX_CACHE - 2) { // -2是因为循环内有可能再补 '\0' 或 '%'
		buf[i++] = c;
		if (quoting) { // 字符串常量没完
			if (c == '"' && i > 1 && buf[i - 2] != '\\') { // 找到了字符串常量的结尾引号
				quoting = 0;
			}
			if (c == '%') { // 我们自己要输出字符串，如果字符串包含%转义，直接传给printf会缺少参数
				buf[i++] = '%';
			}
			continue; // 字符串常量还没完，不能进行其他操作
		}

		if (commenting) { // 正在注释
			if (cppcomment) { // C++风格的 // 注释法，找行尾
				if (c == '\n' && i > 1 && buf[i - 2] != '\\') { // 换行了，但这里要考虑以 \ 强制转行如 comment 5
					commenting = 0; // 找到了注释结尾，注释结束
					i = 0; // 重新开始缓存
					continue;
				}
			} else { // C风格的 /* */ 注释法，找 */
				if (c == '/' && i > 1 && buf[i - 2] == '*') {
					commenting = 0;
					i = 0; // 重新开始缓存
					continue;
				}
			}
			continue; // 注释还没结束，不能进行其他操作
		}

		if (c == '"') { // 开始了字符串常量
			quoting = 1;
			continue;
		}

		if (c == '/' && i > 1 && buf[i - 2] == '/') { // 是否C++风格注释的开头 //
			commenting = 1;
			cppcomment = 1;
		} else if (c == '*' && i > 1 && buf[i - 2] == '/') { // 是否C风格注释的开头 /*
			commenting = 1;
			cppcomment = 0;
		}

		if (commenting && i > 1) { // 这里可以省略 i > 1，因为根据上一段代码，commenting=1 时已经判断过i>1了。但编译器会警告，因此写上了。
			// 输出之前缓存的内容，并重新开始缓存
			buf[i - 2] = '\0'; // 不要输出 // 或 /*
			printf(buf);
			i = 0; // 重新开始缓存
			continue;
		}

		if (c == '\n') { // 换行了，输出缓存内容并重新开始缓存
			buf[i] = '\0';
			printf(buf);
			i = 0;
		}
	}

	// 考虑读完了但文件结尾没有换行
	buf[i] = '\0';
	printf(buf); // 完结撒花
}

// 使用状态机
enum Status {
	NORMAL,
	QUOTING,
	C_COMMENTING,
	CPP_COMMENTING,
};

void rm_comment2()
{
	char buf[MAX_CACHE];
	int c, i = 0;
	enum Status status = NORMAL;

	while ((c = getchar()) != EOF && i < MAX_CACHE - 2) { // -2是因为循环内有可能再补 '\0' 或 '%'
		buf[i++] = c;

		switch (status) {
		case QUOTING:
			if (c == '"' && i > 1 && buf[i - 2] != '\\') { // 找到了字符串常量的结尾引号
				status = NORMAL;
			} else if (c == '%') { // 我们自己要输出字符串，如果字符串包含%转义，直接传给printf会缺少参数
				buf[i++] = '%';
			}
			break;
		case C_COMMENTING:
			if (c == '/' && i > 1 && buf[i - 2] == '*') {
				status = NORMAL; // 找到了注释结尾，注释结束
				i = 0; // 重新开始缓存
			}
			break;
		case CPP_COMMENTING:
			if (c == '\n' && i > 1 && buf[i - 2] != '\\') { // 换行了，但这里要考虑以 \ 强制转行如 comment 5
				status = NORMAL; // 找到了注释结尾，注释结束
				i = 0; // 重新开始缓存
			}
			break;
		default:
			switch (c) {
			case '"':
				status = QUOTING;
				break;
			case '/':
				if (i > 1 && buf[i - 2] == '/') {
					status = CPP_COMMENTING;
				}
				break;
			case '*':
				if (i > 1 && buf[i - 2] == '/') {
					status = C_COMMENTING;
				}
				break;
			case '\n':
				buf[i] = '\0';
				printf(buf);
				i = 0;
				break;
			}

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

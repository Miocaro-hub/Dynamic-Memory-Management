#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//3.常见的动态内存错误

//(1).对NULL的解引用操作
int main()
{
	int* p = (int*)malloc(40);

	//没有进行判断,万一malloc失败了,此时的p就被赋值为空指针
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		*(p + i) = i;
	}
	free(p);
	p = NULL;
	return 0;
}

//(2).对动态开辟空间的越界访问
int main()
{
	int* p = (int*)malloc(5 * sizeof(int));
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		int i = 0;
		for (i = 0; i < 10; i++)  //此时造成了越界访问,malloc中只定义了5个函数,而此时却循环10次
		{
			*(p + i) = i;
		}
	}
	free(p);
	p = NULL;
	return 0;
}

//(3).对非动态开辟内存使用free释放
int main()
{
	int a = 10;
	int* p = &a;
	*p = 20;
	free(p);  //a存在于栈区,不是动态内存开辟的
	p = NULL;
	return 0;
}

//(4).使用free释放一块动态内存的一部分
int main()
{
	int* p = (int*)malloc(40);
	if (p == NULL);
	{
		return 0;
	}
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		*p++ = i;
	}
	free(p);  //此时p所指向的空间不是起始位置指向的空间,此时的释放是不完整的
	p = NULL;
	return 0;
}

//(5).对同一块动态内存多次释放
int main()
{
	int* p = (int*)malloc(40);
	if (p == NULL);
	{
		return 0;
	}
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		*(p + i) = i;
	}
	free(p);
	//.......
	free(p);  //多次释放,其实只要一开始释放完之后就将p置为空指针,p == NULL,后边再释放也没什么卵事
	return 0;
}

//(6).动态开辟内存忘记释放(内存泄漏)
#include<windows.h>
int main()
{
	while (1)
	{
		malloc(1);  //一直开辟空间但不回收,会一直占用着内存
		Sleep(1000);
	}
	return 0;
}
//忘记释放不再使用的动态开辟的空间会造成内存泄漏.切记:动态开辟的空间一定要释放,并且正确释放
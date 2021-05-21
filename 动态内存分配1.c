#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

//动态内存管理
//本章重点:
//1.为什么存在动态内存分配
//2.动态内存函数的介绍:malloc  free  calloc  realloc
//3.常见的动态内存错误
//4.几个经典的笔试题
//5.柔性数组


//1.为什么存在动态内存分配

//当前我们知道的内存的使用方式:
//(1).创建一个变量
int a = 10; //局部变量 - 栈区
int g_a = 10; //全局变量 - 静态区

//(2).创建一个数组
int arr[10]; //局部数组 - 栈区,全局数组 - 静态区

struct S
{
	char name[20];
	int age;
};
int main()
{
	struct S arr[50];
	//此时就会出现一个状况
	//若全班只有30个学生,arr数组有50个元素就会造成浪费
	//若全班有60个学生,arr数组的容量就会不够
	return 0;
}

//这两种开辟空间的方式有两个特点:
//(1).空间开辟大小是固定的
//(2).数组在申明的时候,必须指定数组的长度,它所需要的内存在编译时分配
//但是对于空间的需求,不仅仅是上述的情况,有时候我们需要的空间大小在程序运行的时候才能知道,
//那数组的编译时开辟空间的方式就不能满足了,这时候只能试试动态内存开辟了



//2.动态内存函数的介绍
//malloc和free

//C语言提供了一个动态内存开辟的函数: void* malloc(size_t size);
//这个函数向内存申请一块连续可用的空间,并返回指向这块空间的指针
//如果开辟成功,则返回一个指向开辟好空间的指针
//如果开辟失败,则返回一个NULL指针,因为malloc的返回值一定要做检查
//返回值的类型是void*,所以malloc函数并不知道开辟空间的类型,具体在使用的时候使用者自己来决定
//如果参数size为0,malloc的行为是标准未定义的,取决于编译器

//C语言提供了另外一个函数free,专门是用来做动态内存的释放和回收的,函数原型如下:
//void free(void* ptr);

int main()
{
	//向内存申请10个整型的空间
	int* p = (int*)malloc(10 * sizeof(int));
	if (p == NULL)
	{
		//打印错误原因
		printf("%s\n", strerror(errno));
	}
	else
	{
		//正常使用空间
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			*(p + i) = i;
		}
		for (i = 0; i < 10; i++)
		{
			printf("%d ", *(p + i));
		}
	}
	//当动态申请的空间不再使用的时候
	//就应该还给操作系统

    //free函数用来释放动态开辟的内存
	//如果参数ptr指向的空间不是动态开辟的,那free函数的行为是未定义的
	//如果参数ptr是NULL指针,则函数什么事都不用做
	free(p);

	p = NULL;
	return 0;
}


//calloc
//C语言还提供了一个函数叫calloc,calloc函数也用来动态内存分配,原型如下：
//void* calloc(size_t num,size_t size);
//函数的功能是为num个大小为size的元素开辟一块空间,并且把空间的每个字节初始化为0
//与函数malloc的区别只在于calloc会在返回地址之前把申请的空间的每个字节初始化为全0

int main()
{
	int* p  = (int*)calloc(10, sizeof(int));
	if (p == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	else
	{
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			printf("%d ", *(p + i));
		}
	}
	//释放空间
	//free函数是用来释放动态开辟空间的
	return 0;
}


//realloc - 调整动态开辟内存空间的大小
//realloc函数的出现让动态内存管理更加灵活
//我们有时候会发现过去申请的空间太小或太大,为了合理时候的内存,我们会对内存的大小做灵活的调整
//realloc函数就可以做到对动态开辟内存大小的调整,函数原型如下:
//void* realloc(void* ptr , size_t size);

int main()
{
	int* p = (int*)malloc(20);
	if (p == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	else
	{
		int i = 0;
		for (i = 0; i < 5; i++)
		{
			*(p + i) = i;
		}
	}
	//使用malloc开辟的20个字节空间
	//假设这里,20个字节不能满足我们的使用了
	//我们希望可以有40个字节的空间
	//这里就可以使用realloc来调整动态开辟的内存

	//realloc使用时的注意事项:
	//
	int* p2 = realloc(p, 40);
	int i = 0;
	for (i = 5; i < 10; i++)
	{
		*(p2 + i) = i;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", *(p2 + 1));
	}
	return 0;
}
//63 第一部分 26：00结束

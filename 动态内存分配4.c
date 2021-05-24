#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//5.柔性数组
//C99中,结构中的最后一个元素允许是未知大小的数组,这就叫做柔性数组成员

//柔性数组的特点:
//结构中的柔性数组成员前面必须至少一个其他成员
//sizeof返回的这种结构大小不包括柔性数组的内存
//包含柔性数组成员的结构体用malloc()函数进行内存的动态分配,并且分配的内存应该大于结构的大小,以适应柔性数组的预期大小

struct S
{
	int n;
	int arr[];  //结构体最后一个成员,称为柔性数组成员,可以是未知大小  int a[0]和int a[]等效,但在不同的编译器下可能会报警告,适当转换就好
	//此时数组的内存为4个字节,可见此时的柔性数组并没有占用空间
};
int main()
{
	struct S* ps = (struct S*)malloc(sizeof(struct S) + 5 * sizeof(int));
	//24个字节,前4个字节为n,后面20个字节为5个整型
	ps->n = 100;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ps->arr[i] = i;  //0,1,2,3,4
	}
	struct S* ptr = malloc(ps, 44);
	if (ptr != NULL)
	{
		ps = ptr;
	}
	for(i=5;i<10;i++)
	{
		ps->arr[i] = i;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", ps->arr[i]);
	}
	//释放
	free(ps);
	ps = NULL;
	return 0;
}


struct S
{
	int n;
	int* arr;  //指针的方式
};
int main()
{
	struct S* ps = (struct S*)malloc(sizeof(struct S));
	ps->arr = malloc(5 * sizeof(int));
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ps->arr[i] = i;
	}
	for (i = 0; i < 5; i++)
	{
		printf("%d ", ps->arr[i]);
	}

	//调整大小
	int* ptr = realloc(ps->arr, 10 * sizeof(int));
	if (ptr != NULL)
	{
		ps->arr = ptr;
	}
	for (i = 5; i < 10; i++)
	{
		ps->arr[i] = i;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", ps->arr[i]);
	}

	//释放内存
	free(ps->arr);
	ps->arr = NULL;
	free(ps);
	ps = NULL;
	return 0;
}

//以上两个代码皆可实现结构体中的动态内存开辟
//柔性数组的好处:
//1.方便内存释放 - 如果我们的代码是在一个给别人用的函数中,你在里面做了二次内存分配,并把整个结构体返回给用户,用户很难知道结构体内的成员也需要free
//2.有利于访问速度 - 连续的内存有益于提高访问速度,也有益于减少内存碎片


//推荐网站:COOL SHELL酷壳

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//4.几个经典的笔试题

//题目一:运行Test函数会有什么样的结果
void GetMemory(char* p)
{
	p = (char*)malloc(100);  //GetMemory函数返回之后,动态开辟内存尚未释放,并且无法找到,所以会造成内存泄漏
}
void Test(void)
{
	char* str = NULL;
	GetMemory(str);  //str以直传的形式给p,p是str的一个临时拷贝,出了GetMemory函数之后销毁,所以此时的str还是空指针NULL
	strcpy(str, "hello world");  //程序崩溃,并没有成功开辟空间
	printf(str);
}
int main()
{
	Test();
	return 0;
}
//1.运行代码程序会出现崩溃的现象
//2.程序存在内存泄漏的问题


//题目一改正1:
void GetMemory(char** p)
{
	*p = (char*)malloc(100);
}
void Test(void)
{
	char* str = NULL;
	GetMemory(&str);  
	strcpy(str, "hello world"); 
	printf(str);
	free(str);
	str = NULL;
}
int main()
{
	Test();
	return 0;
}

//题目一改正2:
char* GetMemory(char* p)
{
	p = (char*)malloc(100); 
	return p;
}
void Test(void)
{
	char* str = NULL;
	str = GetMemory(str); 
	strcpy(str, "hello world");  
	printf(str);
	free(str);
	str = NULL;
}
int main()
{
	Test();
	return 0;
}


//题目二:运行Test函数会有什么样的结果?
char* GetMemory(void)   //返回栈空间的地址的问题
{
	char p[] = "hello world";  //栈区
	return p;  //地址虽然返回了,但p数组为局部变量,出了GetMemory函数就被销毁,此时地址指向的内容变得不确定,就是非法访问内存,最后打印的也为随机值
}
void Test(void)
{
	char* str = NULL;
	str = GetMemory();
	printf(str);
}
int main()
{
	Test();
	return 0;
}

//题目二改正:
char* GetMemory(void)
{
	static char p[] = "hello world";  //static修饰函数的局部变量: 特点:有默认值0,只执行一次,运行一开始就开辟了内存,内存放在全局(此时的p[]就放在了静态区)
	return p;  
}
void Test(void)
{
	char* str = NULL;
	str = GetMemory();
	printf(str);
}
int main()
{
	Test();
	return 0;
}


//题目三:运行Test函数会有什么样的结果
void GetMemory(char** p, int num)
{
	*p = (char*)malloc(num);
}
void Test(void)
{
	char* str = NULL;
	GetMemory(&str, 100);
	strcpy(str, "hello");
	printf(str);  //忘记释放动态开辟的内存,导致内存泄漏
}
int main()
{
	Test();
	return 0;
}
//输出hello,但存在内存泄漏的现象


//题目四:运行Test函数会有什么样的结果?
void Test(void)
{
	char* str = (char*)malloc(100);
	strcpy(str, "hello");
	free(str);  //提前释放,str成为野指针,下面再使用就是非法访问内存
	if (str != NULL)  //free释放str指向的空间后,并不会把str置为NULL,才是的判断无意义
	{
		strcpy(str, "world");
		printf(str);
	}
}
int main()
{
	Test();
	return 0;
}
//篡改动态内存区的内容,后果难以预料,非常危险



//C/C++程序的内存开辟
//内存中区的分别:内核空间(用户代码不能读写),栈(向下增长),内存映射段(文件映射,动态库,匿名映射),堆(向上增长),数据段(全局数据,静态数据),代码段(可执行代码/只读常量)
//1.栈区(stack):在执行函数时,函数内局部变量的存储单元都可以在栈上创建,函数执行结束时这些存储单元自动被释放.
//              栈内存分配运算内置于处理器的指令集中,效率很高,但是分配的内存容量有限.
//              栈区主要存放运行函数而分配的局部变量,函数参数,返回数据,返回地址等
//2.堆区(heap):一般由程序员分配释放,若程序员不释放,程序结束时可能由OS回收,分配方式蕾丝于链表
//3.数据段(静态区)(static):存放全局变量,静态数据,程序结束后由系统释放
//4.代码段:存放函数体(类成员函数和全局函数)的二进制代码

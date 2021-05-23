#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//4.��������ı�����

//��Ŀһ:����Test��������ʲô���Ľ��
void GetMemory(char* p)
{
	p = (char*)malloc(100);  //GetMemory��������֮��,��̬�����ڴ���δ�ͷ�,�����޷��ҵ�,���Ի�����ڴ�й©
}
void Test(void)
{
	char* str = NULL;
	GetMemory(str);  //str��ֱ������ʽ��p,p��str��һ����ʱ����,����GetMemory����֮������,���Դ�ʱ��str���ǿ�ָ��NULL
	strcpy(str, "hello world");  //�������,��û�гɹ����ٿռ�
	printf(str);
}
int main()
{
	Test();
	return 0;
}
//1.���д���������ֱ���������
//2.��������ڴ�й©������


//��Ŀһ����1:
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

//��Ŀһ����2:
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


//��Ŀ��:����Test��������ʲô���Ľ��?
char* GetMemory(void)   //����ջ�ռ�ĵ�ַ������
{
	char p[] = "hello world";  //ջ��
	return p;  //��ַ��Ȼ������,��p����Ϊ�ֲ�����,����GetMemory�����ͱ�����,��ʱ��ַָ������ݱ�ò�ȷ��,���ǷǷ������ڴ�,����ӡ��ҲΪ���ֵ
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

//��Ŀ������:
char* GetMemory(void)
{
	static char p[] = "hello world";  //static���κ����ľֲ�����: �ص�:��Ĭ��ֵ0,ִֻ��һ��,����һ��ʼ�Ϳ������ڴ�,�ڴ����ȫ��(��ʱ��p[]�ͷ����˾�̬��)
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


//��Ŀ��:����Test��������ʲô���Ľ��
void GetMemory(char** p, int num)
{
	*p = (char*)malloc(num);
}
void Test(void)
{
	char* str = NULL;
	GetMemory(&str, 100);
	strcpy(str, "hello");
	printf(str);  //�����ͷŶ�̬���ٵ��ڴ�,�����ڴ�й©
}
int main()
{
	Test();
	return 0;
}
//���hello,�������ڴ�й©������


//��Ŀ��:����Test��������ʲô���Ľ��?
void Test(void)
{
	char* str = (char*)malloc(100);
	strcpy(str, "hello");
	free(str);  //��ǰ�ͷ�,str��ΪҰָ��,������ʹ�þ��ǷǷ������ڴ�
	if (str != NULL)  //free�ͷ�strָ��Ŀռ��,�������str��ΪNULL,���ǵ��ж�������
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
//�۸Ķ�̬�ڴ���������,�������Ԥ��,�ǳ�Σ��



//C/C++������ڴ濪��
//�ڴ������ķֱ�:�ں˿ռ�(�û����벻�ܶ�д),ջ(��������),�ڴ�ӳ���(�ļ�ӳ��,��̬��,����ӳ��),��(��������),���ݶ�(ȫ������,��̬����),�����(��ִ�д���/ֻ������)
//1.ջ��(stack):��ִ�к���ʱ,�����ھֲ������Ĵ洢��Ԫ��������ջ�ϴ���,����ִ�н���ʱ��Щ�洢��Ԫ�Զ����ͷ�.
//              ջ�ڴ�������������ڴ�������ָ���,Ч�ʺܸ�,���Ƿ�����ڴ���������.
//              ջ����Ҫ������к���������ľֲ�����,��������,��������,���ص�ַ��
//2.����(heap):һ���ɳ���Ա�����ͷ�,������Ա���ͷ�,�������ʱ������OS����,���䷽ʽ��˿������
//3.���ݶ�(��̬��)(static):���ȫ�ֱ���,��̬����,�����������ϵͳ�ͷ�
//4.�����:��ź�����(���Ա������ȫ�ֺ���)�Ķ����ƴ���

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//3.�����Ķ�̬�ڴ����

//(1).��NULL�Ľ����ò���
int main()
{
	int* p = (int*)malloc(40);

	//û�н����ж�,��һmallocʧ����,��ʱ��p�ͱ���ֵΪ��ָ��
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		*(p + i) = i;
	}
	free(p);
	p = NULL;
	return 0;
}

//(2).�Զ�̬���ٿռ��Խ�����
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
		for (i = 0; i < 10; i++)  //��ʱ�����Խ�����,malloc��ֻ������5������,����ʱȴѭ��10��
		{
			*(p + i) = i;
		}
	}
	free(p);
	p = NULL;
	return 0;
}

//(3).�ԷǶ�̬�����ڴ�ʹ��free�ͷ�
int main()
{
	int a = 10;
	int* p = &a;
	*p = 20;
	free(p);  //a������ջ��,���Ƕ�̬�ڴ濪�ٵ�
	p = NULL;
	return 0;
}

//(4).ʹ��free�ͷ�һ�鶯̬�ڴ��һ����
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
	free(p);  //��ʱp��ָ��Ŀռ䲻����ʼλ��ָ��Ŀռ�,��ʱ���ͷ��ǲ�������
	p = NULL;
	return 0;
}

//(5).��ͬһ�鶯̬�ڴ����ͷ�
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
	free(p);  //����ͷ�,��ʵֻҪһ��ʼ�ͷ���֮��ͽ�p��Ϊ��ָ��,p == NULL,������ͷ�Ҳûʲô����
	return 0;
}

//(6).��̬�����ڴ������ͷ�(�ڴ�й©)
#include<windows.h>
int main()
{
	while (1)
	{
		malloc(1);  //һֱ���ٿռ䵫������,��һֱռ�����ڴ�
		Sleep(1000);
	}
	return 0;
}
//�����ͷŲ���ʹ�õĶ�̬���ٵĿռ������ڴ�й©.�м�:��̬���ٵĿռ�һ��Ҫ�ͷ�,������ȷ�ͷ�
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//5.��������
//C99��,�ṹ�е����һ��Ԫ��������δ֪��С������,��ͽ������������Ա

//����������ص�:
//�ṹ�е����������Աǰ���������һ��������Ա
//sizeof���ص����ֽṹ��С����������������ڴ�
//�������������Ա�Ľṹ����malloc()���������ڴ�Ķ�̬����,���ҷ�����ڴ�Ӧ�ô��ڽṹ�Ĵ�С,����Ӧ���������Ԥ�ڴ�С

struct S
{
	int n;
	int arr[];  //�ṹ�����һ����Ա,��Ϊ���������Ա,������δ֪��С  int a[0]��int a[]��Ч,���ڲ�ͬ�ı������¿��ܻᱨ����,�ʵ�ת���ͺ�
	//��ʱ������ڴ�Ϊ4���ֽ�,�ɼ���ʱ���������鲢û��ռ�ÿռ�
};
int main()
{
	struct S* ps = (struct S*)malloc(sizeof(struct S) + 5 * sizeof(int));
	//24���ֽ�,ǰ4���ֽ�Ϊn,����20���ֽ�Ϊ5������
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
	//�ͷ�
	free(ps);
	ps = NULL;
	return 0;
}


struct S
{
	int n;
	int* arr;  //ָ��ķ�ʽ
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

	//������С
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

	//�ͷ��ڴ�
	free(ps->arr);
	ps->arr = NULL;
	free(ps);
	ps = NULL;
	return 0;
}

//������������Կ�ʵ�ֽṹ���еĶ�̬�ڴ濪��
//��������ĺô�:
//1.�����ڴ��ͷ� - ������ǵĴ�������һ���������õĺ�����,�����������˶����ڴ����,���������ṹ�巵�ظ��û�,�û�����֪���ṹ���ڵĳ�ԱҲ��Ҫfree
//2.�����ڷ����ٶ� - �������ڴ���������߷����ٶ�,Ҳ�����ڼ����ڴ���Ƭ




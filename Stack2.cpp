/*��������� ����, ���������� ������� 
��������� �������� ���������� ���� � �������� �������.*/
#include <iostream>
#include <conio.h>
#include <stdarg.h>
//---------------------------------------------------------
struct Stack
{
	char data;
	Stack *last;
};
//---------------------------------------------------------
struct StackInStack
{
	Stack *slovo;
	StackInStack *last;
};
typedef Stack* (*pS)(Stack*);//��������� ��� �������� �� �������
//---------------------------------------------------------
inline Stack* Start(Stack* stack)
{
	return NULL;
}
//---------------------------------------------------------
Stack* Stack_push(Stack* stack,char ch)
{
	Stack* new_stack=new Stack;//������� ������� �� ���� ������� �����
	new_stack->last=stack;//����� �� �������� last ����� �� ��������� �������
	new_stack->data=ch;//������� ��� � ���� �������
	stack=new_stack;//�������� ����� ���� �������
	new_stack=NULL;//������� ���������� ��������
	return stack;//�������� �������� �� ���� �������
}
//---------------------------------------------------------
Stack* Stack_push(Stack* stack,char* ch)
{
	Stack* new_stack=new Stack;//������� ������� �� ���� ������� �����
	new_stack->last=stack;//����� �� �������� last ����� �� ��������� �������
	new_stack->data=*ch;//������� ��� � ���� �������
	stack=new_stack;//�������� ����� ���� �������
	new_stack=NULL;//������� ���������� ��������
	return stack;//�������� �������� �� ���� �������
}
//---------------------------------------------------------
Stack* Stack_Slovo(int i,...)
{
	Stack* stack=NULL;//�������� ����
	va_list p;//�������� �������� �� ������� �������
	va_start(p,i);//��������� �������� �� ������� ��������� ���� �������
	for(int j=(int)1;j<=i;j++)
	{//������ ���������
		char* ch=(char*)p;
		stack=Stack_push(stack,ch);//������� ������� � ����
		va_arg(p,char);//��� �� ���������� ���������
	}
	va_end(p);//�������� ��������
	return stack;
}
//---------------------------------------------------------
StackInStack* StackInStack_push(StackInStack *SIS,Stack *stack)
{
	StackInStack* new_SIS=new StackInStack;//������� ������ �� ����� ������� �����
	new_SIS->last=SIS;//������� ������ ������������ ��������
	new_SIS->slovo=stack;//������ ������ �����(�����)
	SIS=new_SIS;//������� ���� �������
	new_SIS=NULL;//�������� ��������
	return SIS;//�������� ���� �������
}
//---------------------------------------------------------
Stack* clear(Stack * stack)
{
	if (stack==NULL)
		return NULL;//���� ���� ��� ������ �������
	Stack* del_stack;
	while(true)
	{
		if (stack->last!=NULL)//��������� �� �� ��������� ���� �� ��������� ��������
		{
			del_stack=stack;//������ ������ ����� ��� ������� ��������
			stack=stack->last;//�������� ������������� �� ��������� �������
			std::cout<<del_stack->data;
			delete del_stack;//�������� ������
			del_stack=NULL;//������ ������ ����� ��� ������� ��������
		}
		else 
		{
			std::cout<<stack->data;
			delete stack;//�������� ������
			return NULL;//�������� ��������
		}
	}
}
//---------------------------------------------------------
StackInStack* StackInStack_clear(StackInStack* SIS,pS p1)
{
	if (SIS==NULL)
		return NULL;//���� ���� ��� ������ �������
	StackInStack* del_SIS;
	while(true)
	{
		if (SIS->last!=NULL)//��������� �� �� ��������� ������ ��������� ��������
		{
			del_SIS=SIS;//������ ������ ����� ��� ������� ��������
			SIS=SIS->last;//��������� ������������� �� ��������� �������
			del_SIS->slovo=p1(del_SIS->slovo);//del_SIS->slovo=clear(del_SIS->slovo);//�������� ������ � �����
			std::cout<<' ';
			delete del_SIS;//�������� ������
			del_SIS=NULL;//�������� ������
		}
		else 
		{
			SIS->slovo=clear(SIS->slovo);//�������� ������ � �� �����
			delete SIS;//�������� ������
			return NULL;//�������� ��������
		}
	}
}
//---------------------------------------------------------
void keep_window_open()
{
	std::cin.clear();
	char ch;
	std::cout<<"Wedit sumvol dla zavershena\n";
	std::cin>>ch;
}
//---------------------------------------------------------
int main()
{
	Stack* stack;
	StackInStack *SIS;
	stack=NULL;
	SIS=NULL;//�������� ���������
	pS p1=clear;
	char ch;
	std::cout<<"Wedit recenna, dla zavershena wedit '.'\n";
	while(std::cin.get(ch))//��������� ������ �� ������ �������
	{
		if (isalpha(ch))
		{//��������� �� ���� ������� ����� ��������� ��� �������� ������� ��� ' '
			stack=Stack_push(stack,ch);//������� ������ � ����
		}
		else if (ch==' ')//��������� �� ����� ����������
		{
			SIS=StackInStack_push(SIS,stack);//�������� �����(����) � ����
			stack=NULL;//�������� ��������, ��� �� ��� �� ������� ������� ���
		}
		else if (ch=='.')
		{
			SIS=StackInStack_push(SIS,stack);//������� ������ ������� ����� � ����
			stack=Stack_Slovo(7,':','e','g','n','a','h','C');
			SIS=StackInStack_push(SIS,stack);
			stack=NULL;
			break;//������� ����������
		}
	}
	SIS= StackInStack_clear(SIS,p1);//�������� ������
	std::cout<<std::endl;
	keep_window_open();//�������� ������
	getch();
	return 0;
}

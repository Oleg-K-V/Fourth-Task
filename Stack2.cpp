/*Используя стек, напечатать символы 
некоторой величины строкового типа в обратном порядке.*/
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
typedef Stack* (*pS)(Stack*);//створюємо тип вказівник на функцію
//---------------------------------------------------------
inline Stack* Start(Stack* stack)
{
	return NULL;
}
//---------------------------------------------------------
Stack* Stack_push(Stack* stack,char ch)
{
	Stack* new_stack=new Stack;//виділяєм памятьь під нову вершину стека
	new_stack->last=stack;//кажем що вказівник last вказує на попередню вершину
	new_stack->data=ch;//записуєм дані в нову вершину
	stack=new_stack;//Присвоюю стеку нову вершину
	new_stack=NULL;//зануляє непотрібний вказвіник
	return stack;//повертаєм вказвіник на нову вершину
}
//---------------------------------------------------------
Stack* Stack_push(Stack* stack,char* ch)
{
	Stack* new_stack=new Stack;//виділяєм памятьь під нову вершину стека
	new_stack->last=stack;//кажем що вказівник last вказує на попередню вершину
	new_stack->data=*ch;//записуєм дані в нову вершину
	stack=new_stack;//Присвоюю стеку нову вершину
	new_stack=NULL;//зануляє непотрібний вказвіник
	return stack;//повертаєм вказвіник на нову вершину
}
//---------------------------------------------------------
Stack* Stack_Slovo(int i,...)
{
	Stack* stack=NULL;//створюєм стек
	va_list p;//оголошую вказівник на початок паретрів
	va_start(p,i);//перекидую вказівник на парамтр наступний після першого
	for(int j=(int)1;j<=i;j++)
	{//зчитую параметри
		char* ch=(char*)p;
		stack=Stack_push(stack,ch);//парисую парамтр в стек
		va_arg(p,char);//іду до наступного параметра
	}
	va_end(p);//видаляєм вказівник
	return stack;
}
//---------------------------------------------------------
StackInStack* StackInStack_push(StackInStack *SIS,Stack *stack)
{
	StackInStack* new_SIS=new StackInStack;//виділяєм память під новий елемент стеку
	new_SIS->last=SIS;//записуєм адресу попереднього елементу
	new_SIS->slovo=stack;//зчитуєм адресу слова(стека)
	SIS=new_SIS;//записуєм нову вершину
	new_SIS=NULL;//зануляєм вказівник
	return SIS;//повертаєм нову вершину
}
//---------------------------------------------------------
Stack* clear(Stack * stack)
{
	if (stack==NULL)
		return NULL;//якщо стек уже пустий виходим
	Stack* del_stack;
	while(true)
	{
		if (stack->last!=NULL)//перевіряєм чи не вивільнили стек до останього елемента
		{
			del_stack=stack;//зчитуєм адресу памяті яку потрібно звільнити
			stack=stack->last;//вказівник перепризначаєм на попередній елемент
			std::cout<<del_stack->data;
			delete del_stack;//звільняєм память
			del_stack=NULL;//зчитуєм адресу памяті яку потрібно звільнити
		}
		else 
		{
			std::cout<<stack->data;
			delete stack;//звільняєм память
			return NULL;//зануляєм вказвіник
		}
	}
}
//---------------------------------------------------------
StackInStack* StackInStack_clear(StackInStack* SIS,pS p1)
{
	if (SIS==NULL)
		return NULL;//якщо стек уже пустий виходим
	StackInStack* del_SIS;
	while(true)
	{
		if (SIS->last!=NULL)//перевіряєм чи не вивільнили стекдо останього елемента
		{
			del_SIS=SIS;//зчитуєм адресу памяті яку потрібно звільнити
			SIS=SIS->last;//вказівнику переприсвоюєм на попередній елемент
			del_SIS->slovo=p1(del_SIS->slovo);//del_SIS->slovo=clear(del_SIS->slovo);//звільняєм память з слова
			std::cout<<' ';
			delete del_SIS;//звільняєм память
			del_SIS=NULL;//зануляєм адресу
		}
		else 
		{
			SIS->slovo=clear(SIS->slovo);//звільняєм память з під слова
			delete SIS;//звільняєм память
			return NULL;//зануляєм вказвіник
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
	SIS=NULL;//Обнуляєм вказвіники
	pS p1=clear;
	char ch;
	std::cout<<"Wedit recenna, dla zavershena wedit '.'\n";
	while(std::cin.get(ch))//почергово зчитуєм всі введені символи
	{
		if (isalpha(ch))
		{//перевіряєм чи було введено букву верхнього або нижнього регістра крім ' '
			stack=Stack_push(stack,ch);//заносим символ в стек
		}
		else if (ch==' ')//перевіряєм чи слово закінчилося
		{
			SIS=StackInStack_push(SIS,stack);//заносимо слово(стек) в стек
			stack=NULL;//зануляєм вказвіник, щоб він нам не спортив занесені дані
		}
		else if (ch=='.')
		{
			SIS=StackInStack_push(SIS,stack);//заносим остане зчитане слово в стек
			stack=Stack_Slovo(7,':','e','g','n','a','h','C');
			SIS=StackInStack_push(SIS,stack);
			stack=NULL;
			break;//закінчуєм зчитування
		}
	}
	SIS= StackInStack_clear(SIS,p1);//звільняєм память
	std::cout<<std::endl;
	keep_window_open();//завершуєм роботу
	getch();
	return 0;
}

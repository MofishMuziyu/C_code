#ifndef _NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

struct queuenode
{
	struct queuenode *next; /*next为指向下一结点的指针*/
	ElementType data;
};

typedef struct queuenode Queuenode;

Queuenode* CreateQueue();
void In(Queuenode** rear, ElementType x);
ElementType Out(Queuenode** rear);

Queuenode* CreateQueue()
{
	Queuenode*  rear =(Queuenode*)malloc(sizeof (Queuenode));
	rear->data = 0;
	rear->next = NULL;
	return rear;
}

void In(Queuenode** rear, ElementType x)
{
	if ((*rear)->next == NULL){
		(*rear)->next = *rear;
		(*rear)->data = x;
	}
	
	Queuenode *tmp = (Queuenode*)malloc(sizeof (Queuenode));
	tmp->data = x;
	tmp->next = (*rear)->next;
	(*rear)->next = tmp;
}

ElementType Out(Queuenode** rear)
{
	int result;
	Queuenode *tmp = (*rear)->next;
	if ((*rear)->next==NULL){
		printf("The node list is empty");
	}
	result = (*rear)->next->data;
	(*rear)->next = (*rear)->next->next;
	free(tmp);

	return result;
}
#endif
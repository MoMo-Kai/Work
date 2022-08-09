#include<stdio.h> 
#include<stdlib.h> 

//创建链表单元结构 
typedef struct _node{
	int value;
	struct _node *next;
}Node;

typedef struct _list{
	//记录链表的头和尾 
	Node *head;
//	Node *tail;
}List;

void add(List *pList, int number);
void print(List *pList);

int main(int argc , char const *argv[])
{
	List list;
	int number;
	list.head = list.tail = NULL;
	do{
		scanf("%d",&number);
		if(number != -1 ){
			add(&list,number);
		}
	}while(number != -1 );
	print(&list);
	scanf("%d",&number);
	//链表的搜索 
	Node *p;
	int isFound=0;
	for(p=list.head; p ; p=p->next){
		if(p->value == number){
			printf("找到了");
			isFound=1;
			break; 
		}
	}
	if(isFound==0){
		printf("没找到"); 
	}
	//链表的删除
	Node *q; 
	for(q=NULL,p=list.head; p ;q=p,p=p->next){
		if(p->value == number){
			if(q){
				q->next=p->next;	
			}
			else{
				list.head=p->next;
			}
			free(p);
			break; 
		}
	}
	//链表的清除 
	for(p=list.head; p ;p=q){
		q=p->next;
		free(p);
	}
	return 0;
}

void add(List *pList, int number){
	//add to linked-list
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;
	//方法一 
/*  //find the last	
	Node *last = pList->head;
	if(last){
		while(last->next){
			last = last->next;
			}
		//attach
		last->next = p;
	}
	else{
		pList->head = p;
	}
*/
	//方法二 
	if(pList->tail){
		pList->tail->next = p;
		pList->tail = p;
	}
	else{
		pList->tail = pList->head = p;
	}			
}

void print(List *pList){
	Node *p;
	for(p=pList->head; p ;p = p->next){
		printf("%d\t",p->value);
	}
	printf("\n");
}
	

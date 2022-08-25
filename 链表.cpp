#include<stdio.h> 
#include<stdlib.h> 

//��������Ԫ�ṹ 
typedef struct _node{
	int value;
	struct _node *next;
}Node;

typedef struct _list{
	//��¼�����ͷ��β 
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
	//��������� 
	Node *p;
	int isFound=0;
	for(p=list.head; p ; p=p->next){
		if(p->value == number){
			printf("�ҵ���");
			isFound=1;
			break; 
		}
	}
	if(isFound==0){
		printf("û�ҵ�"); 
	}
	//�����ɾ��
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
	//�������� 
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
	//����һ 
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
	//������ 
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
	

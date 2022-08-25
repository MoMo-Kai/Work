#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#define MAX 50  //�༶�������Ϊ50 

typedef struct _score{
	int Math;  //�ߵ���ѧ 
	int English;  //��ѧӢ�� 
	int Physics;  //��ѧ���� 
	int History;  //���ִ�ʷ 
	int Computer;  //������γ� 
	int total;  //�ܳɼ�
	int rank;  //������ 
}Score; 

typedef struct _student{
	short state;  //ѧ��״̬(1����/0ע��) 
	int number;  //ѧ��
	char name[9];  //����
	char sex[2];  //�Ա�
	int age;  //����
	char origin[15];  //����
	int grade;  //�꼶
	char major[15];  //רҵ
	int _class;  //�༶ 
	Score score;  //���Ƴɼ� 
}Student;

//�����溯�� 
void add_data();  //ѧ����Ӻ��� 
void modify_data();  //ѧ���޸ĺ��� 
void search_data();  //ѧ����ѯ���� 
	//ѧ����ѯ�Ӻ���
	void search_data_by_person();  //�����˲�ѯ
	void search_data_by_class();  //���༶��ѯ 
void cancel_data();  //ѧ��ע������ 
void score_manage();  //�ɼ������� 
	//�ɼ������Ӻ��� 
	void grade_input();  //�ɼ�¼�뺯�� 
	void grade_inquire();  //�ɼ���ѯ���� 
		//�ɼ���ѯ�Ӻ��� 
		void grade_inquire_by_class();  //���༶��ѯ 
		void grade_inquire_by_subject();  //����Ŀ��ѯ 

FILE *fp=NULL;

int main() {
	char select=' ';
	//����ļ��Ƿ�� 
	if((fp=fopen("student.txt","rb+"))==NULL) 
	{
		if((fp=fopen("student.txt","wb+"))==NULL) {
			printf("���ļ�student.txtʧ�ܣ�");
			exit(1);	
		} 	
	}
	
	while(select!='0'){
		system("cls");
		//��������� 
		printf("**********С��ѧ������ϵͳ**********\n");
		printf("====================================\n");
		printf("=          1. ѧ�����             =\n");
		printf("=          2. ѧ���޸�             =\n");
		printf("=          3. ѧ����ѯ             =\n");
		printf("=          4. ѧ��ע��             =\n");
		printf("=          5. �ɼ�����             =\n"); 
		printf("=          0. ��    ��             =\n");
		printf("====================================\n");
		printf("��ѡ���������: ");
		select=getchar();
		//����ѡ����뺯�� 
		switch(select){
			case'1': add_data(); break;
   		    case'2': modify_data(); break;
			case'3': search_data(); break;
			case'4': cancel_data(); break;
			case'5': score_manage(); break;
			case'0': fclose(fp); return 0;
			default: printf("�������,���������룡\n"); break;
		}
	}
}

//ѧ����Ӻ��� 
void add_data()
{
	Student person;
	person.state=1;
	person.score.total=-1;
	char sign;
	do{
		system("cls");
		printf("************ѧ�����************\n");
		printf("******�밴��ʾ����������Ϣ******\n");
		printf("ѧ��: ");
		scanf("%ld",&person.number);
		printf("����: ");
		scanf("%s",person.name);
		printf("�Ա�(��/Ů): ");
		scanf("%s",person.sex);
		while(strcmp(person.sex,"��")!=0 && strcmp(person.sex,"Ů")!=0){
			printf("�Ա������������������: ");
			scanf("%s",person.sex);
		}
		printf("����: ");
		scanf("%d",&person.age);
		printf("����: ");
		scanf("%s",person.origin);
		printf("�꼶: ");
		scanf("%d",&person.grade);
		printf("רҵ: ");
		scanf("%s",person.major);
		printf("�༶: ");
		scanf("%d",&person._class);
		
		fseek(fp,0,SEEK_END);  //��ָ���ƶ����ļ�β��
		fwrite(&person,sizeof(Student),1,fp); 
		
		printf("=====================================\n") ;
		printf("�Ƿ������ӣ�\n");
		printf("����1����/0����: "); 
		while(getchar()!='\n'); 
		sign=getchar();
		while(sign!='1'&&sign!='0'){
			printf("�����������������(1/0): ");
			while(getchar()!='\n');
			sign=getchar();
		}
	}while(sign=='1');
}

//ѧ���޸ĺ��� 
void modify_data()
{
	Student person;
	int number;
	system("cls");
	printf("************ѧ���޸�************\n");
	printf("������Ҫ�޸ĵ�ѧ����ѧ��: ");
	scanf("%d",&number);
	
	fseek(fp,0L,SEEK_SET);
	fread(&person,sizeof(Student),1,fp);
	
	while(!feof(fp))
	{
		if(person.number==number && person.state==1) break;
		fread(&person,sizeof(Student),1,fp);
	}
	if(!feof(fp))
	{
		printf("�������ǰѧ������Ϣ:\n");
		printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","ѧ��","����","�Ա�","����","����","�꼶","רҵ","�༶");
		printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
			person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
		printf("��������º������:\n");
		printf("ѧ��: ");
		scanf("%d",&person.number);
		printf("����: ");
		scanf("%s",person.name);
		printf("�Ա�(��/Ů): ");
		scanf("%s",person.sex);
		while(strcmp(person.sex,"��")!=0 && strcmp(person.sex,"Ů")!=0){
			printf("�Ա������������������: ");
			scanf("%s",person.sex);
		}
		printf("����: ");
		scanf("%d",&person.age);
		printf("����: ");
		scanf("%s",person.origin);
		printf("�꼶: ");
		scanf("%d",&person.grade);
		printf("רҵ: ");
		scanf("%s",person.major);
		printf("�༶: ");
		scanf("%d",&person._class);
		fseek(fp,(long)-sizeof(Student),SEEK_CUR); 
		fwrite(&person,sizeof(Student),1,fp);
	}
	else
	{
		printf("�޴�ѧ�ŵ�ѧ�������Ƚ���ѧ����ӣ�\n");
	}
	system("pause");
}

//ѧ����ѯ���� 
void search_data()
{
	char menuid=' ';
	
	while(menuid!='0')
	{
		system("cls");
		printf("************ѧ����ѯ************\n");
		printf("================================\n");
		printf("          1. ����ѧ����ѯ\n");
		printf("          2. �༶ѧ����ѯ\n");
		printf("          0. ����\n");
		printf("================================\n");
		printf("��ѡ���������: ");
		menuid=getchar();
		
		switch(menuid){
			case'1': search_data_by_person(); break;
			case'2': search_data_by_class(); break;
			case'0': break; 
			default: printf("�������,���������룡\n"); break;
		}
	}
}

void search_data_by_person()
{
	Student person;
	int number;
	int sign;     
	system("cls");
	printf("������Ҫ��ѯ��ѧ����ѧ��: ");
	scanf("%d",&number);
	fseek(fp,0L,SEEK_SET); 
	fread(&person,sizeof(Student),1,fp); 
	while(!feof(fp))
	{
		if(person.number==number && person.state==1) break;
		fread(&person,sizeof(Student),1,fp);
	}
	if(!feof(fp))
	{
		printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","ѧ��","����","�Ա�","����","����","�꼶","רҵ","�༶");
		printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
			person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
	}
	else
	{
		printf("�޴�ѧ�ŵ�ѧ����\n");
	}
	system("pause");
}

void search_data_by_class()
{
	Student person;
	int class_number;
	system("cls"); 
	printf("������Ҫ��ѯ�İ༶: ");
	scanf("%d",&class_number);
	printf("%d���ѧ��ѧ��ͳ�����£�\n",class_number);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","ѧ��","����","�Ա�","����","����","�꼶","רҵ","�༶");
	fseek(fp,0L,SEEK_SET);
	fread(&person,sizeof(Student),1,fp); 
	while(!feof(fp))
	{
		if(person._class==class_number && person.state==1){
			printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
				person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
		} 
		fread(&person,sizeof(Student),1,fp);
	}
	system("pause");
}

//ѧ��ע������
void cancel_data()
{
	Student person;
	int number;
	system("cls");
	printf("********************ѧ��ע��********************\n");
	printf("��������Ҫע��ѧ����Ϣ��ѧ����ѧ��: ");
	scanf("%d",&number);
	fseek(fp,0L,SEEK_SET); 
	fread(&person,sizeof(Student),1,fp);
	while(!feof(fp))
	{
		if(person.number==number && person.state==1) break;
		fread(&person,sizeof(Student),1,fp);
	}
	if(!feof(fp))
	{
		printf("��ɾ����¼Ϊ:\n");
		printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","ѧ��","����","�Ա�","����","����","�꼶","רҵ","�༶");
		printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
			person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
		person.state=0;
		fseek(fp,(long)-sizeof(Student),SEEK_CUR); 
		fwrite(&person,sizeof(Student),1,fp);
	}
	else
	{
		printf("�޴�ѧ��ѧ�ŵ���Ϣ!\n");
	}
	system("pause");
}

//�ɼ�������
void score_manage()
{
	char menuid=' ';
	
	while(menuid!='0')
	{
		system("cls");
		printf("************�ɼ�����************\n");
		printf("================================\n");
		printf("          1. �ɼ�¼��\n");
		printf("          2. �ɼ�ͳ��\n");
		printf("          0. ����\n");
		printf("================================\n");
		printf("��ѡ���������: ");
		menuid=getchar();
		
		switch(menuid){
			case'1': grade_input(); break;
			case'2': grade_inquire(); break;
			case'0': break; 
			default: printf("�������,���������룡\n"); break;
		}
	}
}

void grade_input()
{
	Student person;
	int number;
	char sign;
	do{
		system("cls");
		printf("********************�ɼ�¼��********************\n");
		printf("��������Ҫ¼��ɼ���ѧ����ѧ��: ");
		scanf("%d",&number);
		fseek(fp,0L,SEEK_SET);
		fread(&person,sizeof(Student),1,fp); 
		while(!feof(fp))
		{
			if(person.number==number && person.state==1) break;
			fread(&person,sizeof(Student),1,fp);
		}
		if(!feof(fp))
		{
			printf("ѧ����Ϣ:\n");
			printf("ѧ��: %-15d  ����: %-15s\n",person.number,person.name);
			printf("�밴��Ŀ����ɼ�:\n");
			printf("�ߵ���ѧ: ");
			scanf("%d",&person.score.Math);
			printf("��ѧӢ��: ");
			scanf("%d",&person.score.English);
			printf("��ѧ����: ");
			scanf("%d",&person.score.Physics);
			printf("���ִ�ʷ: ");
			scanf("%d",&person.score.History);
			printf("������γ�: ");
			scanf("%d",&person.score.Computer);
			person.score.total=person.score.Math+person.score.English+person.score.Physics
				+person.score.History+person.score.Computer;
			fseek(fp,(long)-sizeof(Student),SEEK_CUR); 
			fwrite(&person,sizeof(Student),1,fp);
		}
		else
		{
			printf("�޴�ѧ�ŵ�ѧ����\n");
		}
		printf("=====================================\n") ;
		printf("�Ƿ������ӣ�\n");
		printf("����1����/0����: "); 
		while(getchar()!='\n');
		sign=getchar();
		while(sign!='1'&&sign!='0'){
			printf("�����������������(1/0): ");
			while(getchar()!='\n');
			sign=getchar();
		}
	}while(sign=='1');
}

void grade_inquire()
{
	char menuid=' ';
	
	while(menuid!='0')
	{
		system("cls");
		printf("************�ɼ���ѯ************\n");
		printf("================================\n");
		printf("          1. �༶�ɼ���ѯ\n");
		printf("          2. ѧ�Ƴɼ����\n");
		printf("          0. ����\n");
		printf("================================\n");
		printf("��ѡ���������: ");
		menuid=getchar();
		
		switch(menuid){
			case'1': grade_inquire_by_class(); break;
			case'2': grade_inquire_by_subject(); break;
			case'0': break; 
			default: printf("�������,���������룡\n"); break;
		}
	}
}

void grade_inquire_by_class()
{
	Student student[MAX],t_student;
	int class_number,count=0;
	int i,j;
	system("cls");
	
	printf("��������Ҫ��ѯ�İ༶: ");
	scanf("%d",&class_number);
	fseek(fp,0L,SEEK_SET);
	fread(&student[count],sizeof(Student),1,fp); 
	while(!feof(fp))
	{
		if(student[count]._class==class_number && student[count].state==1 && student[count].score.total!=-1){
			count++;
		}
		else{
			fread(&student[count],sizeof(Student),1,fp);
		}	
	}
	//ð������ 
	for(i=1;i<=count;i++){
		for(j=0;j<count-i;j++){
		    if(student[j].score.total<student[j+1].score.total)
		    {
		     t_student=student[j];
		     student[j]=student[j+1];
		     student[j+1]=t_student;
		    }
		}
	}
	for(i=0;i<count;i++){
		student[i].score.rank=i+1;
	} 
	printf("%d��ĳɼ���������(���ܳɼ���������):\n",class_number);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-10s%-10s\n",
		"ѧ��","����","�ߵ���ѧ","��ѧӢ��","��ѧ����","���ִ�ʷ","������γ�","�ܳɼ�","�༶����");
	for(i=0;i<count;i++)
	{
		printf("%-15d%-15s%-15d%-15d%-15d%-15d%-15d%-10d%-10d\n",
			student[i].number,student[i].name,student[i].score.Math,student[i].score.English,
			student[i].score.Physics,student[i].score.History,student[i].score.Computer,
			student[i].score.total,student[i].score.rank);
		if(student[i].score.total==student[i+1].score.total){
			student[i+1].score.rank=student[i].score.rank;
		}
	} 
	system("pause");
}

void grade_inquire_by_subject()
{
	Student person;
	float sum_Math=0,sum_English=0,sum_Physics=0,sum_History=0,sum_Computer=0; 
	int pass_Math=0,pass_English=0,pass_Physics=0,pass_History=0,pass_Computer=0; 
	int count=0;
	
	system("cls");
	fseek(fp,0L,SEEK_SET);
	fread(&person,sizeof(Student),1,fp);
	while(!feof(fp))
	{
		if(person.state==1&&person.score.total!=-1){
			sum_Math+=person.score.Math;
			if(person.score.Math>=60) pass_Math++;
			sum_English+=person.score.English;
			if(person.score.English>=60) pass_English++;
			sum_Physics+=person.score.Physics;
			if(person.score.Physics>=60) pass_Physics++;
			sum_History+=person.score.History;
			if(person.score.History>=60) pass_History++;
			sum_Computer+=person.score.Computer;
			if(person.score.Computer>=60) pass_Computer++;
			count++;
		} 
		fread(&person,sizeof(Student),1,fp);
	}
	
	printf("%15s%15s%15s\n","�γ�����","ƽ���ɼ�","������");
	printf("===============================================\n");
	printf("%15s%15.2f%14.2f%%\n","�ߵ���ѧ",sum_Math/count,((float)pass_Math/count)*100);
	printf("%15s%15.2f%14.2f%%\n","��ѧӢ��",sum_English/count,((float)pass_English/count)*100);
	printf("%15s%15.2f%14.2f%%\n","��ѧ����",sum_Physics/count,((float)pass_Physics/count)*100);
	printf("%15s%15.2f%14.2f%%\n","���ִ�ʷ",sum_History/count,((float)pass_History/count)*100);
	printf("%15s%15.2f%14.2f%%\n","������γ�",sum_Computer/count,((float)pass_Computer/count)*100);
	printf("===============================================\n");
	
	system("pause");
}

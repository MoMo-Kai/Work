#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#define MAX 50  //班级最大人数为50 

typedef struct _score{
	int Math;  //高等数学 
	int English;  //大学英语 
	int Physics;  //大学物理 
	int History;  //近现代史 
	int Computer;  //计算机课程 
	int total;  //总成绩
	int rank;  //总排名 
}Score; 

typedef struct _student{
	short state;  //学籍状态(1正常/0注销) 
	int number;  //学号
	char name[9];  //姓名
	char sex[2];  //性别
	int age;  //年龄
	char origin[15];  //籍贯
	int grade;  //年级
	char major[15];  //专业
	int _class;  //班级 
	Score score;  //各科成绩 
}Student;

//主界面函数 
void add_data();  //学籍添加函数 
void modify_data();  //学籍修改函数 
void search_data();  //学籍查询函数 
	//学籍查询子函数
	void search_data_by_person();  //按个人查询
	void search_data_by_class();  //按班级查询 
void cancel_data();  //学籍注销函数 
void score_manage();  //成绩管理函数 
	//成绩管理子函数 
	void grade_input();  //成绩录入函数 
	void grade_inquire();  //成绩查询函数 
		//成绩查询子函数 
		void grade_inquire_by_class();  //按班级查询 
		void grade_inquire_by_subject();  //按科目查询 

FILE *fp=NULL;

int main() {
	char select=' ';
	//检查文件是否打开 
	if((fp=fopen("student.txt","rb+"))==NULL) 
	{
		if((fp=fopen("student.txt","wb+"))==NULL) {
			printf("打开文件student.txt失败！");
			exit(1);	
		} 	
	}
	
	while(select!='0'){
		system("cls");
		//主界面呈现 
		printf("**********小型学籍管理系统**********\n");
		printf("====================================\n");
		printf("=          1. 学籍添加             =\n");
		printf("=          2. 学籍修改             =\n");
		printf("=          3. 学籍查询             =\n");
		printf("=          4. 学籍注销             =\n");
		printf("=          5. 成绩管理             =\n"); 
		printf("=          0. 退    出             =\n");
		printf("====================================\n");
		printf("请选择代码输入: ");
		select=getchar();
		//功能选择进入函数 
		switch(select){
			case'1': add_data(); break;
   		    case'2': modify_data(); break;
			case'3': search_data(); break;
			case'4': cancel_data(); break;
			case'5': score_manage(); break;
			case'0': fclose(fp); return 0;
			default: printf("输入错误,请重新输入！\n"); break;
		}
	}
}

//学籍添加函数 
void add_data()
{
	Student person;
	person.state=1;
	person.score.total=-1;
	char sign;
	do{
		system("cls");
		printf("************学籍添加************\n");
		printf("******请按提示依次输入信息******\n");
		printf("学号: ");
		scanf("%ld",&person.number);
		printf("姓名: ");
		scanf("%s",person.name);
		printf("性别(男/女): ");
		scanf("%s",person.sex);
		while(strcmp(person.sex,"男")!=0 && strcmp(person.sex,"女")!=0){
			printf("性别输入错误，请重新输入: ");
			scanf("%s",person.sex);
		}
		printf("年龄: ");
		scanf("%d",&person.age);
		printf("籍贯: ");
		scanf("%s",person.origin);
		printf("年级: ");
		scanf("%d",&person.grade);
		printf("专业: ");
		scanf("%s",person.major);
		printf("班级: ");
		scanf("%d",&person._class);
		
		fseek(fp,0,SEEK_END);  //将指针移动到文件尾部
		fwrite(&person,sizeof(Student),1,fp); 
		
		printf("=====================================\n") ;
		printf("是否继续添加？\n");
		printf("输入1继续/0返回: "); 
		while(getchar()!='\n'); 
		sign=getchar();
		while(sign!='1'&&sign!='0'){
			printf("输入错误，请重新输入(1/0): ");
			while(getchar()!='\n');
			sign=getchar();
		}
	}while(sign=='1');
}

//学籍修改函数 
void modify_data()
{
	Student person;
	int number;
	system("cls");
	printf("************学籍修改************\n");
	printf("请输入要修改的学生的学号: ");
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
		printf("请检查更新前学生的信息:\n");
		printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","学号","姓名","性别","年龄","籍贯","年级","专业","班级");
		printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
			person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
		printf("请输入更新后的数据:\n");
		printf("学号: ");
		scanf("%d",&person.number);
		printf("姓名: ");
		scanf("%s",person.name);
		printf("性别(男/女): ");
		scanf("%s",person.sex);
		while(strcmp(person.sex,"男")!=0 && strcmp(person.sex,"女")!=0){
			printf("性别输入错误，请重新输入: ");
			scanf("%s",person.sex);
		}
		printf("年龄: ");
		scanf("%d",&person.age);
		printf("籍贯: ");
		scanf("%s",person.origin);
		printf("年级: ");
		scanf("%d",&person.grade);
		printf("专业: ");
		scanf("%s",person.major);
		printf("班级: ");
		scanf("%d",&person._class);
		fseek(fp,(long)-sizeof(Student),SEEK_CUR); 
		fwrite(&person,sizeof(Student),1,fp);
	}
	else
	{
		printf("无此学号的学生，请先进行学籍添加！\n");
	}
	system("pause");
}

//学籍查询函数 
void search_data()
{
	char menuid=' ';
	
	while(menuid!='0')
	{
		system("cls");
		printf("************学籍查询************\n");
		printf("================================\n");
		printf("          1. 个人学籍查询\n");
		printf("          2. 班级学籍查询\n");
		printf("          0. 返回\n");
		printf("================================\n");
		printf("请选择代码输入: ");
		menuid=getchar();
		
		switch(menuid){
			case'1': search_data_by_person(); break;
			case'2': search_data_by_class(); break;
			case'0': break; 
			default: printf("输入错误,请重新输入！\n"); break;
		}
	}
}

void search_data_by_person()
{
	Student person;
	int number;
	int sign;     
	system("cls");
	printf("请输入要查询的学生的学号: ");
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
		printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","学号","姓名","性别","年龄","籍贯","年级","专业","班级");
		printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
			person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
	}
	else
	{
		printf("无此学号的学生！\n");
	}
	system("pause");
}

void search_data_by_class()
{
	Student person;
	int class_number;
	system("cls"); 
	printf("请输入要查询的班级: ");
	scanf("%d",&class_number);
	printf("%d班的学生学籍统计如下：\n",class_number);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","学号","姓名","性别","年龄","籍贯","年级","专业","班级");
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

//学籍注销函数
void cancel_data()
{
	Student person;
	int number;
	system("cls");
	printf("********************学籍注销********************\n");
	printf("请输入需要注销学籍信息的学生的学号: ");
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
		printf("被删除记录为:\n");
		printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","学号","姓名","性别","年龄","籍贯","年级","专业","班级");
		printf("%-15d%-15s%-15s%-15d%-15s%-15d%-15s%-15d\n",
			person.number,person.name,person.sex,person.age,person.origin,person.grade,person.major,person._class);
		person.state=0;
		fseek(fp,(long)-sizeof(Student),SEEK_CUR); 
		fwrite(&person,sizeof(Student),1,fp);
	}
	else
	{
		printf("无此学生学号的信息!\n");
	}
	system("pause");
}

//成绩管理函数
void score_manage()
{
	char menuid=' ';
	
	while(menuid!='0')
	{
		system("cls");
		printf("************成绩管理************\n");
		printf("================================\n");
		printf("          1. 成绩录入\n");
		printf("          2. 成绩统计\n");
		printf("          0. 返回\n");
		printf("================================\n");
		printf("请选择代码输入: ");
		menuid=getchar();
		
		switch(menuid){
			case'1': grade_input(); break;
			case'2': grade_inquire(); break;
			case'0': break; 
			default: printf("输入错误,请重新输入！\n"); break;
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
		printf("********************成绩录入********************\n");
		printf("请输入需要录入成绩的学生的学号: ");
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
			printf("学生信息:\n");
			printf("学号: %-15d  姓名: %-15s\n",person.number,person.name);
			printf("请按科目输入成绩:\n");
			printf("高等数学: ");
			scanf("%d",&person.score.Math);
			printf("大学英语: ");
			scanf("%d",&person.score.English);
			printf("大学物理: ");
			scanf("%d",&person.score.Physics);
			printf("近现代史: ");
			scanf("%d",&person.score.History);
			printf("计算机课程: ");
			scanf("%d",&person.score.Computer);
			person.score.total=person.score.Math+person.score.English+person.score.Physics
				+person.score.History+person.score.Computer;
			fseek(fp,(long)-sizeof(Student),SEEK_CUR); 
			fwrite(&person,sizeof(Student),1,fp);
		}
		else
		{
			printf("无此学号的学生！\n");
		}
		printf("=====================================\n") ;
		printf("是否继续添加？\n");
		printf("输入1继续/0返回: "); 
		while(getchar()!='\n');
		sign=getchar();
		while(sign!='1'&&sign!='0'){
			printf("输入错误，请重新输入(1/0): ");
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
		printf("************成绩查询************\n");
		printf("================================\n");
		printf("          1. 班级成绩查询\n");
		printf("          2. 学科成绩情况\n");
		printf("          0. 返回\n");
		printf("================================\n");
		printf("请选择代码输入: ");
		menuid=getchar();
		
		switch(menuid){
			case'1': grade_inquire_by_class(); break;
			case'2': grade_inquire_by_subject(); break;
			case'0': break; 
			default: printf("输入错误,请重新输入！\n"); break;
		}
	}
}

void grade_inquire_by_class()
{
	Student student[MAX],t_student;
	int class_number,count=0;
	int i,j;
	system("cls");
	
	printf("请输入您要查询的班级: ");
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
	//冒泡排序 
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
	printf("%d班的成绩汇总如下(按总成绩降序排列):\n",class_number);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-10s%-10s\n",
		"学号","姓名","高等数学","大学英语","大学物理","近现代史","计算机课程","总成绩","班级排名");
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
	
	printf("%15s%15s%15s\n","课程名称","平均成绩","及格率");
	printf("===============================================\n");
	printf("%15s%15.2f%14.2f%%\n","高等数学",sum_Math/count,((float)pass_Math/count)*100);
	printf("%15s%15.2f%14.2f%%\n","大学英语",sum_English/count,((float)pass_English/count)*100);
	printf("%15s%15.2f%14.2f%%\n","大学物理",sum_Physics/count,((float)pass_Physics/count)*100);
	printf("%15s%15.2f%14.2f%%\n","近现代史",sum_History/count,((float)pass_History/count)*100);
	printf("%15s%15.2f%14.2f%%\n","计算机课程",sum_Computer/count,((float)pass_Computer/count)*100);
	printf("===============================================\n");
	
	system("pause");
}

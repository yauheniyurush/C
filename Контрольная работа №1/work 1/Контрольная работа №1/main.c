//���������� ����������� ������������ ����� ����������� ����������
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//���������� ��������� ������������ ����
#include "header.h"

//����� ������� ������� ���������
void main()
{	
	//��������� ����������
	//���������� ��� ���������� ������������� ������ �������
	int n=0;
	//�����. ��� ���������� �������� ���-��, ��� �������� � �� ����� ������� � ������	
	Student std;
	//��������� �� ������ � ��������� ������� ��������� ��������	
	Student *begin=NULL, *end=NULL;  
	
	//���������������� ����
	//1.�������� ������ � ������ ��������� 2.��������������� ������ � ������ 
	//3.����. ������ � ���� 4.������. ������ �� ����� 5.������� ������ �� ����� 
	//6.�����
L:  printf("\n1.add    3.save   5.print  \n2.edit   4.load   6.exit   \n");
	printf("Input the command number (from 1 to 6): ");
	//��������� �������� ������������� �������� � ���������� n
	scanf("%d", &n);
	
	//� ���-�� �� ��������� ������������� �������� (1-5) ������. �����. �������,
	//��� ����� '6' (6� �������) ������� ��� ������
	switch(n) 
	{
	case 1: //��������� �������� �� ������������ �� ��������� ��������� std
			getUser(&std);
			//��������� ����������� �����-�� ���-�� std � ���������� �����������
		    end=addEnd(&std,end,0);
			//��� ������ ���������� ���-�� ��������� �� 1 � �������. ��������� �����
			if (begin==NULL) begin=end;  
			break;
	case 2: //����������� ��������� ������������� ������
			editStd(begin, &end, &begin);
			break;
	case 3: //��������� ������ � ����
			saveList(begin,"list.dat"); break;
	case 4:	//��������� ������ �� �����
			loadList(begin,"list.dat",&end, &begin); break;
	case 5: //�������� ������ �� �����
			printList (begin); break;
	case 6: //��������� ��������� ��� ������
			exit(0); break;
	}
	//��� ����� ������������� �������� �� ������� 1,2,3,4,5,6
	//������ ������������ ������ ������� ��� ���
	goto L; 
}

//������� ��� ����� �������� �� ������������
//���� ��������: ��������� �� ���������
void getUser(Student *p)
{
	Student tmp;
	//��������� ����������� � ��������� ���������� �� ������������
	printf("\nInput name :");
	fflush(stdin);
	fgets(tmp.fname,MAXFNAME,stdin);
	//������� ������ ���������� ������ ���. ��������� �������� fgets
	tmp.fname[strlen(tmp.fname)-1]='\0';
	printf("Input floor: ");
	scanf("%d", &tmp.floor);
	fflush(stdin);
	printf("Input room number: ");
	scanf("%d", &tmp.roomNmb);
	
	//��������� �� ����. ����. ��������� ������ ����� 
	tmp.pnext = tmp.pprev = NULL;
	//�������� ��������� tmp � ��������� �� ��������� p (����. ���-�)
	*p = tmp;
}

//������� (�) ��� ���������� ����������� �����-�� ��������� � ��������� ������� 
//��������. � ���������: ����������� ���������, ��������� �� ���������
//��������� � ������, ����� � ������ ������� ���������� ��������� ��� 
//������������ �������� (�.�. ������ �-� ��� ������������ ��� ��������
//������ �� �����). � ����������: ��������� �� ��������� ������� ������������ � 
//���������� end - ��������� �� ��������� ���������
Student* addEnd(Student *p, Student *end, int stnumb)
{
	//�������� ������ ��� ���������, �������� ��������� �� �� � pAdd
	Student *pAdd=(Student*)malloc(sizeof(Student));
	//��������� ������ �� ������ pAdd ����������, ����� �������� ��������� p, ����������
	*pAdd=*p; 
	if (end==NULL) //���� ��������� ������ ������� 
	{
		//� ��������� end �������� ��������� �� ����������� ���������
		end=pAdd;
		//���� ���������� �������� stnumb ����� ����, ����� ������ � ������ ����������� 1
		//����� �������� ������ ����������� ��������� stnumb
		if (stnumb==0) pAdd->studNmb=1;
		else pAdd->studNmb=stnumb;
	}
	else //���� ��������� �� ������ �������
	{
		end->pnext = pAdd;//��������� ��������� ������� � �����������
		pAdd->pprev=end;  //��������� ����������� ������� � ��������� 
		//���� ���������� �������� stnumb ����� ����, ����� ����� � ������ �����������
		//����� ��������� ������ � ������ ���� ����
		if (stnumb==0) pAdd->studNmb=end->studNmb+1;
		else  pAdd->studNmb=stnumb;
		end= pAdd;
	}
	//���������� ��������� �� ��������� �������
	return end;
}
//������� ��� �������������� ��������� ������������� �����
//����. ���-��: ��������� �� ������ ���������, 
//��������� �� ��������� ��������� � ������ ���������,
//��������� �� ��������� ������ � ������ ���������,
int editStd(Student *p, Student **pend, Student **pbegin)
{	//��������� ����������
	int n, k;
	Student *s, std;
	//������� ������ �� ����� � ���������� ������� ����� ������
	printList (p);
	printf("Input number of student: ");
	scanf("%d", &n);
	//������� ��������� ����� � ������ ���. ����� ����������
	while(p!=NULL) {
	if (p->studNmb==n){	s=p; break;}	
	p=p->pnext;	}
	//���������� ������� ����� ������� "��� ������� �� �������"
L:	printf("\nWhat do you want to do with it? \n1.edit \n2.delete\
 \n3.exit to the main menu \nInput the command number : ");
	scanf("%d", &k);
	switch(k)
	{
	case 1: //��� �������������� ������ ����������� ���������� ������
			getUser(&std);//� ��������� �� � ��������� std 
			//� ��������� ������������� ������ ������ ��������� 
			strncpy(s->fname,std.fname,sizeof(std.fname));
			s->roomNmb=std.roomNmb; s->floor=std.floor;
			goto M; //����� �� �����
	case 2: //������� ������ �������� deleteStd, ������� � ��
			//��������� �� ��������� ���-��, �� ������ � ��������� ��-�� ������ 
			deleteStd(s, pend, pbegin); goto M; //� ������� �� �����
	case 3: goto M;	//����� �� ����� � ������� ����
	}
	goto L;  //�������������� ����� ������� ���� �������� �������� �� 1,2,3
M:	return 0;//������� ��� ���� �� ������
}
//�������� ������ �� ������, ��������� ���������� ������� editStd
int deleteStd(Student *p, Student **pend, Student **pbegin) 
{
	Student *pr=NULL, *pn=NULL;//��������� ��� ����. ����. ��. ������
	if (p->pnext==NULL) //���� ��������� ������ ���������
	{
		pr=p->pprev; //��������� � pr ��������� �� ������. ��. ������
		if(pr!=NULL) //���� ������. ��. ����
		{
			pr->pnext=NULL; //�������� ��������� � ����. ��-��
			*pend=pr;       //���������� ������� ��������� ���������
		
		} else //���� ������. �������� ��� (�.�. ������� � ������ ����)
		{
			*pend=NULL; //��������� � ������ �������� ������ ��������
			*pbegin=NULL;
		}
	}
	else if (p->pprev==NULL) //���� ��������� ������ ������
	{
		pn=p->pnext; //��������� � pn ��������� �� ����. ��. ������
		*pbegin=pn;  //��������� �� ������ ������� ������ �� pn
		pn->pprev=NULL; //� ���� ��-�� �������� ��������� �� ����. ��-�
	}
	else //���� ��������� ���. �� ������ �� ���������
	{
		pn=p->pnext; //��������� � pn ��������� �� ����. ��. ������
		pr=p->pprev; //��������� � pr ��������� �� ������. ��. ������
   //��������� ����-�� ��������. � ����. ��-�� ��� ��� ���. ��-� �������
		pn->pprev=p->pprev; 
		pr->pnext=p->pnext;
	}
	free(p); //����������� ������ �� ��������� ���. ��������
	p=NULL;  //�������� ���������
	return 0; //������� ��� ���� ������
}
//������� ������ ������ � ����
//��������: ��������� �� ������ ������� ������ � �������� �����
void saveList(Student *p, char *file)
{
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ��������. ������), � �������� ��������� �� ���� � pf
	FILE *pf=fopen(file,"w");
	//���� ���� ������� ������/������
	if (pf!=NULL)
	{
		while(p!=NULL)//���������� �� ���� ��������� ������
		{	
		//� ���������� �������� �������� � ����
		fprintf(pf,"%d %s %d %d\n", p->studNmb, p->fname, p->roomNmb, p->floor);
		p=p->pnext;
		}	
		fclose(pf);//��������� ����
	}
}

//������� �������� ������ �� �����, ���������:
//��������� �� ��������� ���� Student, �������� �����, ��������� �� 
//����-�� �� ������ ��-� ������, ����-�� �� ����-�� �� ��������� ��-� ������
void loadList(Student *p, char *file, Student **pend, Student **pbegin)
{	
	Student tmp, *ptmp;//
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ��������. ������), � �������� ��������� �� ���� � pf
	FILE *pf=fopen(file,"r");
	//���� ���� ������� ������/������
	if (pf!=NULL)
	{	
		//������� ������� ������ ��������
		while(p!=NULL)
		{
			ptmp=p->pnext;
			deleteStd(p, *pend, *pbegin);
			p=ptmp;
		}
		*pend=NULL;
		*pbegin=NULL;
		//���� �� ��������� ����� ����� ������ ������ �� ��������� ��������� tmp
		while(!feof(pf))
		{	
			fscanf(pf,"%d %s %d %d\n", &tmp.studNmb, &tmp.fname, &tmp.roomNmb, &tmp.floor);
			tmp.pnext = tmp.pprev = NULL;
			//��������� ������� addEnd, ������� � �� ��������� �� ����������� ��������� ���������,
			//��������� �� ��������� ���������� �������� ������, � ����� ������������� �������� � ������
			//������� ������� ���������� �� ����� ��������� � ������
			*pend=addEnd(&tmp,*pend,tmp.studNmb);
			//���� ������� ������ �� ��������� ������� ����� ������� ��������
			if (*pbegin==NULL) *pbegin=*pend;
		}
		fclose(pf);//��������� ����
	}
}
//������� ������ ������ �� ����� ��������� ��������� �� ���������
void printList(Student *p)
{
	//������� ����� �������
	printf("\n%s %s %s %s \n","# ","Name                     ","Floor ","Room ");
	printf("%s \n","----------------------------------------");
	
	//������ ���������� �� ��������� ������ � ������� �� �� ����� 
	//���� ��������� �������� print
	while(p!=NULL)
	{
		print(p);
		p=p->pnext;
	}
}
//������� ������ ������ ������ � �����
void print(Student *p)
{
	printf("%-2d %-25s %-6d %-3d \n", p->studNmb, p->fname, p->floor, p->roomNmb);
}
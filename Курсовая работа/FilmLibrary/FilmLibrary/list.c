//���������� ����������� ������������ ����� ����������� ����������
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//���������� ��������� ������������ ����
#include "header.h"

//������� ��� ����� �������� �� ������������
//���� ��������: ��������� �� ���������
void getUser(Film *p)
{
	Film tmp;
	int i;
	//��������� ����������� � ��������� ���������� �� ������������
	printf("\n������� �������� ������ :");
	//fflush(stdin);
	//fgets(tmp.fname,MAXFNAME,stdin);
	//tmp.fname[strlen(tmp.fname)-1]='\0';
	getLimStr(&tmp.fname, 100, MAXFNAME+1);
	//printf("%s",tmp.fname);
	printf("������� ���� ������ :");
	//fflush(stdin);
	//fgets(tmp.genre,GENRE,stdin);
	//������� ������ ���������� ������ ���. ��������� �������� fgets
	//tmp.genre[strlen(tmp.genre)-1]='\0';
	getLimStr(&tmp.genre, 100, GENRE+1);
	fflush(stdin);
	printf("������� ��� ������� ������: ");
	scanf("%d", &tmp.year);

	fflush(stdin);
	printf("������� ������ �������� [1-10]: ");
	scanf("%d", &tmp.mark);

	fflush(stdin);
	printf("������� ������ ������ (��� $): ");
	scanf("%d", &tmp.budget);
	//�������������� ����� ������ ������� ���������� 
	for(i=0;i<5;i++) {
		strcpy(tmp.actors[i].name,"");
	}

	//��������� �� ����. ����. ��������� ������ ����� 
	tmp.pnext = tmp.pprev = NULL;
	//�������� ��������� tmp � ��������� �� ��������� p (����. ���-�)
	*p = tmp;
}

//������� (�) ��� ���������� ����������� �����-�� ��������� � ��������� ������� 
//��������. � ���������: ����������� ���������, ��������� �� ���������
//��������� � ������, ����� � ������ ������� ���������� ��������� ��� 
//������������ ������ (�.�. ������ �-� ��� ������������ ��� ��������
//������ �� �����). � ����������: ��������� �� ��������� ������� ������������ � 
//���������� end - ��������� �� ��������� ���������
Film* addEnd(Film *p, Film *end, int stnumb)
{
	//�������� ������ ��� ���������, �������� ��������� �� �� � pAdd
	Film *pAdd=(Film*)malloc(sizeof(Film));
	//��������� ������ �� ������ pAdd ����������, ����� �������� ��������� p, ����������
	*pAdd=*p; 
	if (end==NULL) //���� ��������� ������ ������� 
	{
		//� ��������� end �������� ��������� �� ����������� ���������
		end=pAdd;
		//���� ���������� �������� stnumb ����� ����, ����� ������ � ������ ����������� 1
		//����� �������� ������ ����������� ��������� stnumb
		if (stnumb==0) pAdd->filmNmb=1;
		else pAdd->filmNmb=stnumb;
	}
	else //���� ��������� �� ������ �������
	{
		end->pnext = pAdd;//��������� ��������� ������� � �����������
		pAdd->pprev=end;  //��������� ����������� ������� � ��������� 
		//���� ���������� �������� stnumb ����� ����, ����� ����� � ������ �����������
		//����� ��������� ������ � ������ ���� ����
		if (stnumb==0) pAdd->filmNmb=end->filmNmb+1;
		else  pAdd->filmNmb=stnumb;
		end= pAdd;
	}
	//���������� ��������� �� ��������� �������
	return end;
}
//������� ��� �������������� ��������� ������������� �����
//����. ���-��: ��������� �� ������ ���������, 
//��������� �� ��������� ��������� � ������ ���������,
//��������� �� ��������� ������ � ������ ���������,
int editStd(Film *p, Film **pend, Film **pbegin)
{	//��������� ����������
	int n, k, i , w;
	Film *s, std, *z;
	//������� ������ �� ����� � ���������� ������� ����� ������
	printList (p);
	//������� ���������� �������
	z=p;
	w=0;
	while(z!=NULL) {	
		w++;
		z=z->pnext;
	}

	//printf("������� ID ������: ");
	//scanf("%d", &n);
	//������� ��������� ����� � ������ ���. ����� ����������
	//while(p!=NULL) {
	//	if (p->filmNmb==n){	s=p; break;}	
	//	p=p->pnext;	}
	printf("������� � ������: ");
	//scanf("%d", &n);
	check(w, &n);
	//������� ��������� ����� � ������ ���. ����� ����������
	i=1;
	while(p!=NULL) {
		if (i==n){
			s=p; 
		}	
		i++;
		p=p->pnext;
	}

	//���������� ������� ����� ������� "��� ������� �� �������"
L:	printf("\n�������� ��������: \n1.������������� \n2.�������\
		   \n3.�������� ������ \n4.������������� ������\
		   \n5.������� ����� \n6.����� � ������� ���� \n");
	check(6, &k);
	switch(k)
	{
	case 1: //��� �������������� ������ ����������� ���������� ������
		getUser(&std);//� ��������� �� � ��������� std 
		//� ��������� ������������� ������ ������ ��������� 
		strncpy(s->fname,std.fname,sizeof(std.fname));
		s->mark=std.mark; 
		s->year=std.year;
		strncpy(s->genre,std.genre,sizeof(std.genre));
		s->budget=std.budget;
		goto M; //����� �� �����
	case 4: //��������� ������� �������������� ������
		editActors(s); goto M;
	case 3: //��������� ������� ���������� ������
		addActors(s); goto M;
	case 5: //��������� ������� ���������� ������
		delActors(s); goto M;
	case 2: //������� ������ �������� deleteStd, ������� � ��
		//��������� �� ��������� ���-��, �� ������ � ��������� ��-�� ������ 
		deleteStd(s, pend, pbegin); goto M; //� ������� �� �����
	case 6: goto M;	//����� �� ����� � ������� ����
	}
	goto L;  //�������������� ����� ������� ���� �������� �������� �� 1,2,3
M:	return 0;//������� ��� ���� �� ������
}

//������� �������� ������
int delActors(Film *p)
{
	int i,n,k;
	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(p->actors[i].name,"")!=0)
			n++;
	}
	if (n==-1) printf("\n����� �� �������\n");
	else {
		printf("\n����� ������ %s \n",p->fname);
		printf("# ��� ������:               �������: �������� ����:\n");	
		for(k=0;k<5;k++)
		{
			if (strcmp(p->actors[k].name,"")!=0)
				printf("%d %-25s %-9d %s \n",k+1,p->actors[k].name,p->actors[k].age,p->actors[k].desc);	
		}
		printf("\n������� ����� �����: ");
		scanf("%d", &n);
		n--;
		if (n>=0 && n<5) {
			strcpy(p->actors[n].name,"");
			p->actors[n].age=0;
			strcpy(p->actors[n].desc,"");
			printf("\n���� �����.");
		}
		else {
			printf("\n�� ������� ����� � ����� �������");
		}
	}
	return 0;//������� ��� ���� �� ������
}

//������� �������������� ������ ������
//�������� ��������� �� ��������� ���� Film
int editActors(Film *p)
{
	int i,n,k;
	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(p->actors[i].name,"")!=0)
			n++;
	}
	if (n==-1) printf("\n����� �� �������\n");
	else {
		printf("\n����� ������ %s \n",p->fname);
		printf("# ��� ������:               �������: �������� ����:\n");	
		for(k=0;k<5;k++)
		{
			if (strcmp(p->actors[k].name,"")!=0)
				printf("%d %-25s %-9d %s \n",k+1,p->actors[k].name,p->actors[k].age,p->actors[k].desc);	
		}
		printf("\n������� ����� �����: ");
		scanf("%d", &n);
		n--;
		if (n>=0 && n<5) {
			printf("������� ���, ���. �����:");
			//fflush(stdin);
			//fgets(&p->actors[n].name,ACTORSNAME,stdin);
			//������� ������ ���������� ������ ���. ��������� �������� fgets
			//p->actors[n].name[strlen(p->actors[n].name)-1]='\0';
			getLimStr(&p->actors[n].name, 100, ACTORSNAME+1);

			fflush(stdin);
			printf("������� ������� �����: ");
			scanf("%d", &p->actors[n].age);

			printf("������� ����, ������� ��������:");
			//fflush(stdin);
			//fgets(&p->actors[n].desc,100,stdin);
			//������� ������ ���������� ������ ���. ��������� �������� fgets
			//p->actors[n].desc[strlen(p->actors[n].desc)-1]='\0';
			getLimStr(&p->actors[n].desc, 100, 50+1);
			printf("\n������ ���������������");
		}
		else {
			printf("\n�� ������� ����� � ����� �������");
		}
	}
	return 0;//������� ��� ���� �� ������
}

//������� ������ ������
//�������� ��������� �� ��������� ���� Film
int printActors(Film *p)
{
	Film *s=NULL;
	int      i, k, n;
	printList (p);
	printf("������� � ������: ");
	scanf("%d", &n);
	//������� ��������� ����� � ������ ���. ����� ����������
	i=1;
	while(p!=NULL) {
		if (i==n){
			s=p; 
		}	
		i++;
		p=p->pnext;
	}

	//print(s);
	if (s!=NULL) {
	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(s->actors[i].name,"")!=0)
			n++;
	}
	}
	if (n==-1 || s==NULL) printf("\n����� �� �������\n");
	else {

		printf("\n����� ������ %s \n",s->fname);
		printf("��� ������:               �������: �������� ����:\n");	
		for(k=0;k<5;k++)
		{
			if (strcmp(s->actors[k].name,"")!=0)
				printf("%-25s %-9d %s \n",s->actors[k].name,s->actors[k].age,s->actors[k].desc);	
		}
	}
	return 0;//������� ��� ���� �� ������
}

//������� ���������� ������ ������
//�������� ��������� �� ��������� ���� Film
int addActors(Film *p)
{
	int i,n,k;

	//����� ��������� ������ ��� �����
L:	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(p->actors[i].name,"")==0)
			n=i;
	}
	if (n>-1) {
		printf("������� ���, ���. �����:");
		//fflush(stdin);
		//fgets(&p->actors[n].name,ACTORSNAME,stdin);
		//������� ������ ���������� ������ ���. ��������� �������� fgets
		//p->actors[n].name[strlen(p->actors[n].name)-1]='\0';
		getLimStr(&p->actors[n].name, 100, ACTORSNAME+1);


		fflush(stdin);
		printf("������� ������� �����: ");
		scanf("%d", &p->actors[n].age);

		printf("������� ����, ������� ��������:");
		//fflush(stdin);
		//fgets(&p->actors[n].desc,100,stdin);
		//������� ������ ���������� ������ ���. ��������� �������� fgets
		//p->actors[n].desc[strlen(p->actors[n].desc)-1]='\0';
		getLimStr(&p->actors[n].desc, 100, 50+1);



		//������������� ����������� ���������� ������� ������
		printf("\n���� �����. \n1.�������� ��� ������ \n2.����� � ������� ����");
		printf("\n������� ����� ������� :");
		check(2, &k);
		//������� ���� ���������� ������� ������
		switch(k){
			case 1: goto L; 
			case 2: goto M;
		}  
	}
	else {
		printf("��� ��������� ������� ��� ���������� �����. �������� �������������.");
	}
M:	return 0;//������� ��� ���� �� ������
}

//�������� ������ �� ������, ��������� ���������� ������� editStd
int deleteStd(Film *p, Film **pend, Film **pbegin) 
{
	Film *pr=NULL, *pn=NULL;//��������� ��� ����. ����. ��. ������
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
void saveList(Film *p, char *file)
{	
	int i,n,k;
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ��������. ������), � �������� ��������� �� ���� � pf
	FILE *pf=fopen(file,"w");
	//���� ���� ������� ������/������
	if (pf!=NULL)
	{
		while(p!=NULL)//���������� �� ���� ��������� ������
		{	
			//� ���������� �������� �������� � ����
			fprintf(pf,"%d %d %d %d\n", p->filmNmb, p->mark, p->year, p->budget);
			fputs(p->fname, pf);
			fprintf(pf,"\n");
			fputs(p->genre, pf);
			fprintf(pf,"\n");
			//---------------------
			n=0;
			for(i=0;i<5;i++){
				if (strcmp(p->actors[i].name,"")!=0)
					n++;
			}
			fprintf(pf,"%d\n", n);
			if (n>0) {
				for(k=0;k<5;k++) {
					if (strcmp(p->actors[k].name,"")!=0) {
						fprintf(pf,"%d\n", p->actors[k].age);
						fputs(p->actors[k].name, pf);
						fprintf(pf,"\n");
						fputs(p->actors[k].desc, pf);
						fprintf(pf,"\n");
					}
				}
			}
			//------------------------
			//fprintf(pf,"%d %25s %d %d\n", p->filmNmb, p->fname, p->mark, p->year);
			p=p->pnext;
		}	
		fclose(pf);//��������� ����
	}
}

//������� �������� ������ �� �����, ���������:
//��������� �� ��������� ���� Film, �������� �����, ��������� �� 
//����-�� �� ������ ��-� ������, ����-�� �� ����-�� �� ��������� ��-� ������
void loadList(Film *p, char *file, Film **pend, Film **pbegin)
{	
	int i, k;
	Film tmp, *ptmp;//
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ��������. ������), � �������� ��������� �� ���� � pf
	FILE *pf1=fopen(file,"r");
	//���� ���� ������� ������/������
	if (pf1!=NULL)
	{	
		//������� ������� ������ ��������
		while(p!=NULL)
		{
			ptmp=p->pnext;
			deleteStd(p, pend, pbegin);
			p=ptmp;
		}
		*pend=NULL;
		*pbegin=NULL;
		//���� �� ��������� ����� ����� ������ ������ �� ��������� ��������� tmp
		while(!feof(pf1))
		{	
			//fscanf(pf,"%d %25[^\r\n] %d %d\n", &tmp.filmNmb, &tmp.fname, &tmp.mark, &tmp.year);
			fscanf(pf1,"%d %d %d %d\n", &tmp.filmNmb, &tmp.mark, &tmp.year, &tmp.budget);
			//fgets(&tmp.fname, 25, pf);
			fscanf(pf1,"%25[^\r\n]\n", &tmp.fname);
			fscanf(pf1,"%10[^\r\n]\n", &tmp.genre);
			tmp.pnext = tmp.pprev = NULL;
			fscanf(pf1,"%d\n", &i);
			if (i>0) {
				for(k=0;k<i;k++) {
					fscanf(pf1,"%d\n", &tmp.actors[k].age);
					fscanf(pf1,"%25[^\r\n]\n", &tmp.actors[k].name);
					//fprintf(pf,"\n");
					fscanf(pf1,"%100[^\r\n]\n", &tmp.actors[k].desc);
					//fprintf(pf,"\n");
				}
				for(k=i;k<5;k++){
					strcpy(tmp.actors[k].name,"");
				}
			}
			//��������� ������� addEnd, ������� � �� ��������� �� ����������� ��������� ���������,
			//��������� �� ��������� ���������� �������� ������, � ����� ������������� �������� � ������
			//������� ������� ���������� �� ����� ��������� � ������
			*pend=addEnd(&tmp,*pend,tmp.filmNmb);
			//���� ������� ������ �� ��������� ������� ����� ������� ��������
			if (*pbegin==NULL) *pbegin=*pend;
		}
		fclose(pf1);//��������� ����
	}
}
//������� ������ ������ �� ����� ��������� ��������� �� ���������
void printList(Film *p)
{
	int n=1;
	//������� ����� �������                                       
	printf("\n%s %s %s %s %s %s %s \n","#  ","ID ","�������� ������          ","��� ","������","����      ","������(���)");
	printf("%s \n","--------------------------------------------------------------------");

	//������ ���������� �� ��������� ������ � ������� �� �� ����� 
	//���� ��������� �������� print
	while(p!=NULL)
	{
		printf("%-3d ",n);
		print(p);
		p=p->pnext;
		n++;
	}
}
//������� ������ ������ ������ � �����
void print(Film *p)
{
	printf("%-3d %-25s %-4d %6d %-15s %-12d \n", p->filmNmb, p->fname, p->year, p->mark, p->genre, p->budget);
}

//������� ������ ����������� ����� �� �����, ��������� ��������� �� ������ ������� ���������� ������
void find(Film *p)
{	
	int k;
	printf("\n�� ������ �������� ��������� �����?\
		   \n1.�� ��������\
		   \n2.�� �����\
		   \n3.�� ���� �������\
		   \n������� ����� ������:");
	check(3, &k);
	switch(k)
	{
	case 1: {
		//������ ���������� ����(0,1) � ���������� ��� �������� ����� ������������
		int  flag=0;
		char tempname[MAXFNAME];
		//����������� ��� ������ ��� ������
		printf("\n������� ������������ ������ ��� ������:");
		//fflush(stdin);
		//fgets(tempname,MAXFNAME,stdin);
		//tempname[strlen(tempname)-1]='\0';
		getLimStr(&tempname, 100, MAXFNAME+1);
		//scanf("%s", tempname);
		//������ ���������� �� ��������� ������ � ������� �� ����� ������ 
		//� ����������� �� ������������ ������ 
		while(p!=NULL)
		{
			if (strcmp(p->fname,tempname)==0) 
			{
				if (flag==0) 
				{
					//������� ����� �������                                       
					printf("\n%s %s %s %s %s %s %s \n","ID ","�������� ������          ","��� ","������","����      ","������(���)", "�����");
					printf("%s \n","---------------------------------------------------------------------");
					flag=1;
				}
				print(p);
			}
			p=p->pnext;
		}
		//�� ����� �����, �������� �� ���� ������������ 
		if (flag==0) printf("%s %s\n","�� ������� ������ � ����� ������������� - ",tempname);
		break;
			}
	case 2: {
		//������ ���������� ����(0,1) � ���������� ��� �������� ����� ������������
		int  flag=0;
		char tempname[GENRE];
		//����������� ��� ������ ��� ������
		printf("\n������� ���� ������ ��� ������:");
		//fflush(stdin);
		//fgets(tempname,GENRE,stdin);
		//tempname[strlen(tempname)-1]='\0';
		getLimStr(tempname, 100, GENRE+1);

		//scanf("%s", tempname);
		//������ ���������� �� ��������� ������ � ������� �� ����� ������ 
		//� ����������� �� ������������ ������ 
		while(p!=NULL)
		{
			if (strcmp(p->genre,tempname)==0) 
			{
				if (flag==0) 
				{
					//������� ����� �������                                       
					printf("\n%s %s %s %s %s %s %s \n","#  ","ID ","�������� ������          ","��� ","������","����      ","������(���)", "�����");
					printf("%s \n","---------------------------------------------------------------------");
					flag=1;
				}
				print(p);
			}
			p=p->pnext;
		}
		//�� ����� �����, �������� �� ���� ������������ 
		if (flag==0) printf("%s %s\n","�� ������� ������ � ����� ������ - ",tempname);
		break;
			}
	case 3: {
		//������ ���������� ����(0,1) � ���������� ��� �������� ����� ������������
		int  flag=0, year;
		//����������� ��� ������ ��� ������
		printf("\n������� ��� ������� ������ ��� ������:");
		scanf("%d", &year);
		//scanf("%s", tempname);
		//������ ���������� �� ��������� ������ � ������� �� ����� ������ 
		//� ����������� �� ������������ ������ 
		while(p!=NULL)
		{
			if (p->year==year) 
			{
				if (flag==0) 
				{
					//������� ����� �������                                       
					printf("\n%s %s %s %s %s %s %s \n","#  ","ID ","�������� ������          ","��� ","������","����      ","������(���)", "�����");
					printf("%s \n","---------------------------------------------------------------------");
					flag=1;
				}
				print(p);
			}
			p=p->pnext;
		}
		//�� ����� �����, �������� �� ���� ������������ 
		if (flag==0) printf("%s %d\n","�� ������� ������ � ����� ����� ������� - ",year);
		break;
			}
	}
}

//������� ��� ����� ������� ��������� ������������� �������
//�������� ��� ��� ����� �������� ��������� ��� � ��� ����� 
//�� �������� ���������
Film* insInv(Film *p1, Film *p2)
{
	Film *pnextTemp, *pprevTemp, *pprev2Temp, *pnextTemp2, *pprevTemp2;

	//����� ����������� ����� ���������� �� �������
	//����� ������� ������ ������������ � ���������� ������

	//��� ���� ������������ �������� ��������� ���������� �� 
	//����������� �� ��������, ������� ���� ����������� ��� �����

	if (p2->pprev==p1)//���� �������� ��������
	{
		pprev2Temp=p1->pprev;
		pprevTemp=p1->pprev;
		pnextTemp=p2->pnext;

		p1->pnext=p2->pnext;
		p1->pprev=p2;

		p2->pnext=p1;
		p2->pprev=pprevTemp;

		if (pnextTemp!=NULL) pnextTemp->pprev=p1;
		if (pprev2Temp!=NULL) pprev2Temp->pnext=p2;
	}
	else//���� �������� �� ��������
	{
		pnextTemp=p2->pnext;
		pprevTemp=p1->pprev;
		pnextTemp2=p1->pnext;
		pprevTemp2=p2->pprev;

		p1->pnext=pnextTemp;
		p1->pprev=pprevTemp2;

		p2->pnext=pnextTemp2;
		p2->pprev=pprevTemp;

		pprevTemp2->pnext=p1;
		pnextTemp2->pprev=p2;
		if (pprevTemp!=NULL) pprevTemp->pnext=p2;
		if (pnextTemp!=NULL) pnextTemp->pprev=p1;
	}
	return p2;
}


//������� ��� ���������� ����������
void sortByFeature(Film *p, Film **begin, Film **end) 
{
	int attr;
	Film *pnext1, *pnext2;

	printf("\n�� ������ �������� ��������� ����������?\
		   \n1.�� ID ������\
		   \n2.�� ��������\
		   \n3.�� �����\
		   \n4.�� ���� �������\
		   \n������� ����� ������:");
	check(4, &attr);

	//�������� ��������� �� ��������� ������� �.�. ������������� ����� ������
	//������� ������� � ������� ����� ���
	pnext1=p->pnext;
	while (pnext1!=NULL)
	{
		//���������� ������� ��������� �� ���� ���������������
		pnext2=pnext1->pnext;
		//���� ��������������� ������� �� ������� �� ��� ����� � ����������� 
		//� ���������� ������� �������, ��������� ������������ �������� ���������
		while (1)
		{
			//� ������ ���� ������� ���� ������ � ������ ��� ���� ������� 
			//����� ��� ������, ����������� ������ ������������
			if (pnext1->pprev==NULL) break; 
			if (compare(pnext1,pnext1->pprev, attr)==1) break;
			//������������ ��������� �� ������ ��� ����� ���� ����������
			if (pnext1->pprev->pprev==NULL) *begin=pnext1;
			if (pnext1->pnext==NULL) *end=pnext1->pprev;
			//���� ������� ������������
			pnext1=insInv(pnext1->pprev,pnext1);
		}
		//������������ ��������� �� ������� ��������� �� ���� ���������������
		pnext1=pnext2;
	}
}


int compare(Film *p1, Film *p2, int attr) {
	int n=0;
	if (attr==1) {
		if (p1->filmNmb>p2->filmNmb) n=1;
	}
	else if (attr==2) {
		if (strcmp(p1->fname,p2->fname)>0) n=1;
	}
	else if (attr==3) {
		if (strcmp(p1->genre,p2->genre)>0) n=1;
	}
	else {
		if (p1->year>p2->year) n=1;
	}
	return n;
}





int checkLogPas(int k)
{
	char login[16], pass[16], tmplogin[16], tmppass[16];
	char role[5];
	char strtemp1[5];
	int n=0;
	FILE *pf=fopen("usr.dat","r");

	if (k==1) strcpy(role,"adm");
	else strcpy(role,"usr");

	printf("������� ��� ������������: ");
	strcpy(login,"");
	//fflush(stdin);
	//fgets(login,15,stdin);
	//login[strlen(login)-1]='\0';	
	getLimStr(&login, 15, 6);

	printf("������: ");
	strcpy(pass,"");
	//fflush(stdin);
	//fgets(pass,15,stdin);
	//pass[strlen(pass)-1]='\0';
	getLimStr(&pass, 15, 6);
	if (pf!=NULL) { 
		fseek(pf,0,0);
		while(!feof(pf)) {
			strcpy(strtemp1,"");
			fscanf(pf,"%4[^\r\n]\n", &strtemp1);
			if (strcmp(strtemp1,role)==0) {
				fscanf(pf,"%15[^\r\n]\n", &tmplogin);
				fscanf(pf,"%15[^\r\n]\n", &tmppass);
				//fgets(tmplogin, 16, pf);
				//fgets(tmppass, 16, pf);
				if (strcmp(tmplogin,login)==0 && strcmp(tmppass,pass)==0) n++;
			}
		}
		//printf("���� ����������");
	}
	if (n!=0) return 0; 
	else return 1;
}



void manageUsers() {

	int n, k=0;
	char strtemp[5], login[15], pass[15], tmplogin[16], tmppass[16];
	int flag=0;
	while (flag==0) {
		printf("\n���������� �������� �������� �������������\
			   \n1. �������� ���� ������� ������� �������������\
			   \n2. ���������� ����� ������� ������\
			   \n3. �������� ������� ������\
			   \n4. ����� � ������������ ����\
			   \n������� ����� ������� [1-4]:");
		check(4, &n);
		switch(n) 
		{
		case 1: {	
			FILE *pf=fopen("usr.dat","r");
			int n=0, k=0;
			if (pf!=NULL) { 
				while(!feof(pf)) {
					fscanf(pf,"%4[^\r\n]\n", &strtemp);
					if (strcmp(strtemp,"adm")==0 || strcmp(strtemp,"usr")==0) {
						fscanf(pf,"%15[^\r\n]\n", &tmplogin);
						fscanf(pf,"%15[^\r\n]\n", &tmppass);
						if (k==0) {
							printf("\n%2s %5s %15s %15s \n","# ","���� ","�����           ","������         ");
							printf("%s \n","-----------------------------------------");
							k++;
						}
						n++;
						printf("%-2d %-5s %-16s %-16s\n", n, strtemp, tmplogin, tmppass);
					}
				}
			}
			fclose(pf);
			break;
				}
		case 2: {	
			int k;
			char role[5], login[15], pass[15];
			FILE *pf=fopen("usr.dat","a");
			fprintf(pf,"\n");
			if (pf!=NULL) { 
				printf("\n�������� ���� ������������ ������������\
					   \n1. �������������\
					   \n2. ������������\
					   \n������� ����� ������� [1-2]:");
				check(2, &k);

				if (k==1) strcpy(role,"adm");
				else strcpy(role,"usr");
				fputs(role, pf);
				fprintf(pf,"\n");

				printf("\n������� ��� ������������: ");
				strcpy(login,"");
				//fflush(stdin);
				//fgets(login,15,stdin);
				//login[strlen(login)-1]='\0';
				getLimStr(&login, 15, 6);
				fputs(login, pf);
				fprintf(pf,"\n");

				printf("������: ");
				strcpy(pass,"");
				//fflush(stdin);
				//fgets(pass,15,stdin);
				//pass[strlen(pass)-1]='\0';
				getLimStr(&pass, 15, 6);
				fputs(pass, pf);
				fprintf(pf,"\n");
				fclose(pf);
				printf("\n������� ������ ���������.");
			}
			fclose(pf);
			break;
				}
		case 3: {	
			FILE *pf;
			int n=0, k=0;
			int flag=0;

			pf=fopen("usr.dat","r");
			if (pf!=NULL) { 
				while(!feof(pf)) {
					fscanf(pf,"%4[^\r\n]\n", &strtemp);
					if (strcmp(strtemp,"adm")==0 || strcmp(strtemp,"usr")==0) {
						fscanf(pf,"%15[^\r\n]\n", &tmplogin);
						fscanf(pf,"%15[^\r\n]\n", &tmppass);
						if (k==0) {
							printf("\n%2s %5s %15s %15s \n","# ","���� ","�����           ","������         ");
							printf("%s \n","-----------------------------------------");
							k++;
						}
						n++;
						printf("%-2d %-5s %-16s %-16s\n", n, strtemp, tmplogin, tmppass);
					}
				}
			}
			fclose(pf);

			printf("\n������� ����� ������������ � ������: ");
			scanf("%d", &n);

			k=1;
			pf=fopen("usr.dat","r+");
			if (pf!=NULL) { 
				while(!feof(pf) && flag!=1) {
					fscanf(pf,"%4[^\r\n]\n", &strtemp);
					if (strcmp(strtemp,"adm")==0 || strcmp(strtemp,"usr")==0) {
						if (n==k) {
							fseek(pf,-5,SEEK_CUR);
							fputs("                 \n", pf);
							flag=1;
						}
						k++;
					}
				}
			}
			fclose(pf);
			break;
				}
		case 4: { 
			flag=1;
			break;
				}
		}

	}
}


void fileManager(Film *p, char *file, Film **pend, Film **pbegin) {

	int k=0;
	int flag=0;

	while (flag==0) {
		printf("\n���������� ������ ���� ������\
			   \n1. ��������� ������������ ���������\
			   \n2. ������� ���� �������� ������\
			   \n3. ������� ���� ��� �������� ������\
			   \n4. ����� � ������� ����\
			   \n������� ����� ������� [1-4]:");
		check(4, &k);
		switch(k) 
		{
		case 1: {
			saveList(p,file);
			printf("��������� ��������� � ���� %s", file);
			break;
				}
		case 2: { 
			FILE *pf;
			char newdir[100]={""};
			printf("������� ����������:\n");
			//fflush(stdin);
			//fgets(newdir,100,stdin);
			//newdir[strlen(newdir)-1]='\0';
			getLimStr(&newdir, 200, 100);
			pf=fopen(newdir,"r");
			if (pf!=NULL) {
				fclose(pf);
				strcpy(file,newdir);
				printf("���� ������ ���������.");
				loadList(p,newdir,pend,pbegin);
			} else printf("������ �������� ����� ���� ������");
			fflush(stdin);
			break;
				} 
		case 3: { 
			FILE *newfile;
			char newdir[100]={""};
			printf("������� ����������:\n");
			//fflush(stdin);
			//fgets(newdir,100,stdin);
			//newdir[strlen(newdir)-1]='\0';
			getLimStr(&newdir, 200, 100);
			newfile=fopen(newdir,"w");
			if (newfile!=NULL) {
				strcpy(file,newdir);
				fclose(newfile);
				printf("���� ������ �������.");
			} else printf("������ �������� ����� ��� �������� ������");
			break;
				}
		case 4: {
			flag=1;
			break;
				}
		}
	}						
}

void check(int k, int *n){
	int flag=0;
	char r[3];
	while(flag==0) {
		fflush(stdin);
		fgets(r,2,stdin);
		*n=atoi(r);
		//printf("%d",*n);
		if (*n>0 && *n<k+1) {
			flag=1;
		} else {
			printf("������� ����� ������� [1-%d]:", k);
		}
	}
}


void getLimStr(char *c, int l, int lim) {			
	int flag=0;
	char *str = (char*) malloc((l+1)*sizeof(char));
	while (flag==0) {
		fflush(stdin);
		fgets(str,l,stdin);
		str[strlen(str)-1]='\0';
		if (strlen(str)<=lim) {
			strcpy(c,str);
			flag=1;
		} else { 
			printf("���������� ������ ������. ���������� �������� �� ������ ��������� %d:\n", lim-1);
		}
	}
}
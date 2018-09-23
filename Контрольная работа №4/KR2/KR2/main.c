//���������� ����������� ������������ ����� ����������� ����������
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
//���������� ��������� ������������ ����
#include "header.h"
//��������� ���������� ���������� ���� clock_t 
//�� <time.h> ��� �������� �������� �������
clock_t t;

//����� ������� ������� ���������
void main()
{	
	//��������� ����������
	//���������� ��� ���������� ������������� ������ �������
	int n=0, k=0;
	//�����. ��� ���������� �������� ���-��, ��� �������� � �� ����� ������� � ������	
	Merchant std;
	//��������� �� ������ � ��������� ������� ��������� ��������	
	Merchant *begin=NULL, *end=NULL;  
	//��������� ��������� �� ��������� ��� ����������� ������� ��� �����-������
	queue *q;
	//�������� ������ ��� ��������� queue �� ��������� q
	q = (queue*)malloc(sizeof(queue));
	//������ � ��������� ������� ������� ���������� ��������, ��� ��. ��� ��� �����
	q->frnt = 0;
	q->rear = 0;

	//���������������� ����
	//1.�������� ������ � ������ ������� 2.��������������� ������ � ������ 
	//3.����. ������ � ���� 4.������. ������ �� ����� 5.������� ������ �� ����� 
	//6.����� 7.����� ������ �� ������������ ������ 8.����������� ���������
	//9.���������� ���������� 10.���������� ������� 11.���������� ���������� �������
L:  printf("\n1.add    3.save   5.print  7.find     9.sortSign   11.add Queue\n2.edit\
	 4.load   6.exit   8.sortInsr 10.exchSort\n");
	printf("Input the command number (from 1 to 7): ");
	//��������� �������� ������������� �������� � ���������� n
	scanf("%d", &n);
	
	//� ���-�� �� ��������� ������������� �������� (1-7) ������. �����. �������,
	//��� ����� '6' (6� �������) ������� ��� ������
	switch(n) 
	{
	case 1: //��������� �������� �� ������������ �� ��������� ��������� std
			getUser(&std);
			//��������� ����������� �����-�� ���-�� std � ���������� �����������
		    end=addEnd(&std,end,0);
			//��� ������ ���������� ���-�� ��������� �� 1 � �������. ��������� �����
			if (begin==NULL) begin=end;  break;
	case 2: editStd(begin, &end, &begin); break; //���-�� ��������� ������������� ������
	case 3: saveIntoFile(begin); break;//��������� ������ � ����
	case 4:	//��������� ������ �� �����
			//��������� ����� ���������� ����������: ��������, ���������
			//� � ����������� �� ���� ��������� ������ �������
			k=loadFileMode();
			if (k==1) loadList(begin,"list.dat",&end, &begin); 
			else loadListBinary(begin,"list.dat",&end, &begin); break;
	case 5: printListQueue (begin, q); break;//�������� ������ �� �����
	case 6: exit(0); break;//��������� ��������� ��� ������
	case 7: find(begin); break; //������� ����������� ������ 
	case 8: insSort(begin, &begin, &end);	break; //��������� ���������� ������ ���������
	case 9: signSort(begin, &begin, &end);	break; //��������� ���������� ����������
	case 10: //��������� ���������� ������ ������� (����������� �-��)
			exchSort(begin, &begin, &end);	break;
	case 11: getUserQueue(q, &begin, &end); break; //���� ��������
	}
	//��� ����� ������������� �������� �� ������� 1-11
	//������ ������������ ������ ������� ��� ���
	goto L; 
}

//������� ��� ����� �������� �� ������������
//���� ��������: ��������� �� ���������
void getUser(Merchant *p)
{
	Merchant tmp;
	//��������� ����������� � ��������� ���������� �� ������������
	printf("\nInput merchant :");
	fflush(stdin);
	fgets(tmp.fname,MAXFNAME,stdin);
	//������� ������ ���������� ������ ���. ��������� �������� fgets
	tmp.fname[strlen(tmp.fname)-1]='\0';
	printf("Input sold amount: ");
	scanf("%d", &tmp.sold);
	fflush(stdin);
	printf("Input price: ");
	scanf("%d", &tmp.price);
	
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
Merchant* addEnd(Merchant *p, Merchant *end, int stnumb)
{	
	//�������� ������ ��� ���������, �������� ��������� �� �� � pAdd
	Merchant *pAdd=(Merchant*)malloc(sizeof(Merchant));
	//��������� ������ �� ������ pAdd ����������, ����� �������� ��������� p, ����������
	*pAdd=*p; 
	if (end==NULL) //���� ��������� ������ ������� 
	{
		//� ��������� end �������� ��������� �� ����������� ���������
		end=pAdd;
		//���� ���������� �������� stnumb ����� ����, ����� ������ � ������ ����������� 1
		//����� �������� ������ ����������� ��������� stnumb
		if (stnumb==0) pAdd->merchNmb=1;
		else pAdd->merchNmb=stnumb;
	}
	else //���� ��������� �� ������ �������
	{
		end->pnext = pAdd;//��������� ��������� ������� � �����������
		pAdd->pprev=end;  //��������� ����������� ������� � ��������� 
		//���� ���������� �������� stnumb ����� ����, ����� ����� � ������ �����������
		//����� ��������� ������ � ������ ���� ����
		if (stnumb==0) pAdd->merchNmb=end->merchNmb+1;
		else  pAdd->merchNmb=stnumb;
		end= pAdd;
	}
	//���������� ��������� �� ��������� �������
	return end;
}
//������� ��� �������������� ��������� ������������� �����
//����. ���-��: ��������� �� ������ ���������, 
//��������� �� ��������� ��������� � ������ ���������,
//��������� �� ��������� ������ � ������ ���������,
int editStd(Merchant *p, Merchant **pend, Merchant **pbegin)
{	//��������� ����������
	int n, k;
	Merchant *s, std;
	//������� ������ �� ����� � ���������� ������� ����� ������
	printList (p);
	printf("Input number of Merchant: ");
	scanf("%d", &n);
	//������� ��������� ����� � ������ ���. ����� ����������
	while(p!=NULL) {
	if (p->merchNmb==n){	s=p; break;}	
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
			s->price=std.price; s->sold=std.sold;
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
int deleteStd(Merchant *p, Merchant **pend, Merchant **pbegin) 
{
	Merchant *pr=NULL, *pn=NULL;//��������� ��� ����. ����. ��. ������
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
void saveList(Merchant *p, char *file)
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
		fprintf(pf,"%d %s %d %d\n", p->merchNmb, p->fname, p->price, p->sold);
		p=p->pnext;
		}	
		fclose(pf);//��������� ����
	}
}

//������� �������� ������ �� �����, ���������:
//��������� �� ��������� ���� Merchant, �������� �����, ��������� �� 
//����-�� �� ������ ��-� ������, ����-�� �� ����-�� �� ��������� ��-� ������
void loadList(Merchant *p, char *file, Merchant **pend, Merchant **pbegin)
{	
	Merchant tmp, *ptmp;
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
			fscanf(pf,"%d %s %d %d\n", &tmp.merchNmb, &tmp.fname, &tmp.price, &tmp.sold);
			tmp.pnext = tmp.pprev = NULL;
			//��������� ������� addEnd, ������� � �� ��������� �� ����������� ��������� ���������,
			//��������� �� ��������� ���������� �������� ������, � ����� ������������� �������� � ������
			//������� ������� ���������� �� ����� ��������� � ������
			*pend=addEnd(&tmp,*pend,tmp.merchNmb);
			//���� ������� ������ �� ��������� ������� ����� ������� ��������
			if (*pbegin==NULL) *pbegin=*pend;
		}
		fclose(pf);//��������� ����
	}
}
//������� ������ ������ �� ����� ��������� ��������� �� ���������
void printList(Merchant *p)
{
	//������� ����� �������                                       
	printf("\n%s %s %s %s \n","# ","Merchant                 ","Amount","Price");
	printf("%s \n","-----------------------------------------");
	
	//������ ���������� �� ��������� ������ � ������� �� �� ����� 
	//���� ��������� �������� print
	while(p!=NULL)
	{
		print(p);
		p=p->pnext;
	}
}
//������� ������ ������ ������ � �����
void print(Merchant *p)
{
	printf("%-2d %-25s %-7d %-5d \n", p->merchNmb, p->fname, p->sold, p->price);
}

//������� ������ ����������� ����� �� �����, ��������� ��������� �� ������ ������� ���������� ������
void find(Merchant *p)
{	//������ ���������� ����(0,1) � ���������� ��� �������� ����� ������������
	int  flag=0;
	char tempname[MAXFNAME];
	//����������� ��� ������ ��� ������
	printf("\nInput name of merchant which you want to find:");
	scanf("%s", tempname);
	//������ ���������� �� ��������� ������ � ������� �� ����� ������ 
	//� ����������� �� ������������ ������ 
	while(p!=NULL)
	{
		if (strcmp(p->fname,tempname)==0) 
		{
			if (flag==0) 
			{
				//������� ����� �������                                       
				printf("\n%s %s %s %s \n","# ","Merchant                 ","Amount","Price");
				printf("%s \n","-----------------------------------------");
				flag=1;
			}
			print(p);
		}
		p=p->pnext;
	}
	//�� ����� �����, �������� �� ���� ������������ 
	if (flag==0) 
	{printf("%s %s\n","There are no merchant called - ",tempname);}
}

//������� ��� ����� ������� ��������� ������������� �������
//�������� ��� ��� ����� �������� ��������� ��� � ��� ����� 
//�� �������� ���������
Merchant* insInv(Merchant *p1, Merchant *p2)
{
	Merchant *pnextTemp, *pprevTemp, *pprev2Temp, *pnextTemp2, *pprevTemp2;
	
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
void insSort(Merchant *p, Merchant **begin, Merchant **end) 
{

	Merchant *pnext1, *pnext2;
	t=clock();
	//��������� ��������� �� ��������� ������� �.�. ������������� ����� ������
	//������� ������� � ������� ����� ���
	pnext1=p->pnext;
	while (pnext1!=NULL)
	{
		//���������� ������� ��������� �� ���� ���������������
		pnext2=pnext1->pnext;
		//���� ��������������� ������� �� ������� �� ��� ����� � ����������� 
		//� ���������� ������� �������, ��������� ����������� �������� ���������
		while (1)
			{
				//� ������ ���� ������� ���� ������ � ������ ��� ���� ������� 
				//����� ��� ������, ����������� ������ ������������
				if (pnext1->pprev==NULL) break; 
				if (pnext1->price>pnext1->pprev->price) break;
				//������������ ��������� �� ������ ��� ����� ���� ����������
				if (pnext1->pprev->pprev==NULL) *begin=pnext1;
				if (pnext1->pnext==NULL) *end=pnext1->pprev;
				//���� ������� ������������
				pnext1=insInv(pnext1->pprev,pnext1);
			}
		//������������ ��������� �� ������� ��������� �� ���� ���������������
		pnext1=pnext2;
	}
	t = clock() - t;
printf("\nOperation time: %d CPU cycles (%f seconds).\n",(int)t,((double)t)/CLOCKS_PER_SEC);
}
//������� ��� ���������� �������
void signSort(Merchant *p, Merchant **begin, Merchant **end)
{
	int n=0,k=0,m=0,i;
	Merchant *pSign=p, *pCount=p, *pBegin=p;	
	t=clock();
	//������� ��� �������� � ������� ����������
	while(pCount!=NULL){
		if (pCount->price<pSign->price) pSign=pCount;
		pCount=pCount->pnext;
		k++;}
	//���� ��������� �� ������ � ������� ������� ��� �� ������ �����
	//���� ������������ � ������ ���������
	if (pSign!=p) 
	{
		if (pSign->pnext==NULL) *end=p;
		pBegin=insInv(p,pSign);
		*begin=pBegin;//������������ ��������� �� ������ �������
	}
	//������ ������� �������� ���������� ��������� ������� ����� � ����������� �������
	n++;
	//���������� �� ����� ����� (����� ��������� ����� ����) ���
	//� ������ ��� ������������� � ������ ������� ������ ��������
	while(n<k-1)
	{
		pCount=pBegin; pSign=pBegin; m=0;
		//� ������ ����� �� ������� ���������� �������� ����� �� ���������� ���������
		while(pCount!=NULL)
		{
			if (m<n) pSign=pSign->pnext;
			if (pCount->price<pSign->price && m>=n) pSign=pCount;
			pCount=pCount->pnext;
			m++;
		}
		pCount=pBegin;
		//����� �� ������� ������ ������� ����� ������������ � ������ ������� ��-��� 
		for(i=0;i<n;i++) pCount=pCount->pnext;
		//���� ������ ������� ����� ������������ � ������ ������� �� ����������
		//������ ��� ������� � ����������
		if (pSign!=pCount)
		{
			if (pSign->pnext==NULL) 
	 	{	//������������ ��������� �� ��������� ������� ���� ����������
				*end=pCount;
			}
			//���� ������� ������������ ���������
			insInv(pCount,pSign);
		}
		n++;//����������� ����� ��������� ������������ � ���������� �������
	}
	t = clock() - t;
printf("\nOperation time: %d CPU cycles (%f seconds).\n",(int)t,((double)t)/CLOCKS_PER_SEC);
}

//������� ��� ���������� �������
//��������� ��������� �� ������ ������� �������
//��������� �� ��������� �� ������ ������� �������
//��������� �� ��������� �� ��������� ������� �������
void exchSort(Merchant *p, Merchant **begin, Merchant **end)
{
	int k=0;
	Merchant *pnext1=p, *pnext2=p, *pbegin=p;

	t=clock();
	//������� ���������� ��������� � ������� � �������� �������� � k
	while(pnext1!=NULL)
	{
		k++;
		pnext1=pnext1->pnext;
	}
	//���������� �� ��� �������� � ������������ �� ������� � ������ ���������� �������
	//���������� �� ���� ������� ����� ������� k-1 ���
	while (k-1>0) 
	{
//������ �������� ����� �������� ���������� �� 2�� �������� � ���������� ��� � ����������
		pnext1=pbegin->pnext;
		while (pnext1!=NULL)
		{
			pnext2=pnext1->pnext;
			
			if (pnext1->price<pnext1->pprev->price) 
			{
			//������������ ��������� �� ������ � ����� �������, � ������ �������������
				if (pnext1->pprev->pprev==NULL) {*begin=pnext1; pbegin=pnext1;}
				if (pnext1->pnext==NULL) *end=pnext1->pprev;
				//���� ������������ ���������
				pnext1=insInv(pnext1->pprev,pnext1);
			}
			//��������� �� ��������� ������� �� ���� ���������������
			pnext1=pnext2;		
		}
		//�������� ���������� ����������� �������� ����� ������� �� �������
		k--;
	}
	t = clock() - t;
printf("\nOperation time: %d CPU cycles (%f seconds).\n",(int)t,((double)t)/CLOCKS_PER_SEC);
}
//������� ���������� � ���� � ������������ ������
//����� �������� ������ ��������� ��������� ��
//������ ��������� ��� ����������
void saveIntoFile(Merchant *begin)
{
	int k;
	//���� ��� ������ ������������� ����� �������� ������
L:	printf("\nInpur data storage format \n1.text \n2.binary\
 \n3.exit to the main menu \nInput the command number : ");
	scanf("%d", &k);
	switch(k)
	{
	case 1: saveFileMode(1); //���������� ������ ���������� ������ ��� ��������
			saveList(begin,"list.dat"); //��������� � ��������� �������
			goto M;
	case 2:	saveFileMode(2);
			saveListBinary(begin,"list.dat");//��������� � �������� ����
			goto M; //� ������� �� �����
	case 3: goto M;	//����� �� ����� � ������� ����
	goto L;  //�������������� ����� ������� ���� �������� �������� �� 1,2,3
	}
M:	return 0;
}
//������� ��� ���������� ������ ������:
//� ��������� ���� ��� ��������
void saveFileMode(int n)
{
	FILE *pf=fopen("filemode.dat","w");
	//���� ���� ������� ������/������
	if (pf!=NULL)
	{
		fprintf(pf,"%d", n);
		fclose(pf);//��������� ����
	}
}
//������� ��� ������ �������(�����., �������� ���) ���������� ���������� � ����
int loadFileMode()
{	
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ��������. ������), � �������� ��������� �� ���� � pf
	FILE *pf=fopen("filemode.dat","r");
	int k;
	if (pf!=NULL)
	{	
		while(!feof(pf))
		{	
			fscanf(pf,"%d", &k);
		}
		fclose(pf);//��������� ����
	}
	return k;
}
//������� ��� ���������� ���������� � ���� � �������� ����,
//��������� ��������� �� ������ ��������� � ������ � �������� �����
void saveListBinary(Merchant *p, char *file)
{
	int k=0, len;
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ��������. ������), � �������� ��������� �� ���� � pf
	FILE *pf=fopen(file,"wb");
	
	//���� ���� ������� ������/������
	if (pf!=NULL)
	{	
		//� ������ ����� ��������� ����� ��� ����� ������� ����� ��������� � �����
		fwrite(&k, sizeof(int), 1, pf);
		while(p!=NULL)//���������� �� ���� ��������� ������
		{	
		//� ���������� �������� �������� � ����
		fwrite (&p->merchNmb, sizeof(int), 1, pf);
		//�������� ������ ���������� ��� ������ �������� � ������
		//� ����� ����� �������� ��������
		len = strlen(&p->fname);
        fwrite(&len, sizeof(unsigned), 1, pf);
        fwrite(&p->fname, 1, len, pf);
		
		fwrite (&p->price, sizeof(int), 1, pf);
		fwrite (&p->sold,  sizeof(int), 1, pf);
		p=p->pnext;
		k++;
		}
		rewind(pf);//�������� ��������� � ������ �����
        fwrite(&k, sizeof(int), 1, pf);//���������� ����� ���������� ���������
		fclose(pf);//��������� ����
	}
}

//������� �������� ���������� �� �����, ���������� � �������� ����, ���������:
//��������� �� ��������� ���� Merchant, �������� �����, ��������� �� 
//����-�� �� ������ ��-� ������, ����-�� �� ����-�� �� ��������� ��-� ������
void loadListBinary(Merchant *p, char *file, Merchant **pend, Merchant **pbegin)
{	//��������� ������ ���������-������ ��� ��������, �������������� ��� ������
	//� ��������� ��� �������� ������
	Merchant tmp={0,"",0,0}, *ptmp;	int k=0,i,len;
	//��������� ��������� pf ���� FILE, ���������/������ ����
	//�������� fopen (����� ������ �� ����� ������ � �������� ����),
	//� �������� ��������� �� ���� � pf
	FILE *pf=fopen(file,"rb");
	//���� ���� ������� ������/������
	if (pf!=NULL)
	{	//������� ������� ������ ��������
		while(p!=NULL)	{
			ptmp=p->pnext;
			deleteStd(p, *pend, *pbegin);
			p=ptmp;	}
		//������� ��������� �� ������ � �����
		*pend=NULL;	*pbegin=NULL;
		//������ ����� ������ ���������� ���������� �������� �� ������
		fread(&k, sizeof(int), 1, pf);
		//������ ������ �� ����� � ��������� ��������� ���� �� ��������� ��� ��������� 
		for (i = 0; i < k; i++) 
		 {
			fread (&tmp.merchNmb, sizeof(int), 1, pf);	fread(&len, sizeof(int), 1, pf);
			fread(&tmp.fname, 1, len, pf);	fread (&tmp.price, sizeof(int), 1, pf);
			fread (&tmp.sold,  sizeof(int), 1, pf);	tmp.pnext = tmp.pprev = NULL;
//��������� ������� addEnd, ������� � �� ��������� �� ����������� ��������� ���������,
//��������� �� ��������� ���������� �������� ������, � ����� �����-�� �������� � ������
//������� ������� ���������� �� ����� ��������� � ������
			*pend=addEnd(&tmp,*pend,tmp.merchNmb);
			//���� ������� ������ �� ��������� ������� ����� ������� ��������
			if (*pbegin==NULL) *pbegin=*pend;
		}
		fclose(pf);//��������� ����
	}
}

//������� ��� ���������� ��������� � �������
//��������� ��������� �� ������� ������, ��� ����������� �������
//� ��������� �� ����������� ���������
void insertQ(queue *q, Merchant *x) {
  int h;
	//��������� � ������� ������ � ������ ���� � ������� ��� ���� �����
	if(q->rear < QMAX-1) 
  {
	//� ������� ������ �������� ��������� ��������
	strncpy(q->qu[q->rear].fname,x->fname,sizeof(x->fname));
	q->qu[q->rear].merchNmb=x->merchNmb;
	q->qu[q->rear].price=x->price;
	q->qu[q->rear].sold=x->sold;
	//����������� ����� ������ �������
	q->rear++;
  }
  //���� ������� ����������� �� ����������� � ������ �������
  if(q->rear==QMAX-1)
  { //�������� ������ ������� � �������
    print(&q->qu[q->frnt]);
	//��� ����������� �������� �������� � ������
	for(h = q->frnt; h < q->rear; h++) 
	{
		strncpy(q->qu[h].fname,q->qu[h+1].fname,sizeof(q->qu[h+1].fname));
		q->qu[h].merchNmb=q->qu[h+1].merchNmb;
		q->qu[h].price	 =q->qu[h+1].price;
		q->qu[h].sold    =q->qu[h+1].sold;
	}
	//��������� ����� �������� ������������� ����� �������
	q->rear--;
  }
}
//������� ��� ������������ ������� (��� �������� ������� ���������
//�� ������)
void flushQ(queue *q) 
{
	int h;
	//���� ���� �������� � �������, ������� �� �� ������
	while (q->rear!=q->frnt)
	{	//�������� ������ �������
		print(&q->qu[q->frnt]);
		//������� ��� �������� � ������
		for(h = q->frnt; h<= q->rear; h++)
		{
			strncpy(q->qu[h].fname,q->qu[h+1].fname,sizeof(q->qu[h+1].fname));
			q->qu[h].merchNmb=q->qu[h+1].merchNmb;
			q->qu[h].price	 =q->qu[h+1].price;
			q->qu[h].sold    =q->qu[h+1].sold;
		}
		//��������� ����� �������� ������������� ����� �������
		q->rear--;
	}
}

//������� ��� ������ � �������������� �������
void printListQueue(Merchant *p, queue *q)
{	//������� ����� �������                                       
	printf("\n%s %s %s %s \n","# ","Merchant                 ","Amount","Price");
	printf("%s \n","-----------------------------------------");
	
	//������ ���������� �� ��������� ������ � ������� �� �� ����� 
	//���� ��������� �������� print
	while(p!=NULL)
	{
		insertQ(q, p);
		p=p->pnext;
	}
	flushQ(q);
}

//������� ��� ���������� ���������� ��������� � ������ � �������������� �������
void getUserQueue(queue *q, Merchant **begin, Merchant **end)
{
	Merchant std;
	int k1;
	//���� ��� ������������ ��� 1. ������� �������� ����� �������� � ������ 
	//��� 2. ������ �� �������� ����� ���������� ��������� � ������������� �������
	//(��������� ��������� �� ������� � ������)
L1:	printf("\nYou want to add one more merchant \n1.yes \n2.no \nInput the command number : ");
	scanf("%d", &k1);
	switch(k1)
	{
	//�������� ����� �������� � ������ ����� ������� �� ����
	case 1: 
		{
			int h=0;
			//����������� ���������� � ������������ ��� ���������� ��������
			getUser(&std);
			//��������� ������� � ������� ���� ���� �����
			if(q->rear < QMAX-1) 
			 {
				strncpy(q->qu[q->rear].fname,std.fname,sizeof(std.fname));
				q->qu[q->rear].price=std.price;
				q->qu[q->rear].sold=std.sold;
				//��������� �� ��������� � ���������� �������� � ������ ��������
				q->qu[q->rear].pnext=NULL;
				q->qu[q->rear].pprev=NULL;
				//����� ������� ����������� �� ����
				q->rear++;
			 }
			 //� ������ ���� ������� �����������, ������������ ������ ������� �� �������
			 //� ������� ��� � ������
			  if(q->rear==QMAX-1)
			  {	//������� ������ ������� ������� � ������
				*end=addEnd(&q->qu[q->frnt],*end,0);
				if (*begin==NULL) *begin=*end;
				//������� �������� ������� �����
				for(h = q->frnt; h < q->rear; h++) 
				{
					strncpy(q->qu[h].fname,q->qu[h+1].fname,sizeof(q->qu[h+1].fname));
					q->qu[h].price	 =q->qu[h+1].price;
					q->qu[h].sold    =q->qu[h+1].sold;
				}
				//����� ������� ��������� �� ����
				q->rear--;
			  }
			goto L1;
		} 
		//�������� ������������� ������� � ������ �� ��������
	case 2:	{
				int h=0;
				//���� ���� �������� � �������, ������� �� � ������ 
				while (q->rear!=q->frnt)
				{	//�������� ������� �������� �� �������
					*end=addEnd(&q->qu[q->frnt],*end,0);
					if (*begin==NULL) *begin=*end;
					//������� ��� �������� � ������
					for(h = q->frnt; h<= q->rear; h++)
					{
						strncpy(q->qu[h].fname,q->qu[h+1].fname,sizeof(q->qu[h+1].fname));
						q->qu[h].price	 =q->qu[h+1].price;
						q->qu[h].sold    =q->qu[h+1].sold;
					}
					//����� ������� ��������� �� ����
					q->rear--;
				}
				goto M2; //� ������� �� �����
			}
	}
	goto L1;  //�������������� ����� ������� ���� �������� �������� �� 1,2
M2:	return;
}
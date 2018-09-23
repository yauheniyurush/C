//подключаем необходимые заголовочные файлы стандартной библиотеки
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//подключаем созданный заголовочный файл
#include "header.h"

//функция для приёма значений от пользователя
//вход параметр: указатель на структуру
void getUser(Film *p)
{
	Film tmp;
	int i;
	//поочерёдно запрашиваем и принимаем информацию от пользователя
	printf("\nВведите название фильма :");
	//fflush(stdin);
	//fgets(tmp.fname,MAXFNAME,stdin);
	//tmp.fname[strlen(tmp.fname)-1]='\0';
	getLimStr(&tmp.fname, 100, MAXFNAME+1);
	//printf("%s",tmp.fname);
	printf("Введите жанр фильма :");
	//fflush(stdin);
	//fgets(tmp.genre,GENRE,stdin);
	//удаляем символ завершения строки кот. добавился функцией fgets
	//tmp.genre[strlen(tmp.genre)-1]='\0';
	getLimStr(&tmp.genre, 100, GENRE+1);
	fflush(stdin);
	printf("Введите год выпуска фильма: ");
	scanf("%d", &tmp.year);

	fflush(stdin);
	printf("Введите оценку зрителей [1-10]: ");
	scanf("%d", &tmp.mark);

	fflush(stdin);
	printf("Введите бюджет фильма (млн $): ");
	scanf("%d", &tmp.budget);
	//инициализируем имена актёров пустыми значениями 
	for(i=0;i<5;i++) {
		strcpy(tmp.actors[i].name,"");
	}

	//указатели на пред. след. структуру укажем позже 
	tmp.pnext = tmp.pprev = NULL;
	//копируем структуру tmp в структуру по указателю p (вход. пар-р)
	*p = tmp;
}

//функция (Ф) для связывания заполненной польз-ем структуры с имеющимся списком 
//структур. Ф принимает: заполненную структуру, указатель на последнюю
//структуру в списке, номер в списке который необходимо заполнить для 
//добавляемого фильма (т.к. данная ф-я еще используется при загрузке
//списка из файла). Ф возвращает: указатель на структуру который записывается в 
//переменную end - указатель на последнюю структуру
Film* addEnd(Film *p, Film *end, int stnumb)
{
	//выделяем память для структуры, помещаем указатель на неё в pAdd
	Film *pAdd=(Film*)malloc(sizeof(Film));
	//заполняем память по адресу pAdd переданной, через параметр указатель p, структурой
	*pAdd=*p; 
	if (end==NULL) //если добавляем первый элемент 
	{
		//в указатель end помещаем указатель на заполненную структуру
		end=pAdd;
		//если переданный параметр stnumb равен нулю, тогда номеру в списке присваиваем 1
		//иначе значение равное переданному параметру stnumb
		if (stnumb==0) pAdd->filmNmb=1;
		else pAdd->filmNmb=stnumb;
	}
	else //если добавляем не первый элемент
	{
		end->pnext = pAdd;//связываем последний элемент с добавляемым
		pAdd->pprev=end;  //связываем добавляемый элемент с последним 
		//если переданный параметр stnumb равен нулю, тогда номер в списке присваиваем
		//номер последней строки в списке плюс один
		if (stnumb==0) pAdd->filmNmb=end->filmNmb+1;
		else  pAdd->filmNmb=stnumb;
		end= pAdd;
	}
	//возвращаем указатель на последний элемент
	return end;
}
//функция для редактирования выбранных пользователем строк
//вход. пар-ры: указатель на первую структуру, 
//указатель на указатель последней в списке структуры,
//указатель на указатель первой в списке структуры,
int editStd(Film *p, Film **pend, Film **pbegin)
{	//объявляем переменные
	int n, k, i , w;
	Film *s, std, *z;
	//выводим список на экран и предлагаем выбрать номер строки
	printList (p);
	//считаем количество фильмов
	z=p;
	w=0;
	while(z!=NULL) {	
		w++;
		z=z->pnext;
	}

	//printf("Введите ID Фильма: ");
	//scanf("%d", &n);
	//находим структуру номер в списке кот. равен выбранному
	//while(p!=NULL) {
	//	if (p->filmNmb==n){	s=p; break;}	
	//	p=p->pnext;	}
	printf("Введите № фильма: ");
	//scanf("%d", &n);
	check(w, &n);
	//находим структуру номер в списке кот. равен выбранному
	i=1;
	while(p!=NULL) {
		if (i==n){
			s=p; 
		}	
		i++;
		p=p->pnext;
	}

	//предлагаем выбрать номер команды "что сделать со строкой"
L:	printf("\nВыберите операцию: \n1.Редактировать \n2.Удалить\
		   \n3.Добавить актёров \n4.Редактировать актёров\
		   \n5.Удалить актёра \n6.Выйти в главное меню \n");
	check(6, &k);
	switch(k)
	{
	case 1: //при редактировании строки запрашиваем переввести данные
		getUser(&std);//и сохраняем их в структуру std 
		//в выбранную пользователем строку вносим изменения 
		strncpy(s->fname,std.fname,sizeof(std.fname));
		s->mark=std.mark; 
		s->year=std.year;
		strncpy(s->genre,std.genre,sizeof(std.genre));
		s->budget=std.budget;
		goto M; //выход из цикла
	case 4: //запускаем функцию редактирования актёров
		editActors(s); goto M;
	case 3: //запускаем функцию добавления актёров
		addActors(s); goto M;
	case 5: //запускаем функцию добавления актёров
		delActors(s); goto M;
	case 2: //удаляем строку функцией deleteStd, передаём в неё
		//указатель на удаляемую стр-ру, на первый и последний эл-ты списка 
		deleteStd(s, pend, pbegin); goto M; //и выходим из цикла
	case 6: goto M;	//выход из цикла в главное меню
	}
	goto L;  //переспрашиваем номер команды если введённой значение не 1,2,3
M:	return 0;//выходим без кода об ошибке
}

//функция удаления актёров
int delActors(Film *p)
{
	int i,n,k;
	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(p->actors[i].name,"")!=0)
			n++;
	}
	if (n==-1) printf("\nАктёры не найдены\n");
	else {
		printf("\nАктёры фильма %s \n",p->fname);
		printf("# Имя актера:               Возраст: Описание роли:\n");	
		for(k=0;k<5;k++)
		{
			if (strcmp(p->actors[k].name,"")!=0)
				printf("%d %-25s %-9d %s \n",k+1,p->actors[k].name,p->actors[k].age,p->actors[k].desc);	
		}
		printf("\nВведите номер актёра: ");
		scanf("%d", &n);
		n--;
		if (n>=0 && n<5) {
			strcpy(p->actors[n].name,"");
			p->actors[n].age=0;
			strcpy(p->actors[n].desc,"");
			printf("\nАктёр удалён.");
		}
		else {
			printf("\nНе найдено актёра с таким номером");
		}
	}
	return 0;//выходим без кода об ошибке
}

//функция редактирования актёров фильма
//параметр указатель на структуру типа Film
int editActors(Film *p)
{
	int i,n,k;
	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(p->actors[i].name,"")!=0)
			n++;
	}
	if (n==-1) printf("\nАктёры не найдены\n");
	else {
		printf("\nАктёры фильма %s \n",p->fname);
		printf("# Имя актера:               Возраст: Описание роли:\n");	
		for(k=0;k<5;k++)
		{
			if (strcmp(p->actors[k].name,"")!=0)
				printf("%d %-25s %-9d %s \n",k+1,p->actors[k].name,p->actors[k].age,p->actors[k].desc);	
		}
		printf("\nВведите номер актёра: ");
		scanf("%d", &n);
		n--;
		if (n>=0 && n<5) {
			printf("Введите имя, фам. актёра:");
			//fflush(stdin);
			//fgets(&p->actors[n].name,ACTORSNAME,stdin);
			//удаляем символ завершения строки кот. добавился функцией fgets
			//p->actors[n].name[strlen(p->actors[n].name)-1]='\0';
			getLimStr(&p->actors[n].name, 100, ACTORSNAME+1);

			fflush(stdin);
			printf("Введите возраст актёра: ");
			scanf("%d", &p->actors[n].age);

			printf("Введите роль, краткое описание:");
			//fflush(stdin);
			//fgets(&p->actors[n].desc,100,stdin);
			//удаляем символ завершения строки кот. добавился функцией fgets
			//p->actors[n].desc[strlen(p->actors[n].desc)-1]='\0';
			getLimStr(&p->actors[n].desc, 100, 50+1);
			printf("\nЗапись отредактирована");
		}
		else {
			printf("\nНе найдено актёра с таким номером");
		}
	}
	return 0;//выходим без кода об ошибке
}

//функция печати актёров
//параметр указатель на структуру типа Film
int printActors(Film *p)
{
	Film *s=NULL;
	int      i, k, n;
	printList (p);
	printf("Введите № фильма: ");
	scanf("%d", &n);
	//находим структуру номер в списке кот. равен выбранному
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
	if (n==-1 || s==NULL) printf("\nАктёры не найдены\n");
	else {

		printf("\nАктёры фильма %s \n",s->fname);
		printf("Имя актера:               Возраст: Описание роли:\n");	
		for(k=0;k<5;k++)
		{
			if (strcmp(s->actors[k].name,"")!=0)
				printf("%-25s %-9d %s \n",s->actors[k].name,s->actors[k].age,s->actors[k].desc);	
		}
	}
	return 0;//выходим без кода об ошибке
}

//функция добавления актёров фильму
//параметр указатель на структуру типа Film
int addActors(Film *p)
{
	int i,n,k;

	//найдём свободную запись для актёра
L:	n=-1;
	for(i=0;(i<5 && n==-1);i++){
		if (strcmp(p->actors[i].name,"")==0)
			n=i;
	}
	if (n>-1) {
		printf("Введите имя, фам. актёра:");
		//fflush(stdin);
		//fgets(&p->actors[n].name,ACTORSNAME,stdin);
		//удаляем символ завершения строки кот. добавился функцией fgets
		//p->actors[n].name[strlen(p->actors[n].name)-1]='\0';
		getLimStr(&p->actors[n].name, 100, ACTORSNAME+1);


		fflush(stdin);
		printf("Введите возраст актёра: ");
		scanf("%d", &p->actors[n].age);

		printf("Введите роль, краткое описание:");
		//fflush(stdin);
		//fgets(&p->actors[n].desc,100,stdin);
		//удаляем символ завершения строки кот. добавился функцией fgets
		//p->actors[n].desc[strlen(p->actors[n].desc)-1]='\0';
		getLimStr(&p->actors[n].desc, 100, 50+1);



		//предоставляем возможность продолжить вводить оценки
		printf("\nАктёр введён. \n1.Добавить ещё одного \n2.Выйти в главное меню");
		printf("\nВведите номер команды :");
		check(2, &k);
		//выходим либо продолжаем вводить оценки
		switch(k){
			case 1: goto L; 
			case 2: goto M;
		}  
	}
	else {
		printf("Нет свободных записей для добавления актёра. Измените существующего.");
	}
M:	return 0;//выходим без кода об ошибке
}

//удаление строки из списка, параметры идентичные функции editStd
int deleteStd(Film *p, Film **pend, Film **pbegin) 
{
	Film *pr=NULL, *pn=NULL;//указатели для пред. след. эл. списка
	if (p->pnext==NULL) //если удаляемая строка последняя
	{
		pr=p->pprev; //сохраняем в pr указатель на предыд. эл. списка
		if(pr!=NULL) //если предыд. эл. есть
		{
			pr->pnext=NULL; //обнуляем указатель в пред. эл-те
			*pend=pr;       //предыдущий элемент объявляем последним

		} else //если предыд. элемента нет (т.е. элемент в списке один)
		{
			*pend=NULL; //последний и первый элементы списка обнуляем
			*pbegin=NULL;
		}
	}
	else if (p->pprev==NULL) //если удаляемая строка первая
	{
		pn=p->pnext; //сохраняем в pn указатель на след. эл. списка
		*pbegin=pn;  //указатель на первый элемент меняем на pn
		pn->pprev=NULL; //в след эл-те обнуляем указатель на пред. эл-т
	}
	else //если удаляемая стр. ни первая ни последняя
	{
		pn=p->pnext; //сохраняем в pn указатель на след. эл. списка
		pr=p->pprev; //сохраняем в pr указатель на предыд. эл. списка
		//связываем указ-ли предыдущ. и след. эл-та так как тек. эл-т удаляем
		pn->pprev=p->pprev; 
		pr->pnext=p->pnext;
	}
	free(p); //освобождаем память по указателю тек. элемента
	p=NULL;  //обнуляем указатель
	return 0; //выходим без кода ошибки
}
//функция записи списка в файл
//параметр: указатель на первый элемент списка и название файла
void saveList(Film *p, char *file)
{	
	int i,n,k;
	//объявляем указатель pf типа FILE, открываем/создаём файл
	//функцией fopen (режим символьн. записи), и помещаем указатель на файл в pf
	FILE *pf=fopen(file,"w");
	//если файл успешно открыт/создан
	if (pf!=NULL)
	{
		while(p!=NULL)//проходимся по всем элементам списка
		{	
			//и записываем элементы структур в файл
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
		fclose(pf);//закрываем файл
	}
}

//функция загрузки списка из файла, параметры:
//указатель на структуру типа Film, название файла, указатель на 
//указ-ль на первый эл-т списка, указ-ль на указ-ль на последний эл-т списка
void loadList(Film *p, char *file, Film **pend, Film **pbegin)
{	
	int i, k;
	Film tmp, *ptmp;//
	//объявляем указатель pf типа FILE, открываем/создаём файл
	//функцией fopen (режим символьн. чтения), и помещаем указатель на файл в pf
	FILE *pf1=fopen(file,"r");
	//если файл успешно открыт/создан
	if (pf1!=NULL)
	{	
		//очищаем текущий список структур
		while(p!=NULL)
		{
			ptmp=p->pnext;
			deleteStd(p, pend, pbegin);
			p=ptmp;
		}
		*pend=NULL;
		*pbegin=NULL;
		//пока не достигнут конец файла читаем данные во временную структуру tmp
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
			//запускаем функцию addEnd, передаём в неё указатель на заполненную временную структуру,
			//указатель на указатель последнего элемента списка, и номер записываемого элемента в списке
			//функция добавит полученную из файла структуру в список
			*pend=addEnd(&tmp,*pend,tmp.filmNmb);
			//если элемент первый то последний элемент равен первому элементу
			if (*pbegin==NULL) *pbegin=*pend;
		}
		fclose(pf1);//закрываем файл
	}
}
//функция вывода списка на экран принимает указатель на структуру
void printList(Film *p)
{
	int n=1;
	//выводим шапку таблицы                                       
	printf("\n%s %s %s %s %s %s %s \n","#  ","ID ","Название Фильма          ","Год ","Оценка","Жанр      ","Бюджет(млн)");
	printf("%s \n","--------------------------------------------------------------------");

	//циклом проходимся по элементам списка и выводим их на экран 
	//ниже описанной функцией print
	while(p!=NULL)
	{
		printf("%-3d ",n);
		print(p);
		p=p->pnext;
		n++;
	}
}
//функция печати строки списка н экран
void print(Film *p)
{
	printf("%-3d %-25s %-4d %6d %-15s %-12d \n", p->filmNmb, p->fname, p->year, p->mark, p->genre, p->budget);
}

//функция поиска необходимых строк на экран, принимает указатель на первый элемент связанного списка
void find(Film *p)
{	
	int k;
	printf("\nПо какому критерию выполнить поиск?\
		   \n1.По названию\
		   \n2.По жанру\
		   \n3.По году выпуска\
		   \nВведите номер пункта:");
	check(3, &k);
	switch(k)
	{
	case 1: {
		//вводим переменную флаг(0,1) и переменную для хранения ввода пользователя
		int  flag=0;
		char tempname[MAXFNAME];
		//запрашиваем имя фильма для поиска
		printf("\nВведите наименование фильма для поиска:");
		//fflush(stdin);
		//fgets(tempname,MAXFNAME,stdin);
		//tempname[strlen(tempname)-1]='\0';
		getLimStr(&tempname, 100, MAXFNAME+1);
		//scanf("%s", tempname);
		//циклом проходимся по элементам списка и выводим на экран строку 
		//с информацией по необходимому фильму 
		while(p!=NULL)
		{
			if (strcmp(p->fname,tempname)==0) 
			{
				if (flag==0) 
				{
					//выводим шапку таблицы                                       
					printf("\n%s %s %s %s %s %s %s \n","ID ","Название Фильма          ","Год ","Оценка","Жанр      ","Бюджет(млн)", "Актёры");
					printf("%s \n","---------------------------------------------------------------------");
					flag=1;
				}
				print(p);
			}
			p=p->pnext;
		}
		//не нашли фильм, сообщаем об этом пользователю 
		if (flag==0) printf("%s %s\n","Не найдено фильма с таким наименованием - ",tempname);
		break;
			}
	case 2: {
		//вводим переменную флаг(0,1) и переменную для хранения ввода пользователя
		int  flag=0;
		char tempname[GENRE];
		//запрашиваем имя фильма для поиска
		printf("\nВведите жанр фильма для поиска:");
		//fflush(stdin);
		//fgets(tempname,GENRE,stdin);
		//tempname[strlen(tempname)-1]='\0';
		getLimStr(tempname, 100, GENRE+1);

		//scanf("%s", tempname);
		//циклом проходимся по элементам списка и выводим на экран строку 
		//с информацией по необходимому фильму 
		while(p!=NULL)
		{
			if (strcmp(p->genre,tempname)==0) 
			{
				if (flag==0) 
				{
					//выводим шапку таблицы                                       
					printf("\n%s %s %s %s %s %s %s \n","#  ","ID ","Название Фильма          ","Год ","Оценка","Жанр      ","Бюджет(млн)", "Актёры");
					printf("%s \n","---------------------------------------------------------------------");
					flag=1;
				}
				print(p);
			}
			p=p->pnext;
		}
		//не нашли фильм, сообщаем об этом пользователю 
		if (flag==0) printf("%s %s\n","Не найдено фильма с таким жанром - ",tempname);
		break;
			}
	case 3: {
		//вводим переменную флаг(0,1) и переменную для хранения ввода пользователя
		int  flag=0, year;
		//запрашиваем имя фильма для поиска
		printf("\nВведите год выпуска фильма для поиска:");
		scanf("%d", &year);
		//scanf("%s", tempname);
		//циклом проходимся по элементам списка и выводим на экран строку 
		//с информацией по необходимому фильму 
		while(p!=NULL)
		{
			if (p->year==year) 
			{
				if (flag==0) 
				{
					//выводим шапку таблицы                                       
					printf("\n%s %s %s %s %s %s %s \n","#  ","ID ","Название Фильма          ","Год ","Оценка","Жанр      ","Бюджет(млн)", "Актёры");
					printf("%s \n","---------------------------------------------------------------------");
					flag=1;
				}
				print(p);
			}
			p=p->pnext;
		}
		//не нашли фильм, сообщаем об этом пользователю 
		if (flag==0) printf("%s %d\n","Не найдено фильма с таким годом выпуска - ",year);
		break;
			}
	}
}

//функция для смены местами элементов динамического массива
//работает как для смены соседних элементов так и для смены 
//не соседних элементов
Film* insInv(Film *p1, Film *p2)
{
	Film *pnextTemp, *pprevTemp, *pprev2Temp, *pnextTemp2, *pprevTemp2;

	//здесь совершается смена указателей на объекты
	//таким образом делаем перестановку в двусвязном списке

	//при этом перестановка соседних элементов отличается от 
	//перстановки не соседних, поэтому было разработано два блока

	if (p2->pprev==p1)//если элементы соседние
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
	else//если элементы не соседние
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


//функция для сортировки включением
void sortByFeature(Film *p, Film **begin, Film **end) 
{
	int attr;
	Film *pnext1, *pnext2;

	printf("\nПо какому критерию выполнить сортировку?\
		   \n1.По ID фильма\
		   \n2.По названию\
		   \n3.По жанру\
		   \n4.По году выпуска\
		   \nВведите номер пункта:");
	check(4, &attr);

	//сдвигаем указатель на следующий элемент т.к. рассматривать будем всегда
	//текущий элемент и элемент левее его
	pnext1=p->pnext;
	while (pnext1!=NULL)
	{
		//запоминаем элемент следующий от двух рассматриваемых
		pnext2=pnext1->pnext;
		//пока рассматриваемый элемент не встанет на своё место в выравненном 
		//в правильном порядке массиве, выполняем перестановку соседних элементов
		while (1)
		{
			//в случае если элемент стал первым в списке или если элемент 
			//левее его меньше, заканчиваем делать перестановки
			if (pnext1->pprev==NULL) break; 
			if (compare(pnext1,pnext1->pprev, attr)==1) break;
			//корректируем указатель на начало или конец если необходимо
			if (pnext1->pprev->pprev==NULL) *begin=pnext1;
			if (pnext1->pnext==NULL) *end=pnext1->pprev;
			//сама функция перестановки
			pnext1=insInv(pnext1->pprev,pnext1);
		}
		//переставляем указатель на элемент следующий от двух рассматриваемых
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

	printf("Введите имя пользователя: ");
	strcpy(login,"");
	//fflush(stdin);
	//fgets(login,15,stdin);
	//login[strlen(login)-1]='\0';	
	getLimStr(&login, 15, 6);

	printf("Пароль: ");
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
		//printf("есть нахождение");
	}
	if (n!=0) return 0; 
	else return 1;
}



void manageUsers() {

	int n, k=0;
	char strtemp[5], login[15], pass[15], tmplogin[16], tmppass[16];
	int flag=0;
	while (flag==0) {
		printf("\nУправление учётными записями пользователей\
			   \n1. Просмотр всех учётных записей пользователей\
			   \n2. Добавление новой учётной записи\
			   \n3. Удаление учётной записи\
			   \n4. Выйти в родительское меню\
			   \nВведите номер команды [1-4]:");
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
							printf("\n%2s %5s %15s %15s \n","# ","Роль ","Логин           ","Пароль         ");
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
				printf("\nВыберите роль добавляемого пользователя\
					   \n1. Администратор\
					   \n2. Пользователь\
					   \nВведите номер команды [1-2]:");
				check(2, &k);

				if (k==1) strcpy(role,"adm");
				else strcpy(role,"usr");
				fputs(role, pf);
				fprintf(pf,"\n");

				printf("\nВведите Имя пользователя: ");
				strcpy(login,"");
				//fflush(stdin);
				//fgets(login,15,stdin);
				//login[strlen(login)-1]='\0';
				getLimStr(&login, 15, 6);
				fputs(login, pf);
				fprintf(pf,"\n");

				printf("Пароль: ");
				strcpy(pass,"");
				//fflush(stdin);
				//fgets(pass,15,stdin);
				//pass[strlen(pass)-1]='\0';
				getLimStr(&pass, 15, 6);
				fputs(pass, pf);
				fprintf(pf,"\n");
				fclose(pf);
				printf("\nУчётная запись добавлена.");
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
							printf("\n%2s %5s %15s %15s \n","# ","Роль ","Логин           ","Пароль         ");
							printf("%s \n","-----------------------------------------");
							k++;
						}
						n++;
						printf("%-2d %-5s %-16s %-16s\n", n, strtemp, tmplogin, tmppass);
					}
				}
			}
			fclose(pf);

			printf("\nВведите номер пользователя в списке: ");
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
		printf("\nУправление файлом базы данных\
			   \n1. Сохранить произведённые изменения\
			   \n2. Сменить файл хранения данных\
			   \n3. Создать файл для хранения данных\
			   \n4. Выйти в главное меню\
			   \nВведите номер команды [1-4]:");
		check(4, &k);
		switch(k) 
		{
		case 1: {
			saveList(p,file);
			printf("Изменения сохранены в файл %s", file);
			break;
				}
		case 2: { 
			FILE *pf;
			char newdir[100]={""};
			printf("Введите директорию:\n");
			//fflush(stdin);
			//fgets(newdir,100,stdin);
			//newdir[strlen(newdir)-1]='\0';
			getLimStr(&newdir, 200, 100);
			pf=fopen(newdir,"r");
			if (pf!=NULL) {
				fclose(pf);
				strcpy(file,newdir);
				printf("База данных загружена.");
				loadList(p,newdir,pend,pbegin);
			} else printf("Ошибка загрузки файла базы данных");
			fflush(stdin);
			break;
				} 
		case 3: { 
			FILE *newfile;
			char newdir[100]={""};
			printf("Введите директорию:\n");
			//fflush(stdin);
			//fgets(newdir,100,stdin);
			//newdir[strlen(newdir)-1]='\0';
			getLimStr(&newdir, 200, 100);
			newfile=fopen(newdir,"w");
			if (newfile!=NULL) {
				strcpy(file,newdir);
				fclose(newfile);
				printf("База данных создана.");
			} else printf("Ошибка создания файла для хранения данных");
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
			printf("Введите номер команды [1-%d]:", k);
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
			printf("Необходимо ввести заново. Количество символов не должно превышать %d:\n", lim-1);
		}
	}
}
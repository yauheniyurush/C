//объ€вл€ем символьную константу в которой храним количество символов 
//в поле фио студента структуры Student
#define MAXFNAME 25

//объ€вл€ем структуру 
typedef struct tagStudent
{
	int    studNmb;			//номер в списке
	char   fname[MAXFNAME]; //фио студента
	int	   roomNmb;			//номер комнаты
	int    floor;			//этаж
	
	//в этих переменных храним ссылку на следующую, предыдущую св€занную структуру 
	struct tagStudent *pnext, *pprev;
} Student;

//объ€вл€ем прототипы функций используемых в программе
void print(Student *p);
void getUser(Student *p);
Student* addEnd(Student *p, Student *end, int stnumb);
void printList(Student *p);
void loadList(Student *p, char *file, Student **pend, Student **pbegin);
void saveList(Student *p, char *file);
int editStd(Student *p, Student **pend, Student **pbegin);
int deleteStd(Student *p, Student **pend, Student **pbegin);

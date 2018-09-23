//��������� ���������� ��������� � ������� ������ ���������� �������� 
//� ���� ��� �������� ��������� Student
#define MAXFNAME 25

//��������� ��������� 
typedef struct tagStudent
{
	int    studNmb;			//����� � ������
	char   fname[MAXFNAME]; //��� ��������
	int	   roomNmb;			//����� �������
	int    floor;			//����
	int	   marks[5][12];	//������ ����-� �� ���-�� ��������� �� 5 ������� ��� #��2 
	
	//� ���� ���������� ������ ������ �� ���������, ���������� ��������� ��������� 
	struct tagStudent *pnext, *pprev;
} Student;

//��������� ��������� ������� ������������ � ���������
void print(Student *p, char (*fnc)(char *));
void getUser(Student *p);
Student* addEnd(Student *p, Student *end, int stnumb);
void printList(Student *p,int k);
void loadList(Student *p, char *file, Student **pend, Student **pbegin);
void saveList(Student *p, char *file);
int editStd(Student *p, Student **pend, Student **pbegin);
int deleteStd(Student *p, Student **pend, Student **pbegin);
int printMarks(Student *p);
int printReg(Student *p);
int addMarks(Student *p);
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
	
	//� ���� ���������� ������ ������ �� ���������, ���������� ��������� ��������� 
	struct tagStudent *pnext, *pprev;
} Student;

//��������� ��������� ������� ������������ � ���������
void print(Student *p);
void getUser(Student *p);
Student* addEnd(Student *p, Student *end, int stnumb);
void printList(Student *p);
void loadList(Student *p, char *file, Student **pend, Student **pbegin);
void saveList(Student *p, char *file);
int editStd(Student *p, Student **pend, Student **pbegin);
int deleteStd(Student *p, Student **pend, Student **pbegin);

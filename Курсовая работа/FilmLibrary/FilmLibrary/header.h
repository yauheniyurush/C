//��������� ��������� � ������� ������ ���������� �������� 
#define MAXFNAME 25
#define ACTORSNAME 25
#define GENRE 15

//��������� ��������� ��� �������� ���. �� �����
struct tagActor
{
	char   name[ACTORSNAME];	//��� ��� �����
	int	   age;					//������� �����
	char   desc[100];			//�������� (���� � ����)
};

//��������� ��������� ��� �������� ���. � ������
typedef struct tagFilm
{
	int    filmNmb;				//ID ������
	char   fname[MAXFNAME];		//�������� ������
	char   genre[GENRE];		//����
	int    year;				//��� ������
	int    budget;				//������ ������
	int	   mark;				//�������������� ������ �� 10�� ������� �������
	struct tagActor actors[5];	//����� ����������� ������� ����
	//� ���� ���������� ������ ������ �� ���������, ���������� ��������� ��������� 
	struct tagFilm *pnext, *pprev;
} Film;


//��������� ��������� ������� ������������ � ���������
void getUser(Film *p);
Film* addEnd(Film *p, Film *end, int stnumb);
int editStd(Film *p, Film **pend, Film **pbegin);
int delActors(Film *p);
int editActors(Film *p);
int printActors(Film *p);
int addActors(Film *p);
int deleteStd(Film *p, Film **pend, Film **pbegin);
void saveList(Film *p, char *file);
void loadList(Film *p, char *file, Film **pend, Film **pbegin);
void printList(Film *p);
void print(Film *p);
void find(Film *p);
Film* insInv(Film *p1, Film *p2);
void sortByFeature(Film *p, Film **begin, Film **end);
int compare(Film *p1, Film *p2, int attr);
int checkLogPas(int k);
void manageUsers();
void fileManager(Film *p, char *file, Film **pend, Film **pbegin);
void check(int k, int *n);
void getLimStr(char *c, int l, int lim);
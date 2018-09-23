//��������� ��������� � ������� ������ ���������� �������� 
//� ���� �������� ��������� Merchant
#define MAXFNAME 25
#define QMAX 3


//��������� ��������� � ������� ����� ������� ���������� � ������
typedef struct tagMerchant
{
	int    merchNmb;			//����� � ������
	char   fname[MAXFNAME];		//�������� ������
	int	   price;				//���� ������
	int    sold;				//���������� ��������� �������
	
	//� ���� ���������� ������ ������ �� ���������, ���������� ��������� ��������� 
	struct tagMerchant *pnext, *pprev;
} Merchant;

//��������� ��������� � ������� ����� ������� ������� �� ��� ���������
typedef struct tagQueue {
  Merchant qu[QMAX];
  int rear, frnt;
} queue;

//��������� ��������� ������� ������������ � ���������
void print(Merchant *p);
void getUser(Merchant *p);
Merchant* addEnd(Merchant *p, Merchant *end, int stnumb);
void printList(Merchant *p);
void loadList(Merchant *p, char *file, Merchant **pend, Merchant **pbegin);
void saveList(Merchant *p, char *file);
int editStd(Merchant *p, Merchant **pend, Merchant **pbegin);
int deleteStd(Merchant *p, Merchant **pend, Merchant **pbegin);
void find(Merchant *p);
Merchant* insInv(Merchant *p1, Merchant *p2);
void insSort(Merchant *p, Merchant **begin, Merchant **end);
void signSort(Merchant *p, Merchant **begin, Merchant **end);
void exchSort(Merchant *p, Merchant **begin, Merchant **end);
void saveIntoFile(Merchant *p);
void saveFileMode(int n);
void loadListBinary(Merchant *p, char *file, Merchant **pend, Merchant **pbegin);
void saveListBinary(Merchant *p, char *file);
void printListQueue(Merchant *p, queue *q);
void flushQ(queue *q);
void insertQ(queue *q, Merchant *x);
void getUserQueue(queue *q, Merchant **begin, Merchant **end);
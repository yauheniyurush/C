//объ€вл€ем константу в которой храним количество символов 
//в поле название структуры Merchant
#define MAXFNAME 25

//объ€вл€ем структуру 
typedef struct tagMerchant
{
	int    merchNmb;			//номер в списке
	char   fname[MAXFNAME];		//название товара
	int	   price;				//цена товара
	int    sold;				//количество проданных позиций
	
	//в этих переменных храним ссылку на следующую, предыдущую св€занную структуру 
	struct tagMerchant *pnext, *pprev;
} Merchant;

//объ€вл€ем прототипы функций используемых в программе
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
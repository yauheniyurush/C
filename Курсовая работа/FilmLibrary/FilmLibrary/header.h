//объ€вл€ем константу в которой храним количество символов 
#define MAXFNAME 25
#define ACTORSNAME 25
#define GENRE 15

//объ€вл€ем структуру дл€ хранени€ инф. об актЄре
struct tagActor
{
	char   name[ACTORSNAME];	//им€ фам актЄра
	int	   age;					//возраст актЄра
	char   desc[100];			//описание (роль и проч)
};

//объ€вл€ем структуру дл€ хранени€ инф. о фильме
typedef struct tagFilm
{
	int    filmNmb;				//ID фильма
	char   fname[MAXFNAME];		//название фильма
	char   genre[GENRE];		//жанр
	int    year;				//год фильма
	int    budget;				//бюджет фильма
	int	   mark;				//характеристика фильма по 10ти бальной системе
	struct tagActor actors[5];	//актЄры исполнившие главные роли
	//в этих переменных храним ссылку на следующую, предыдущую св€занную структуру 
	struct tagFilm *pnext, *pprev;
} Film;


//объ€вл€ем прототипы функций используемых в программе
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
#ifndef DEFINES
#define DEFINES

#define startHealth         50  //початкова кількість життя
#define livesPerIteration   1   //скільки відбавляється життя за одну ітерацію
#define livesFromFood       5   //отримується життя за поглинену їжу
#define maxCodeSteps        30  //максимальна кількість виконаних команд на одну ітерацію однією клітинкою

#define fieldSizeX      20          //розмір поля
#define fieldSizeY      20
#define lifesAtStart    16         //кількість органзмів
#define wallsSeed   90

//
// Наступні визначення внутрішнього коду одиниці життя
//

#define maxMemory   64 // максимальний обьєм памяті


// Перейти до певної команди в програмі одиниці життя проводиться через значення від 0 до 63, для переходу до відповідного місьця

// Рух
#define moveLeft    64
#define moveRight   65
#define moveUp      66
#define moveDown    67

// Перевірка
//////
/// В результаті перевірки переходить на позиції відносно самого себе :
/// +1 - стіна
/// +2 - пусто
/// +3 - отрута
/// +4 - їжа
/// +5 - інший організм
//////
#define checkLeft   68
#define checkRight  69
#define checkUp     70
#define checkDown   71

#define itsWall     1
#define itsEmpty    2
#define itsPoison   3
#define itsFood     4
#define itsCreature 5
#define itsMax      5


// Перетворення з отрути на їжу
#define poisonLeft  72
#define poisonRight 73
#define poisonUp    74
#define poisonDown  75

#define commandSize 76


//// Перейти до певної команди в програмі одиниці життя проводиться через значення від 0 до 127, для переходу до відповідного місьця

//// Рух
//#define moveLeft    128
//#define moveRight   129
//#define moveUp      130
//#define moveDown    131

//// Перевірка
////////
///// В результаті перевірки переходить на позиції відносно самого себе :
///// +1 - стіна
///// +2 - пусто
///// +3 - отрута
///// +4 - їжа
///// +5 - інший організм
////////
//#define checkLeft   132
//#define checkRight  133
//#define checkUp     134
//#define checkDown   135

//#define itsWall     1
//#define itsEmpty    2
//#define itsPoison   3
//#define itsFood     4
//#define itsCreature 5
//#define itsMax      5


//// Перетворення з отрути на їжу
//#define poisonLeft  136
//#define poisonRight 137
//#define poisonUp    138
//#define poisonDown  139

//#define commandSize 140


#endif // DEFINES


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
#define moveFront   64
#define moveLeft    65
#define moveRight   66
#define moveBack    67

// Перевірка
//////
/// В результаті перевірки переходить на позиції відносно самого себе :
/// +1 - стіна
/// +2 - пусто
/// +3 - отрута
/// +4 - їжа
/// +5 - інший організм
//////
#define checkFront   68
#define checkLeft    69
#define checkRight   70
#define checkBack    71

#define itsWall     1
#define itsEmpty    2
#define itsPoison   3
#define itsFood     4
#define itsCreature 5
#define itsMax      5


// Перетворення з отрути на їжу
#define poisonFront 72
#define poisonLeft  73
#define poisonRight 74
#define poisonBack  75

// Поворот відносно себе
#define turnRight   76
#define turnLeft    77
#define turnBack    78

#define turnedTop   1
#define turnedRight 2
#define turnedLeft  0
#define turnedDown  3

#define commandSize 79

#endif // DEFINES


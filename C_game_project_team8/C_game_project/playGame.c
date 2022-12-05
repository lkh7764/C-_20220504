// 멀티소스 사용 - 임경화
#include "HEADER.h" //

#define TOTALMAXENEMY 20
#define TOTALMAXBALL 50
#define ITEM_MAX 3  //


struct tag_Enemy
{
    BOOL exist;
    int Type;
    int x, y;
    int Delta;
    int nFrame;
    int nStay;
}Enemy[TOTALMAXENEMY];

struct tag_Ball
{
    BOOL exist;
    int x, y;
    int nFrame;
    int nStay;
}Ball[TOTALMAXBALL];

struct iteminfo {   // 아이템 구조체 생성 - 김태현
    BOOL exist; 
    int Type; 
    int x, y; 
    int Delta; 
    int nFrame;
    int nStay;
}Item[ITEM_MAX];   //

void game_reset()    // 적 우주선, 투사체 초기화하는 함수 - 박상욱
{             
    for (int i = 0; i < TOTALMAXBALL; i++) {    //
        Ball[i].exist == FALSE; //
        Ball[i].y = 24; //
    }
    for (int j = 0; j < TOTALMAXENEMY; j++) {   //
        Enemy[j].exist = FALSE; //
        gotoxy(Enemy[j].x - 3, Enemy[j].y); //
        puts("       ");    //
    }
}

void printPlayerInfo(int fx, int Score, int hp) // 기존 코드 함수화 + HP 출력 추가
{
    gotoxy(fx - 3, 23);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);   // 글씨 색 지정 - 박상욱
    puts(" <<A>> ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    //
    gotoxy(1, 27);
    printf("점수 = %d", Score); 
    gotoxy(1, 29);  //
    printf("HP =           ");  //
    gotoxy(6, 29);  //
    for (int i = 0; i < hp; i++) {  //
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);   //
        printf("♡");    //
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    //
    }
}

void enemySet(int ballRate, int enemyRate, int ballSpeed, int stageMaxEnemy, int* Score, int* bx, int* by)  // 기존 코드 함수화 + 변수를 통해 enemy 속성 변경 - 임경화
{
    int i, j;
    BOOL bFound;

    const char* arEnemy[] = { " ;:^:; "," zZWZz ", " oO@Oo ", " <-=-> " };

    if (rand() % enemyRate == 0)
    {
        for (i = 0; i < stageMaxEnemy && Enemy[i].exist == TRUE; i++) { ; }
        if (i != stageMaxEnemy)
        {
            if ((rand() % 2) + 1 == 1)
            {
                Enemy[i].x = 6;
                Enemy[i].Delta = 1;
            }
            else
            {
                Enemy[i].x = 72;
                Enemy[i].Delta = -1;
            }

            for (;;)
            {
                Enemy[i].y = rand() % 9 + 2;
                for (bFound = FALSE, j = 0; j < stageMaxEnemy; j++) //
                {
                    if (Enemy[j].exist == TRUE && Enemy[j].y == Enemy[i].y)
                    {
                        bFound = TRUE;
                        break;
                    }
                }
                if (bFound == FALSE)
                {
                    break;
                }
            }
            Enemy[i].nFrame = Enemy[i].nStay = rand() % 6 + 1;
            Enemy[i].Type = rand() % (sizeof(arEnemy) / sizeof(arEnemy[0])); //random(sizeof(arEnemy) / sizeof(arEnemy[0]));
            Enemy[i].exist = TRUE;
        }
    }

    for (i = 0; i < TOTALMAXBALL; i++)
    {
        if (Ball[i].exist == FALSE)
            continue;

        if (--Ball[i].nStay == 0)
        {
            Ball[i].nStay = Ball[i].nFrame;
            gotoxy(Ball[i].x, Ball[i].y); putch(' ');

            if (Ball[i].y >= 23)
            {
                Ball[i].exist = FALSE;
            }
            else
            {
                Ball[i].y++;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                gotoxy(Ball[i].x, Ball[i].y); putch('*');
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
        }
    }

    for (i = 0; i < stageMaxEnemy; i++) {
        if (Enemy[i].exist == FALSE) continue;
        if (--Enemy[i].nStay == 0) {
            Enemy[i].nStay = Enemy[i].nFrame;
            if (Enemy[i].x >= 73 || Enemy[i].x <= 5) {
                Enemy[i].exist = FALSE;
                gotoxy(Enemy[i].x - 3, Enemy[i].y);
                puts("       ");
            }
            else
            {
                Enemy[i].x += Enemy[i].Delta;
                gotoxy(Enemy[i].x - 3, Enemy[i].y);
                puts(arEnemy[Enemy[i].Type]);

                if (rand() % ballRate == 0) {
                    for (j = 0; j < TOTALMAXBALL && Ball[j].exist == TRUE; j++) { ; }
                    if (j != TOTALMAXBALL) {
                        Ball[j].x = Enemy[i].x + 2;
                        Ball[j].y = Enemy[i].y + 1;
                        Ball[j].nFrame = Ball[j].nStay = Enemy[i].nFrame * ballSpeed;
                        Ball[j].exist = TRUE;
                    }
                }
            }
        }
    }

    for (int i = 0; i < stageMaxEnemy; i++)
    {
        if (Enemy[i].exist == FALSE)
            continue;

        if (Enemy[i].y == *by && abs(Enemy[i].x - *bx) <= 2)
        {
            gotoxy(bx, *by); putch(' ');
            *bx = -1;
            Enemy[i].exist = FALSE;
            gotoxy(Enemy[i].x - 3, Enemy[i].y);
            puts("       ");
            *Score += 7 - Enemy[i].nFrame;
            break;
        }
    }
}   //enemy를 제어하는 함수

void stageSet(int Score, int* ballRate, int* enemyRate, int* ballSpeed, int* stageMaxEnemy) //Score에 따라 enemy 속성을 변경하는 함수 추가 - 임경화
{
    if (Score == 10) {  //
        *ballRate = 10; //
    }
    else if (Score == 20) { //
        *enemyRate = 20;    //
    }
    else if (Score == 30) { //
        *ballSpeed = 3; //
        *stageMaxEnemy = 10;    //
    }
    else if (Score == 40) { //
        *enemyRate = 10;    //
        *stageMaxEnemy = 20;    //
        *ballSpeed = 2; //
    }
}

void UseDelEn() //화면에 출력된 적, 투사체의 일부를 없애주는 아이템 함수 추가 - 김태현
{
    for (int i = 0; i < TOTALMAXENEMY; i++) //
    {
        if (Enemy[i].exist == FALSE)    //
            continue;   //

        Enemy[i].exist = FALSE; //
        gotoxy(Enemy[i].x - 3, Enemy[i].y); //
        puts("       ");    //
        break;  //
    }
    for (int i = 0; i < TOTALMAXBALL; i++)  //
    {
        if (Ball[i].exist == FALSE) //
            continue;   //

        Ball[i].exist = FALSE;  //
        gotoxy(Ball[i].x, Ball[i].y);   //
        puts(" ");  //
        break;  //
    }


}

void UseAddHP(int* HP)  //HP를 회복하는 아이템 함수 추가 - 김태현
{
    if (*HP < 3)    //
    {
        *HP += 1;   //
    }
}

void itemSet(int* bx, int* by, int* hp)     //기존 함수를 응용하여 아이템에 대한 함수 추가 - 김태현
{
    int i, j;
    const char* arItem[] = { " <<S>> ", " <<P>> " };    //
    BOOL bFound;
    
    if (rand() % 500 == 0)
    {
        for (i = 0; i < ITEM_MAX && Item[i].exist == TRUE; i++) { ; }
        if (i != ITEM_MAX)
        {
            if ((rand() % 2) + 1 == 1)
            {
                Item[i].x = 6;
                Item[i].Delta = 1;
            }

            else
            {
                Item[i].x = 72;
                Item[i].Delta = -1;
            }

            for (;;)
            {
                Item[i].y = rand() % 10 + 1;
                for (bFound = FALSE, j = 0; j < ITEM_MAX; j++)
                {
                    if (Item[j].exist == TRUE && Item[j].y == Item[i].y)
                    {
                        bFound = TRUE;
                        break;
                    }
                }
                if (bFound == FALSE)
                {
                    break;
                }
            }
            Item[i].nFrame = Item[i].nStay = rand() % 6 + 1;
            Item[i].Type = rand() % (sizeof(arItem) / sizeof(arItem[0]));
            Item[i].exist = TRUE;
        }
    }

    for (i = 0; i < ITEM_MAX; i++)
    {
        if (Item[i].exist == FALSE)
            continue;

        if (Item[i].y == *by && abs(Item[i].x - *bx) <= 2)
        {
            gotoxy(*bx, *by); putch(' ');
            *bx = -1;
            Item[i].exist = FALSE;
            gotoxy(Item[i].x - 3, Item[i].y);
            puts("       ");
            
            if (Item[i].Type == 1)  //
            {
                UseDelEn(); //
            }
            else    //
            {
                UseAddHP(hp);   //
            }

            break;  //
        }
    }

    for (i = 0; i < ITEM_MAX; i++) {
        if (Item[i].exist == FALSE) continue;
        if (--Item[i].nStay == 0) {
            Item[i].nStay = Item[i].nFrame;
            if (Item[i].x >= 76 || Item[i].x <= 4) {
                Item[i].exist = FALSE;
                gotoxy(Item[i].x - 3, Item[i].y);
                puts("       ");
            }
            else
            {
                Item[i].x += Item[i].Delta;
                gotoxy(Item[i].x - 3, Item[i].y);
                puts(arItem[Item[i].Type]);
            }
        }
    }
}



void end(int end_score, int best_score) // 기존 코드 함수화 + 최고 점수 출력 기능 추가 - 황재민
{
    system("cls");  //
    
    gotoxy(30, 10);
    printf("==========================GAMEOVER==========================\n\n");
    gotoxy(56, 15);
    printf("점수=%d", end_score);
    gotoxy(54, 17); //
    printf("최고 점수=%d", best_score); //
    gotoxy(45, 19); //
    printf("시작하려면 아무키나 누르세요");  //
    CursorView(0);
    getch();    
    
    system("cls");  //
}

BOOL IsKeyDown(int Key)   // 기존 코드 함수화
{
    return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

boolean playerEnter(int count, int ch, int* fx, int Score, int* bx, int* by) {  // 기존 코드 함수화
    if (count % 2 == 0)
    {
        if (IsKeyDown(VK_LEFT))
        {
            if (*fx > 6)
                *fx = *fx - 1;
        }
        if (IsKeyDown(VK_RIGHT))
        {
            if (*fx < 72)
                *fx = *fx + 1;
        }
    }

    if (kbhit())
    {
        ch = getch();
        if (ch == 0xE0 || ch == 0)
        {
            getch();
        }
        else
        {
            switch (ch)
            {
            case ' '://Space
                if (*bx == -1)
                {
                    *bx = *fx;
                    *by = 23;
                }
                break;
            case ESC:
                return FALSE;
            }
        }
    }

    if (*bx != -1)
    {
        gotoxy(*bx, *by);
        putch(' ');
        if (*by == 2)
        {
            *bx = -1;
        }
        else
        {
            *by = *by - 1;
            gotoxy(*bx, *by);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            putch('i');
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    }
}

boolean hp_check(int hp, int fx) {  //기존 코드 함수화 + 플레이어 hp 기능 추가  - 박상욱
    int count = 0;
    for (int i = 0; i < TOTALMAXBALL; i++) {
        if (Ball[i].exist == FALSE) continue;
        if (Ball[i].y == 23 && abs(Ball[i].x - fx) <= 2) {
            count++;
            Ball[i].y++;
            if (hp <= 1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                gotoxy(fx - 3, 21); puts("   .   ");
                gotoxy(fx - 3, 22); puts(" .  . .");
                gotoxy(fx - 3, 23); puts("..:V:..");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                Sleep(1000);
                count++;
            }
        }
    }
    if (count == 1) {   //
        return TRUE;    //
    }
    if (count == 2) {   //
        return FALSE;   //
    }
}
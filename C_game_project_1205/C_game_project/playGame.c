#include "HEADER.h"

#define TOTALMAXENEMY 20
#define TOTALMAXBALL 50


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

void game_reset() 
{             
    for (int i = 0; i < TOTALMAXBALL; i++) {
        Ball[i].exist == FALSE;
        Ball[i].y = 24;
    }
    for (int j = 0; j < TOTALMAXENEMY; j++) {
        Enemy[j].exist = FALSE;
        gotoxy(Enemy[j].x - 3, Enemy[j].y);
        puts("       ");
    }
}   //적 우주선, 투사체 초기화

void printPlayerInfo(int fx, int Score, int hp)
{
    gotoxy(fx - 3, 23);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    puts(" <<A>> ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(1, 27);
    printf("점수 = %d", Score);
    gotoxy(1, 29);
    printf("HP =           ");
    gotoxy(6, 29);
    for (int i = 0; i < hp; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("♡");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}   //플레이어와 플레이어의 정보를 출력하는 함수

void enemySet(int ballRate, int enemyRate, int ballSpeed, int stageMaxEnemy, int* Score, int* bx, int* by)
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
                for (bFound = FALSE, j = 0; j < stageMaxEnemy; j++)
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

void stageSet(int Score, int* ballRate, int* enemyRate, int* ballSpeed, int* stageMaxEnemy) 
{
    if (Score == 10) {
        *ballRate = 10;
    }
    else if (Score == 20) {
        *enemyRate = 20;
    }
    else if (Score == 30) {
        *ballSpeed = 3;
        *stageMaxEnemy = 10;
    }
    else if (Score == 40) {
        *enemyRate = 10;
        *stageMaxEnemy = 20;
        *ballSpeed = 2;
    }
}

void end(int end_score, int best_score)
{
    system("cls");
    
    gotoxy(30, 10);
    printf("==========================GAMEOVER==========================\n\n");
    gotoxy(56, 15);
    printf("점수=%d", end_score);
    gotoxy(54, 17);
    printf("최고 점수=%d", best_score);
    gotoxy(45, 19);
    printf("시작하려면 아무키나 누르세요");
    CursorView(0);
    getch();
    
    system("cls");
}   //게임오버 화면을 출력하는 함수

BOOL IsKeyDown(int Key)
{
    return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

boolean playerEnter(int count, int ch, int* fx, int Score, int* bx, int* by) {
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
}   //입력값에 따라 플레이어 움직임or상태를 제어하는 함수

boolean hp_check(int hp, int fx) {           
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
                gotoxy(1, 25);
                printf("HP =           ");
                Sleep(1000);
                count++;
            }
        }
    }
    if (count == 1) {
        return TRUE;
    }
    if (count == 2) {
        return FALSE;
    }
}   //플레이어 체력 함수
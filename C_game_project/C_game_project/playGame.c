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
}
Enemy[TOTALMAXENEMY];

struct tag_Ball
{
    BOOL exist;
    int x, y;
    int nFrame;
    int nStay;
}
Ball[TOTALMAXBALL];

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
}   //�� ���ּ�, ����ü �ʱ�ȭ

void printPlayerInfo(int fx, int Score, int hp)
{
    gotoxy(fx - 3, 23);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    puts(" <<A>> ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(1, 26);
    printf("���� = %d", Score);
    gotoxy(1, 27);
    printf("HP =           ");
    gotoxy(6, 27);
    for (int i = 0; i < hp; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("��");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}   //�÷��̾�� �÷��̾��� ������ ����ϴ� �Լ�

void enemySet(int ballRate, int enemyRate, int stageMaxBall, int stageMaxEnemy, int* Score, int* bx, int* by)
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

    for (i = 0; i < stageMaxBall; i++)
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
                    for (j = 0; j < stageMaxBall && Ball[j].exist == TRUE; j++) { ; }
                    if (j != stageMaxBall) {
                        Ball[j].x = Enemy[i].x + 2;
                        Ball[j].y = Enemy[i].y + 1;
                        Ball[j].nFrame = Ball[j].nStay = Enemy[i].nFrame * 6;
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
}   //enemy�� �����ϴ� �Լ�

void end(int end_score)
{
    system("cls");
    
    gotoxy(30, 10);
    printf("==========================GAMEOVER==========================\n\n");
    gotoxy(58, 15);
    printf("����=%d\n\n\n\n\n\n\n\n\n\n\n\n", end_score);
    printf("�ƹ�Ű�� ��������");
    CursorView(0);
    getch();
    
    system("cls");
}   //���ӿ��� ȭ���� ����ϴ� �Լ�

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
}   //�Է°��� ���� �÷��̾� ������or���¸� �����ϴ� �Լ�

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
}   //�÷��̾� ü�� �Լ�
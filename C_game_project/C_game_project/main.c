#include "HEADER.h"


void gotoxy(int x, int y) 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void printTitle()
{
    printf("���� ���� ȭ��\n\n�ƹ�Ű�� ��������");
}   //Ÿ��Ʋȭ���� ����ϴ� �Լ�

void printSide() 
{
    int x, y;
    for (y = 1; y < 26; y++) {
        for (int x = 1; x < 78; x++) {
            if (y == 1 || y == 25) {
                gotoxy(x, y);
                printf("��");
            }
            else {
                if (x == 1 || x == 77) {
                    gotoxy(x, y);
                    printf("��");
                }
            }
        }
    }
}   //�÷��̱��� ���м��� ����ϴ� �Լ�

void how_to_play() {
    gotoxy(47, 26);
    printf("��������������������           ���������� ����������");
    gotoxy(47, 27);
    printf("��  SPACE ��           �� �禢 �� �榢");
    gotoxy(47, 28);
    printf("��������������������           ���������� ����������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(61, 27);
    printf("Move : ");
    gotoxy(38, 27);
    printf("Attack : ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}   //���۹��� ����ϴ� �Լ�

void main()
{
    system("cls");

    BOOL gameStart = TRUE;          //��ü ����
    BOOL gamePlay = TRUE;           //���� ����

    while (gameStart) {
        static int ch;
        int count;
        int hp = 3;
        int fx;
        int Score = 0;
        int bx, by;
        int ballRate, enemyRate, stageMaxBall, stageMaxEnemy;

        srand((unsigned)time(NULL));
        system("cls");
        CursorView(0);

        fx = 60;
        bx = -1;
        ballRate = 20;
        enemyRate = 50;
        stageMaxBall = 10;
        stageMaxEnemy = 5;

        game_reset();
        
        printTitle();
        getch();
        system("cls");

        gamePlay = TRUE;

        while (gamePlay) {
            for (count = 0;; count++) {
                if (playerEnter(count, ch, &fx, Score, &bx, &by) == FALSE) {
                    gamePlay = FALSE;
                    end(Score);
                    break;
                }

                enemySet(ballRate, enemyRate, stageMaxBall, stageMaxEnemy, &Score, &bx, &by);
                if (Score == 50) {
                    stageMaxBall = 20;
                    stageMaxEnemy = 10;
                }
                else if (Score == 100) {
                    ballRate = 10;
                }
                else if (Score == 150) {
                    stageMaxBall = 30;
                    enemyRate = 30;
                }
                else if (Score == 200) {
                    ballRate = 5;
                }

                BOOL check = hp_check(hp, fx);
                if (check == TRUE) {                    //�÷��̾� ü�� ����
                    hp -= 1;
                }
                if (check == FALSE) {                   //���� ����
                    gamePlay = FALSE;
                    end(Score);
                    break;
                }

                printPlayerInfo(fx, Score, hp);
                printSide();
                how_to_play();

                Sleep(40);
            }
        }
    }
}
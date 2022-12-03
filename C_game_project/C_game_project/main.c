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
    printf("대충 시작 화면\n\n아무키나 누르세요");
}   //타이틀화면을 출력하는 함수

void printSide() 
{
    int x, y;
    for (y = 1; y < 26; y++) {
        for (int x = 1; x < 78; x++) {
            if (y == 1 || y == 25) {
                gotoxy(x, y);
                printf("■");
            }
            else {
                if (x == 1 || x == 77) {
                    gotoxy(x, y);
                    printf("■");
                }
            }
        }
    }
}   //플레이구역 구분선을 출력하는 함수

void how_to_play() {
    gotoxy(47, 26);
    printf("┌────────┐           ┌───┐ ┌───┐");
    gotoxy(47, 27);
    printf("│  SPACE │           │ ←│ │ →│");
    gotoxy(47, 28);
    printf("└────────┘           └───┘ └───┘");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(61, 27);
    printf("Move : ");
    gotoxy(38, 27);
    printf("Attack : ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}   //조작법을 출력하는 함수

void main()
{
    system("cls");

    BOOL gameStart = TRUE;          //전체 루프
    BOOL gamePlay = TRUE;           //게임 루프

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
                if (check == TRUE) {                    //플레이어 체력 변경
                    hp -= 1;
                }
                if (check == FALSE) {                   //게임 종료
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
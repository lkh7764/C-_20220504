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
    gotoxy(30, 13);
    printf("S   H   O   O   T   I   N   G       G   A   M   E");
    gotoxy(40, 15);
    printf("�����Ϸ��� �ƹ� Ű�� ��������");
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
    gotoxy(47, 27);
    printf("��������������������           ���������� ����������");
    gotoxy(47, 28);
    printf("��  SPACE ��           �� �禢 �� �榢");
    gotoxy(47, 29);
    printf("��������������������           ���������� ����������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(61, 28);
    printf("Move : ");
    gotoxy(38, 28);
    printf("Attack : ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}   //���۹��� ����ϴ� �Լ�

void best_score_system(int* best_score)
{
    FILE* file = fopen("score.txt", "r+"); // score������ ���� 
    if (file == 0)
    {
        *best_score = 0;
    } //������ ������ �ְ������� 0�� ���� 
    else
    {
        fscanf_s(file, "%d", best_score); // ������ ������ �ְ������� �ҷ��� 
        fclose(file); //���� ���� 
    }
}

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
        int best_score = 0;
        int bx, by;
        int ballRate, enemyRate, ballSpeed, stageMaxEnemy;

        srand((unsigned)time(NULL));
        system("cls");
        CursorView(0);
        best_score_system(&best_score);

        fx = 60;
        bx = -1;
        ballRate = 20;
        enemyRate = 50;
        ballSpeed = 6;
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
                    end(Score, best_score);
                    break;
                }

                enemySet(ballRate, enemyRate, ballSpeed, stageMaxEnemy, &Score, &bx, &by);
                stageSet(Score, &ballRate, &enemyRate, &ballSpeed, &stageMaxEnemy);

                if (Score > best_score)
                {
                    FILE* file = fopen("score.txt", "wt");

                    if (file == 0)
                    {
                        printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
                    }
                    else
                    {
                        fprintf(file, "%d", Score);
                        fclose(file);
                    }
                }

                BOOL check = hp_check(hp, fx);
                if (check == TRUE) {                    //�÷��̾� ü�� ����
                    hp -= 1;
                }
                if (check == FALSE) {                   //���� ����
                    gamePlay = FALSE;
                    end(Score, best_score);
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
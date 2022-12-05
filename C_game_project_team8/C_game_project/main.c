//���Ӹ�: ����� ���� ����
//C277011 ������
//C277015 �ڻ��
//C277030 �Ӱ�ȭ
//C277039 Ȳ���

#include "HEADER.h" // ������� �߰� - �Ӱ�ȭ

void gotoxy(int x, int y) 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}   // ���� �ڵ� �Լ�ȭ

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}   // ���� �ڵ� �Լ�ȭ

void printTitle()   // Ÿ��Ʋȭ���� ����ϴ� �Լ� �߰� - �Ӱ�ȭ&�ڻ��
{
    gotoxy(30, 13); //
    printf("S   H   O   O   T   I   N   G       G   A   M   E");    //
    gotoxy(40, 16); //
    printf("�����Ϸ��� �ƹ� Ű�� ��������"); //
}

void printSide()   // �÷��̱��� ���м��� ����ϴ� �Լ� �߰� - �Ӱ�ȭ
{
    int x, y;   //
    for (y = 1; y < 26; y++) {  //
        for (int x = 1; x < 78; x++) {  //
            if (y == 1 || y == 25) {    //  
                gotoxy(x, y);   //
                printf("��");    //
            }
            else {  //
                if (x == 1 || x == 77) {    //
                    gotoxy(x, y);   //
                    printf("��");    //
                }
            }
        }
    }
}

void how_to_play() {   // ���۹��� ����ϴ� �Լ� �߰� - �ڻ��
    gotoxy(47, 27); //
    printf("��������������������           ���������� ����������"); //
    gotoxy(47, 28); //
    printf("��  SPACE ��           �� �禢 �� �榢");   //
    gotoxy(47, 29); //
    printf("��������������������           ���������� ����������"); //
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);    //���� ������ �����ϴ� �ڵ� �߰�
    gotoxy(61, 28); //
    printf("Move : ");  //
    gotoxy(38, 28); //
    printf("Attack : ");    //
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    //���� ������ �����ϴ� �ڵ� �߰�
}

void best_score_system(int* best_score) // ���� ������Ͽ� �ְ� ������ �����ϰ� �ҷ����� �Լ� - Ȳ���
{
    FILE* file = fopen("score.txt", "r+");  //
    if (file == 0)  //
    {
        *best_score = 0;    //
    }
    else    //
    {
        fscanf_s(file, "%d", best_score);   //
        fclose(file);   //
    }
}

void main()
{
    system("cls");  //

    BOOL gameStart = TRUE;  //
    BOOL gamePlay = TRUE;   //

    while (gameStart) {/// ���� ���� ��� �߰� - �ڻ��
        static int ch;
        int count;
        int hp = 3; //
        int fx; //�������� -> ��������
        int bx, by; //�������� -> ��������
        int Score = 0;  //�������� -> ��������
        int best_score = 0; //
        int ballRate, enemyRate, ballSpeed, stageMaxEnemy;  //

        srand((unsigned)time(NULL));
        system("cls");  //
        CursorView(0);
        best_score_system(&best_score); //

        fx = 60;
        bx = -1;
        ballRate = 20;  //
        enemyRate = 50; //
        ballSpeed = 6;  //
        stageMaxEnemy = 5;  //

        game_reset();   //
        
        printTitle();   //
        getch();    //
        system("cls");  //

        gamePlay = TRUE;    //

        while (gamePlay) {  //
            for (count = 0;; count++) {
                if (playerEnter(count, ch, &fx, Score, &bx, &by) == FALSE) {    //
                    gamePlay = FALSE;   //
                    end(Score, best_score); //
                    break;  //
                }

                enemySet(ballRate, enemyRate, ballSpeed, stageMaxEnemy, &Score, &bx, &by);  //
                stageSet(Score, &ballRate, &enemyRate, &ballSpeed, &stageMaxEnemy); //

                itemSet(&bx, &by, &hp); //

                if (Score > best_score) //
                {
                    FILE* file = fopen("score.txt", "wt");  //

                    if (file == 0)  //                                       
                    {
                        printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");  //
                    }
                    else//
                    {
                        fprintf(file, "%d", Score); //
                        fclose(file);   //
                    }
                }
                
                BOOL check = hp_check(hp, fx);  //
                if (check == TRUE) {    //
                    hp -= 1;    //
                }
                if (check == FALSE) {   //
                    gamePlay = FALSE;   //
                    end(Score, best_score); //
                    break;  //
                }

                printPlayerInfo(fx, Score, hp); //
                printSide();    //
                how_to_play();  //

                Sleep(40);
            }
        }
    }
}
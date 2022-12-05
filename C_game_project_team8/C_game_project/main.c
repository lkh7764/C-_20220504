//게임명: 비행기 슈팅 게임
//C277011 김태현
//C277015 박상욱
//C277030 임경화
//C277039 황재민

#include "HEADER.h" // 헤더파일 추가 - 임경화

void gotoxy(int x, int y) 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}   // 기존 코드 함수화

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}   // 기존 코드 함수화

void printTitle()   // 타이틀화면을 출력하는 함수 추가 - 임경화&박상욱
{
    gotoxy(30, 13); //
    printf("S   H   O   O   T   I   N   G       G   A   M   E");    //
    gotoxy(40, 16); //
    printf("시작하려면 아무 키나 누르세요"); //
}

void printSide()   // 플레이구역 구분선을 출력하는 함수 추가 - 임경화
{
    int x, y;   //
    for (y = 1; y < 26; y++) {  //
        for (int x = 1; x < 78; x++) {  //
            if (y == 1 || y == 25) {    //  
                gotoxy(x, y);   //
                printf("■");    //
            }
            else {  //
                if (x == 1 || x == 77) {    //
                    gotoxy(x, y);   //
                    printf("■");    //
                }
            }
        }
    }
}

void how_to_play() {   // 조작법을 출력하는 함수 추가 - 박상욱
    gotoxy(47, 27); //
    printf("┌────────┐           ┌───┐ ┌───┐"); //
    gotoxy(47, 28); //
    printf("│  SPACE │           │ ←│ │ →│");   //
    gotoxy(47, 29); //
    printf("└────────┘           └───┘ └───┘"); //
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);    //글자 색상을 지정하는 코드 추가
    gotoxy(61, 28); //
    printf("Move : ");  //
    gotoxy(38, 28); //
    printf("Attack : ");    //
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    //글자 색상을 지정하는 코드 추가
}

void best_score_system(int* best_score) // 파일 입출력하여 최고 점수를 저장하고 불러오는 함수 - 황재민
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

    while (gameStart) {/// 게임 루프 기능 추가 - 박상욱
        static int ch;
        int count;
        int hp = 3; //
        int fx; //전역변수 -> 지역변수
        int bx, by; //전역변수 -> 지역변수
        int Score = 0;  //전역변수 -> 지역변수
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
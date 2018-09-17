#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

const char SPACE= '-';
const char X_SYMBOL = 'X';
const char O_SYMBOL = 'O';

void play_game()
{
    printf("Xs and Os!");
    struct game* p_game_info = (struct game*) malloc(sizeof(struct game)* 1);
    initialise_game (p_game_info);
    draw_banner();


    display_board(p_game_info->board);

    while (p_game_info->finished == False)
    {
        display_board_positions(p_game_info);
        print_status(p_game_info);
        process_move(p_game_info);

    }
    print_status(p_game_info);
    free(p_game_info);
}

void initialise_game(struct game* p_game_info)
{
    p_game_info->status = P1_TURN;
    for (int r = 0; r < 3; r++){
         printf("\n");
        for (int i = 0; i < 3; i++){
            p_game_info->board[r][i] = SPACE;
        }
    }

    p_game_info->finished = False;
    char name1[MAX_NAME_LEN];
    char name2[MAX_NAME_LEN];
    printf("Name 1:\n");
    gets(name1);
    printf("Name 2:\n");
    gets(name2);
    int rand = random();
    int other = 1;
    if (rand == 1)
    {
        other = 0;
    }
    strncpy(p_game_info->playerNames[rand], name1,MAX_NAME_LEN);
    strncpy(p_game_info->playerNames[other], name2,MAX_NAME_LEN);
    p_game_info->stepCounter = 0;
}

int random(){
    srand(time(0));
    int res = rand() % 2;
    return res;
}

void draw_banner()
{
    printf("---------------\nGAME STATUS\n---------------");
}
void display_board(struct game* p_game_info)
{
    for (int r = 0; r < 3; r++){
         printf("\n----- ----- -----\n");
        for (int i = 0; i < 3; i++){
            printf("  %c  |", p_game_info->board[r][i]);
        }
    }
}
void print_status(struct game* p_game_info)
{
    if (p_game_info->finished == False)
    {
        if (p_game_info->status == P1_TURN)
        {
            printf("\n\n%s's Turn\n", p_game_info->playerNames[0]);
        }
        else
        {
            printf("\n\n%s's Turn\n", p_game_info->playerNames[1]);
        }
    }
    else
    {
        if (p_game_info->status == P1_WON)
        {
            printf("\nWell done %s you have won", p_game_info->playerNames[0]);
        }
        else if (p_game_info->status == P2_WON)
        {
            printf("\nWell done %s you have won", p_game_info->playerNames[1]);
        }
        else
        {
            printf("\nGame Over. It's a draw");
        }
    }
}
void display_board_positions(struct game* p_game_info)
{
  int counter = 0;
  for (int r = 0; r < 3; r++){
         printf("\n----- ----- -----\n");
        for (int i = 0; i < 3; i++){
            printf("  %d  |", counter);
            counter++;
        }
    }
}
void get_row_col(int input,int* pRow, int* pCol)
{
    *pRow = input / 3;
    *pCol = input % 3;
}

void process_move(struct game* p_game_info)
{
    int userInput = -1;
    int row = -1;
    int col = -1;
    printf("\nEnter number: ");
    scanf("%d", &userInput);
    if (p_game_info->stepCounter == 8)
    {
        p_game_info->status = DRAW;
        p_game_info->finished = True;
    }
    if (userInput > -1 && userInput < 9)
    {
        get_row_col(userInput, &row, &col);
        if (p_game_info->board[row][col] == SPACE)
        {
            p_game_info->stepCounter++;
            if(p_game_info->status == P1_TURN)
            {
                p_game_info->board[row][col] = X_SYMBOL;
                p_game_info->status = P2_TURN;
            }
            else
            {
               p_game_info->board[row][col] = O_SYMBOL;
               p_game_info->status = P1_TURN;
            }
            winSolutions(p_game_info);
        }
        else
        {
                printf("slot is already used");
        }
        display_board(p_game_info->board);
    }
    else
    {
        printf("invalid input");
        boolean finish = False;
        char dummy_char = userInput;
        while (finish == False) {
		if (dummy_char == '\n')
			finish = True;
		else
			dummy_char = getchar();
        }
        process_move(p_game_info);
    }
}

void winSolutions(struct game* p_game_info)
{
    int win[8][6] = {{0,0,0,1,0,2},{1,0,1,1,1,2},{2,0,2,1,2,2},{0,0,1,0,2,0},{0,1,1,1,2,1},{0,2,1,2,2,2},{0,0,1,1,2,2},{0,2,1,1,2,0}};

    char turn = O_SYMBOL;
    int count = 0;

    if (p_game_info->status == P2_TURN)
    {
        turn = X_SYMBOL;
    }

    for (int i = 0; i < 8; i++){
        for (int c = 0; c < 6; c = c+2){
            if (p_game_info->board[win[i][c]][win[i][c+1]] == turn)
            {
                count++;
            }
        }
        if (count == 3 && turn == X_SYMBOL)
        {
            p_game_info->status = P1_WON;
            p_game_info->finished = True;
            break;
        }
        else if (count == 3 && turn == O_SYMBOL)
        {
            p_game_info->status = P2_WON;
            p_game_info->finished = True;
            break;
        }
        else
        {
            count = 0;
        }
    }
}

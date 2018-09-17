#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define MAX_NAME_LEN 50

enum Bool { False, True };
enum status { P1_TURN, P2_TURN, P1_WON, P2_WON, DRAW };
typedef enum Bool boolean;

struct game {
    char board[3][3];
    char playerNames[2][MAX_NAME_LEN];
    int status;
    boolean finished;
    int stepCounter;
};

void play_game();

void initialise_game(struct game* p_game_info);

int random();

void draw_banner();

void display_board(struct game* p_game_info);

void print_status(struct game* p_game_info);

void display_board_positions(struct game* p_game_info);

void get_row_col(int input,int* pRow, int* pCol);

void process_move(struct game* p_game_info);

void winSolutions(struct game* p_game_info);

#endif // GAME_H_INCLUDED

#define ROWS 8
#define COLS 8

// color data type - This will represent a cell in board
typedef enum o_color
{
  WHITE = 'W',
  BLACK = 'B',
  EMPTY = ' ',
} o_color;

// player data type
typedef struct o_player 
{
  char name[20];
  o_color discColor;
  int score;
} o_player;

// board data type
typedef struct o_board
{
  o_color cells[ROWS][COLS];
} o_board;


/* Function Declarations */

/**
 * Precondition : board should be properly allocated memory
 * Postcondition: All cells of board are empty, only center
 *                cells have discs
 * Return       : None
 **/
void board_init(o_board *board);

/**
 * Precondition : board should be properly allocated memory
 * Postcondition: board is printed in the required format
 * Return       : None
 **/
void print_board(o_board *board);

/**
 * Precondition : board should be properly allocated memory,
 *                player1 should be initialized,
 *                player2 should be initialized
 * Postcondition: player1 has score equal to total black discs
 *                on board;
 *                player2 has score equal to total white discs
 *                on board
 * Return       : None
 **/
void update_score(o_board *board, o_player *player1, o_player *player2);

/**
 * Precondition : board should be properly allocated memory,
 *                player should be intialized,
 *                cell should contain a valid input
 * Postcondition: board discs will be changed according to new input
 * Return       : Total cells changed on the board
 *                New disc will only be inserted, if at least one
 *                change occurs
 **/
int make_turn(o_board *board, o_player* player, char cell[2]);

/**
 * Precondition : board should be properly allocated memory,
 *                player should be intialized,
 *                cell should contain a valid input
 * Postcondition: No change will occur in any parameter
 * Return       : Count of valid moves for the player will be 
 *                returned
 **/
int has_valid_move(o_board *board, o_player *player);
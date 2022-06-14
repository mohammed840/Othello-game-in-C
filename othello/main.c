#include <stdio.h>
#include <fcntl.h>
#include "othello.h"

int main()
{
  /* Declarations */
  o_board othelloBoard;       // game board
  o_player players[2];        // players (0- Black) (1- White)
  char cell[2];               // user input
  int turn;                   // player's turn

  /* Initialization */
  printf("\t***\tWelcome to Othello!\t***\n");
  printf("Enter name of Player 1 (Black): ");
  scanf("%s", players[0].name);
  printf("Enter name of Player 2 (White): ");
  scanf("%s", players[1].name);
  players[0].discColor = BLACK;
  players[1].discColor = WHITE;

  board_init(&othelloBoard);  // board intialization
  update_score(&othelloBoard, &players[0], &players[1]);  //players score updation

  turn = 0;                   // black will have first turn
  //while any of the players have valid move
  while (has_valid_move(&othelloBoard, &players[0]) || has_valid_move(&othelloBoard, &players[1]))
  {
    //print the board with score
    printf("\n\t\tScore: %s (Black) %d:%d %s (White)\n", players[0].name, players[0].score, players[1].score, players[1].name);
    print_board(&othelloBoard);

    //if the current player does not have move left, pass!
    if (! has_valid_move(&othelloBoard, &players[turn]) )
    {
      printf("%s has no possible move. The turn is passed!!!\n", players[turn].name);
    }
    else
    {
      //user input
      printf("(%s's turn) Enter the cell: ", players[turn].name);
      scanf("%s", cell);

      //while does not get a valid move as input
      while (make_turn(&othelloBoard, &players[turn], cell) == 0)
      {
        printf("Error: This move is not valid. Try again!!!\n");
        printf("(%s's turn) Enter the cell: ", players[turn].name);
        scanf("%s", cell);
      }
    }
    //update the scores now
    update_score(&othelloBoard, &players[0], &players[1]);
    turn = (turn + 1) % 2;    // update the turn
  }

  printf("\t***\tGame Over\t***\n");

  /* Storing results in a file */
  int winner;
  if (players[0].score > players[1].score) winner = 0;
  else if (players[0].score < players[1].score) winner = 1;
  else winner = -1;           // if the match is draw

  FILE* out = fopen("result.txt", "w");
  fprintf(out, "%s's score: %d\n", players[0].name, players[0].score);
  fprintf(out, "%s's score: %d\n", players[1].name, players[1].score);
  if (winner == -1)
    fprintf(out, "The game ends with a draw!!!\n");
  else
    fprintf(out, "Winner: %s\n", players[winner].name);
  return 0;
}
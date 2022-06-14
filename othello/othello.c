#include <stdio.h>
#include <stdlib.h>
#include "othello.h"

void board_init(o_board *board)
{
  // iniatlize board with all cells empty
  for (int i = 0; i < ROWS; ++i)
    for (int j = 0; j < COLS; ++j)
      board->cells[i][j] = EMPTY;

  // fill the center cells
  board->cells[3][3] = board->cells[4][4] = WHITE;
  board->cells[3][4] = board->cells[4][3] = BLACK;
}

void print_board(o_board *board) 
{
  printf("\t\t    --- --- --- --- --- --- --- --- \n");
  for (int i = 0; i < ROWS; ++i)
  {
    printf("\t\t%d  ", (i+1));
    for (int j = 0; j < COLS; ++j) 
    {
        printf("| %c ", board->cells[i][j]);
    }
    printf("|\n");
  }
  printf("\t\t    --- --- --- --- --- --- --- --- \n");
  printf("\t\t     a   b   c   d   e   f   g   h  \n");
}

void update_score(o_board *board, o_player *player1, o_player *player2) 
{
  // reset the scores first
  player1->score = 0;
  player2->score = 0;
  
  // count total dics of each player, and update the score
  for (int i = 0; i < ROWS; ++i) 
    for (int j = 0; j < COLS; ++j) 
    {
      if (board->cells[i][j] == player1->discColor)
        player1->score += 1;
      else if (board->cells[i][j] == player2->discColor)
        player2->score += 1;
    }
}

int make_turn(o_board *board, o_player *player, char cell[2]) 
{
  // convert the user input into indices
  int col = cell[0] - 'a';
  int row = cell[1] - '1';

  // if the cell is not empty, move is not made
  if (board->cells[row][col] != EMPTY) return 0;

  int changed = 0;          // total directions changed after insertion
  int count;                // count total other colour tiles between two same tiles
  int rowItr;               // row iterator
  int colItr;               // column iterator

  //left direction
  colItr = col;
  count = 0;
  while (colItr > 0)
  {
    colItr -= 1;
    // if the opposite cell is empty, cells cannot be changed here
    if (board->cells[row][colItr] == EMPTY) break;
    // if same color found in the searching direction
    if (player->discColor == board->cells[row][colItr])
    {
      // if found any other color between two, then updation is possible
      if (count) 
      {
        changed += 1;
        for (int j = col; j > colItr; --j)
          board->cells[row][j] = player->discColor;
      }
     break;
    }
    // count total dics found of other color
    else ++count;
  }

  //right direction
  colItr = col;
  count = 0;
  while (colItr < 7)
  {
    colItr += 1;
    if (board->cells[row][colItr] == EMPTY) break;
    if (player->discColor == board->cells[row][colItr])
    {
      if (count) 
      {
        changed += 1;
        for (int j = col; j < colItr; ++j)
          board->cells[row][j] = player->discColor;
      }
     break;
    }
    else ++count;
  }

  //up direction
  rowItr = row;
  count = 0;
  while (rowItr > 0)
  {
    rowItr -= 1;
    if (board->cells[rowItr][col] == EMPTY) break;
    if (player->discColor == board->cells[rowItr][col])
    {
      if (count) 
      {
        changed += 1;
        for (int i = row; i > rowItr; --i)
          board->cells[i][col] = player->discColor;
      }
     break;
    }
    else ++count;
  }

  //down direction
  rowItr = row;
  count = 0;
  while (rowItr < 7)
  {
    rowItr += 1;
    if (board->cells[rowItr][col] == EMPTY) break;
    if (player->discColor == board->cells[rowItr][col])
    {
      if (count) 
      {
        changed += 1;
        for (int i = row; i < rowItr; ++i)
          board->cells[i][col] = player->discColor;
      }
     break;
    }
    else ++count;
  }

  //downright direction
  rowItr = row;
  colItr = col;
  count = 0;
  while (rowItr < 7 && colItr < 7)
  {
    rowItr += 1;
    colItr += 1;
    if (board->cells[rowItr][colItr] == EMPTY) break;
    if (player->discColor == board->cells[rowItr][colItr])
    {
      if (count) 
      {
        changed += 1;
        for (int i = row, j = col; i < rowItr, j < colItr; ++i, ++j)
          board->cells[i][j] = player->discColor;
      }
     break;
    }
    else ++count;
  }

  //downleft direction
  rowItr = row;
  colItr = col;
  count = 0;
  while (rowItr < 7 && colItr > 0)
  {
    rowItr += 1;
    colItr -= 1;
    if (board->cells[rowItr][colItr] == EMPTY) break;
    if (player->discColor == board->cells[rowItr][colItr])
    {
      if (count) 
      {
        changed += 1;
        for (int i = row, j = col; i < rowItr, j > colItr; ++i, --j)
          board->cells[i][j] = player->discColor;
      }
     break;
    }
    else ++count;
  }

  //upright direction
  rowItr = row;
  colItr = col;
  count = 0;
  while (rowItr > 0 && colItr < 7)
  {
    rowItr -= 1;
    colItr += 1;
    if (board->cells[rowItr][colItr] == EMPTY) break;
    if (player->discColor == board->cells[rowItr][colItr])
    {
      if (count) 
      {
        changed += 1;
        for (int i = row, j = col; i > rowItr, j < colItr; --i, ++j)
          board->cells[i][j] = player->discColor;
      }
     break;
    }
    else ++count;
  }


  //upleft direction
  rowItr = row;
  colItr = col;
  count = 0;
  while (rowItr > 0 && colItr > 0)
  {
    rowItr -= 1;
    colItr -= 1;
    if (board->cells[rowItr][colItr] == EMPTY) break;
    if (player->discColor == board->cells[rowItr][colItr])
    {
      if (count) 
      {
        changed += 1;
        for (int i = row, j = col; i > rowItr, j > colItr; --i, --j)
          board->cells[i][j] = player->discColor;
      }
     break;
    }
    else ++count;
  }

  if (changed)
    board->cells[row][col] = player->discColor;

  return changed;
}


int has_valid_move(o_board *board, o_player *player)
{
  int count = 0;            // count the total valid moves left for the player
  int tempCount;            // temporary count for each direction
  int rowItr;               // row iterator
  int colItr;               // column iterator

  // for every cell in the board
  for (int i = 0; i < ROWS; ++i)
    for (int j = 0; j < COLS; ++j)
    {
      // if the cell is not empty, move is not valid here
      if (board->cells[i][j] != EMPTY) continue;

      //left direction
      colItr = j;
      tempCount = 0;
      while (colItr > 0)
      {
        colItr -= 1;
        // if found no matching disc in the direction, no updation possible
        if (board->cells[i][colItr] == EMPTY) break;
        // if found disc of same color
        if (player->discColor == board->cells[i][colItr]) 
        {
          // was there any other color disc?
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
      }

      //right direction
      colItr = j;
      tempCount = 0;
      while (colItr < 7)
      {
        colItr += 1;
        if (board->cells[i][colItr] == EMPTY) break;
        if (player->discColor == board->cells[i][colItr]) 
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
      }

      //up direction
      rowItr = i;
      tempCount = 0;
      while (rowItr > 0)
      {
        rowItr -= 1;
        if (board->cells[rowItr][j] == EMPTY) break;
        if (player->discColor == board->cells[rowItr][j]) 
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
      }

      //down direction
      rowItr = i;
      tempCount = 0;
      while (rowItr < 7)
      {
        rowItr += 1;
        if (board->cells[rowItr][j] == EMPTY) break;
        if (player->discColor == board->cells[rowItr][j]) 
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
      }

      //down-right direction
      rowItr = i;
      colItr = j;
      tempCount = 0;
      while (rowItr < 7 && colItr < 7)
      {
        rowItr += 1;
        colItr += 1;

        if (board->cells[rowItr][colItr] == EMPTY) break;
        if (player->discColor == board->cells[rowItr][colItr]) 
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
      }

      //down-left direction
      rowItr = i;
      colItr = j;
      tempCount = 0;
      while (rowItr < 7 && colItr > 0)
      {
        rowItr += 1;
        colItr -= 1;

        if (board->cells[rowItr][colItr] == EMPTY) break;
        if (player->discColor == board->cells[rowItr][colItr])
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
     }

      //up-right direction
      rowItr = i;
      colItr = j;
      tempCount = 0;
      while (rowItr > 0 && colItr < 7)
      {
        rowItr -= 1;
        colItr += 1;
        if (board->cells[rowItr][colItr] == EMPTY) break;
        if (player->discColor == board->cells[rowItr][colItr])
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
     }

      //up-left direction
      rowItr = i;
      colItr = j;
      tempCount = 0;
      while (rowItr > 0 && colItr > 0)
      {
        rowItr -= 1;
        colItr -= 1;
        if (board->cells[rowItr][colItr] == EMPTY) break;
        if (player->discColor == board->cells[rowItr][colItr])
        {
          if (tempCount) count += 1;
          break;
        }
        else ++tempCount;
      }
    }

    return count;
}
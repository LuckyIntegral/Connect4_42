#pragma once

#include "../libft/libft.h"

# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <time.h>

// Minimum number of columns and lines of the game board
# define MIN_COLUMNS 7
# define MIN_LINES 6

// Characters used to represent the game board
# define EMPTY '_'
# define PLAYER1 'X'
# define PLAYER2 'O'

// Maximum number of columns and lines of the terminal window
# define MAX_COLUMNS 211
# define MAX_LINES 58

// Structure to store the game
// board: 2D array of characters, that is allocated dynamically
// columns: number of columns of the board
// lines: number of lines of the board
typedef struct	s_game
{
	char	**board;
	int		columns;
	int		lines;
}	t_game;

// Functions to manipulate the game board
int		init_game(t_game *game, char *lines, char *columns);

// Functinos to calculate the next AI move
int		ai_turn(t_game *game, char player);

// moves.c
void	add_move(t_game *game, int move, char player);


// validation_win.c
int is_game_over(t_game *game);
int is_draw(t_game *game);

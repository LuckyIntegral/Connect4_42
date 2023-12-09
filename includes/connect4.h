#pragma once

#include "../libft/libft.h"

// Minimum number of columns and lines of the game board
# define MIN_COLUMNS 7
# define MIN_LINES 6

// Characters used to represent the game board
# define EMPTY '.'
# define PLAYER1 'R'
# define PLAYER2 'B'

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

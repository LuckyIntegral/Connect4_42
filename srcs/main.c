
#include "../includes/connect4.h"
#include <stdio.h>

void	drop_player(t_game *game, int column, char player);

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./connect4 [lines] [columns]\n", 2), 1);
	if (init_game(&game, argv[1], argv[2]))
		return (1);

	// game.board[5][0] = PLAYER1;
	// game.board[4][1] = PLAYER1;
	// game.board[3][2] = PLAYER1;
	// game.board[2][3] = PLAYER1;
	// game.board[1][4] = PLAYER2;
	// game.board[0][5] = PLAYER1;

	// game.board[5][5] = PLAYER1;
	// game.board[4][4] = PLAYER1;
	// game.board[3][3] = PLAYER1;
	// game.board[2][2] = PLAYER1;
	// game.board[1][1] = PLAYER2;
	// game.board[0][0] = PLAYER1;

	// game.board[0][5] = EMPTY;
	// game.board[1][5] = EMPTY;
	// game.board[2][5] = PLAYER1;
	// game.board[3][5] = PLAYER1;
	// game.board[4][5] = PLAYER2;
	// game.board[5][5] = PLAYER1;

	// game.board[5][0] = PLAYER2;
	// game.board[5][1] = PLAYER2;
	// // game.board[5][2] = PLAYER1;
	// game.board[5][3] = PLAYER2;
	// game.board[5][4] = PLAYER2;
	// game.board[5][5] = PLAYER1;
	// game.board[5][6] = PLAYER1;

	printf("lines: %d,\n", game.lines);
	printf("columns: %d,\n", game.columns);
	printf("board:\n");
	for (int i = 0; i < game.lines; i++)
	{
		for (int j = 0; j < game.columns; j++)
			printf("%c", game.board[i][j]);
		printf("\n");
	}

	char player = PLAYER1;
	while (true)
	{
		printf("======\n");
		for (int i = 0; i < game.lines; i++)
		{
			for (int j = 0; j < game.columns; j++)
				printf("%c", game.board[i][j]);
			printf("\n");
		}
		if (player == PLAYER2)
		{
			printf("> ");
			fflush(stdout);
			char *line = get_next_line(0, READ);
			int col = ft_atoi(line) -1 ;
			drop_player(&game, col, PLAYER2);

			player = PLAYER1;
		}
		else
		{
			int ai_col = ai(&game, PLAYER1);
			printf("AI MOVE: %i\n", ai_col);
			drop_player(&game, ai_col, PLAYER1);
			player = PLAYER2;
		}
		printf("======\n");
		sleep(1);
	}


	ft_free_split(game.board);
	return (0);
}

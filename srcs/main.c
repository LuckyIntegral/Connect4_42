
#include "../includes/connect4.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./connect4 [lines] [columns]\n", 2), 1);
	if (init_game(&game, argv[1], argv[2]))
		return (1);

	printf("lines: %d,\n", game.lines);
	printf("columns: %d,\n", game.columns);
	printf("board:\n");
	for (int i = 0; i < game.lines; i++)
	{
		for (int j = 0; j < game.columns; j++)
			printf("%c", game.board[i][j]);
		printf("\n");
	}

	ft_free_split(game.board);
	return (0);
}

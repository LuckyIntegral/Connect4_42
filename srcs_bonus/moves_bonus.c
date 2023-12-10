
#include "../includes/connect4.h"

void	add_move(t_game *game, int move, char player)
{
	int	i;

	i = game->lines - 1;
	while (i >= 0)
	{
		if (game->board[i][move] == EMPTY)
		{
			game->board[i][move] = player;
			break ;
		}
		i--;
	}
}

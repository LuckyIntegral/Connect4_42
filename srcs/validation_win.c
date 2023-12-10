
#include "../includes/connect4.h"

static int	vertical_win(t_game *game)
{
	int		i;
	int		j;
	int		count = 0;
	char	player = 0;

	j = 0;
	while (j < game->columns)
	{
		i = 0;
		count = 0;
		while (i < game->lines)
		{
			if (game->board[i][j] == EMPTY)
				count = 0;
			else if (game->board[i][j] == player)
				count++;
			else if (game->board[i][j] != player)
			{
				player = game->board[i][j];
				count = 1;
			}
			if (count == 4)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

static int	diagonal_win(t_game *game)
{
	int		i;
	int		j;
	int		count = 0;
	char	player = 0;

	i = 0;
	while (i < game->lines)
	{
		j = 0;
		count = 0;
		while (j < game->columns)
		{
			if (game->board[i][j] == EMPTY)
				count = 0;
			else if (game->board[i][j] == player)
				count++;
			else if (game->board[i][j] != player)
			{
				player = game->board[i][j];
				count = 1;
			}
			if (count == 4)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	horizontal_win(t_game *game)
{
	int		i;
	int		j;
	int		count = 0;
	char	player = 0;

	i = 0;
	while (i < game->lines)
	{
		j = 0;
		count = 0;
		while (j < game->columns)
		{
			if (game->board[i][j] == EMPTY)
				count = 0;
			else if (game->board[i][j] == player)
				count++;
			else if (game->board[i][j] != player)
			{
				player = game->board[i][j];
				count = 1;
			}
			if (count == 4)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int is_game_over(t_game *game)
{
	if (vertical_win(game) || horizontal_win(game) || diagonal_win(game))
		return (1);
	return (0);
}
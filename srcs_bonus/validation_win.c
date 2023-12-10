
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
	for (int line = 0; line < game->lines - 3; line++)
		for (int column = 0; column < game->columns - 3; column++)
			if (game->board[line + 0][column + 0] == game->board[line + 1][column + 1]
				&& game->board[line + 1][column + 1] == game->board[line + 2][column + 2]
				&& game->board[line + 2][column + 2] == game->board[line + 3][column + 3]
				&& game->board[line + 0][column + 0] != EMPTY)
				return (1);

	for (int line = 0; line < game->lines - 3; line++)
		for (int column = 0; column < game->columns - 3; column++)
			if (game->board[line + 3][column + 0] == game->board[line + 2][column + 1]
				&& game->board[line + 2][column + 1] == game->board[line + 1][column + 2]
				&& game->board[line + 1][column + 2] == game->board[line + 0][column + 3]
				&& game->board[line + 3][column + 0] != EMPTY)
				return (1);
	return (0);
}

int is_game_over(t_game *game)
{
	if (vertical_win(game) || horizontal_win(game) || diagonal_win(game))
		return (1);
	return (0);
}

int is_draw(t_game *game)
{
	for (int i = 0; i < game->lines; i++)
		for (int j = 0; j < game->columns; j++)
			if (game->board[i][j] == EMPTY)
				return (0);
	return (1);
}

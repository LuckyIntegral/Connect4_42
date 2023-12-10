
#include "../includes/connect4.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// prints error messages within the function, as it is the only function that can fail
int	init_game(t_game *game, char *lines, char *columns)
{
	int	i;

	if (ft_strlen(lines) > 2 || ft_strlen(columns) > 2
		|| !is_valid_number(lines) || !is_valid_number(columns))
	{
		ft_putstr_fd("Error: Invalid map size\n", 2);
		return (1);
	}
	game->lines = ft_atoi(lines);
	game->columns = ft_atoi(columns);
	if (game->lines < MIN_LINES || game->columns < MIN_COLUMNS
		|| game->lines > MAX_LINES || game->columns > MAX_COLUMNS)
	{
		ft_putstr_fd("Error: Invalid map size\n", 2);
		return (1);
	}
	game->board = ft_calloc(sizeof(char *), game->lines + 1);
	if (!game->board)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		return (1);
	}
	i = 0;
	while (i < game->lines)
	{
		game->board[i] = ft_calloc(sizeof(char), game->columns + 1);
		if (!game->board[i])
		{
			ft_putstr_fd("Error: Malloc failed\n", 2);
			ft_free_split(game->board);
			return (1);
		}
		ft_memset(game->board[i], EMPTY, game->columns);
		i++;
	}
	return (0);
}


#include "../includes/connect4.h"

int	is_valid_number(char *str);

int	player_turn(t_game *game)
{
	char	*line;
	int		move;

	ft_putstr_fd("Please enter a column number\nValid range is 1 - ", 1);
	ft_putnbr_fd(game->columns, 1);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0, READ);
	if (line == NULL)
	{
		get_next_line(0, CLEAN);
		return (ft_putstr_fd("Error: Failed to read stdin\n", 2), -1);
	}
	line[ft_strlen(line) - 1] = 0;
	if (!is_valid_number(line))
	{
		ft_putstr_fd("Error: Invalid input '", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("'\n", 2);
		free(line);
		return (player_turn(game));
	}
	move = ft_atoi(line);
	free(line);
	if (move < 1 || move > game->columns)
	{
		ft_putstr_fd("Error: Invalid column\n", 2);
		return (player_turn(game));
	}
	if (game->board[0][move - 1] != EMPTY)
	{
		ft_putstr_fd("Error: Column is full\n", 2);
		return (player_turn(game));
	}
	return (move - 1);
}

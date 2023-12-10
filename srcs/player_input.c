
#include "../includes/connect4.h"

int	player_turn(t_game *game)
{
	char	*line;
	int		move;

	ft_putstr_fd("Please enter a column number\nValid range is 1 - ", 1);
	ft_putnbr_fd(game->columns, 1);
	line = get_next_line(0, READ);
	if (line == NULL)
	{
		get_next_line(0, READ);
		return (ft_putstr_fd("Error: Failed to read stdin\n", 2), -1);
	}
	if (!is_valid_number(line))
	{
		ft_putstr_fd("Error: Invalid input\n", 2);
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
	if (game->board[move - 1][0] != EMPTY)
	{
		ft_putstr_fd("Error: Column is full\n", 2);
		return (player_turn(game));
	}
	return (move - 1);
}
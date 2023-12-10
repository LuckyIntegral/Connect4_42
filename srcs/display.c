
#include "../includes/connect4.h"

void	print_board(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->lines)
	{
		ft_putstr_fd(game->board[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

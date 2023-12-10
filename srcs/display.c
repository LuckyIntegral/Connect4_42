
#include "../includes/connect4.h"

void	put_header(void)
{
	ft_putendl_fd(" $$$$$$\\                                                      $$\\           $$\\   $$\\", 1);
	ft_putendl_fd("$$  __$$\\                                                     $$ |          $$ |  $$ |", 1);
	ft_putendl_fd("$$ /  \\__| $$$$$$\\  $$$$$$$\\  $$$$$$$\\   $$$$$$\\   $$$$$$$\\ $$$$$$\\         $$ |  $$ |", 1);
	ft_putendl_fd("$$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|\\_$$  _|        $$$$$$$$ |", 1);
	ft_putendl_fd("$$ |      $$ /  $$ |$$ |  $$ |$$ |  $$ |$$$$$$$$ |$$ /        $$ |          \\_____$$ |", 1);
	ft_putendl_fd("$$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |        $$ |$$\\             $$ |", 1);
	ft_putendl_fd("\\$$$$$$  |\\$$$$$$  |$$ |  $$ |$$ |  $$ |\\$$$$$$$\\ \\$$$$$$$\\   \\$$$$  |            $$ |", 1);
	ft_putendl_fd(" \\______/  \\______/ \\__|  \\__|\\__|  \\__| \\_______| \\_______|   \\____/             \\__|", 1);
	ft_putendl_fd("\nRules:\n Connect Four is a 2-player game.\n Players alternate taking turns.\n Each side of the Connect Four board has its own color of checkers.\n There is one color for each player.\n The goal of Connect Four is to get 4 of your color checkers in a\n row—horizontally, vertically, or diagonally—before your opponent does!\n", 1);
}


void	print_board(t_game *game)
{
	ft_putstr_fd("Your colour is ", 1);
	ft_putstr_fd(game->player_sign == PLAYER1 ? "🟢\n" : "🟡\n", 1);
	for (int i = 0; i < game->lines; i++)
	{
		for (int j = 0; j < game->columns; j++)
			ft_putstr_fd("+--", 1);
		ft_putstr_fd("+\n", 1);
		for (int j = 0; j < game->columns; j++)
		{
			ft_putstr_fd("|", 1);
			switch (game->board[i][j])
			{
				case EMPTY:
					ft_putstr_fd("  ", 1);
					break ;
				case PLAYER1:
					ft_putstr_fd("🟢", 1);
					break ;
				case PLAYER2:
					ft_putstr_fd("🟡", 1);
			}
		}
		ft_putstr_fd("|\n", 1);
	}
	for (int j = 0; j < game->columns; j++)
		ft_putstr_fd("+--", 1);
	ft_putstr_fd("+\n", 1);
	for (int j = 0; j < game->columns; j++)
	{
		ft_putstr_fd("|", 1);
		if (j < 9)
			ft_putstr_fd("0", 1);
		ft_putnbr_fd(j + 1, 1);
	}
	ft_putstr_fd("|\n", 1);
	for (int j = 0; j < game->columns; j++)
		ft_putstr_fd("+--", 1);
	ft_putstr_fd("+\n\n", 1);
}

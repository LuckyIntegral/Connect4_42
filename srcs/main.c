
#include "../includes/connect4.h"

int main(int argc, char **argv)
{
	t_game	game;
	int		players_move;
	int		ai_move;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./connect4 [lines] [columns]\n", 2), 1);
	if (init_game(&game, argv[1], argv[2]))
		return (1);

	while (!is_game_over(&game))
	{
		print_board(&game);
		players_move = player_turn(&game);
		if (players_move == -1)
			return (get_next_line(0, CLEAN), ft_free_split(game.board), 1);
		add_move(&game, players_move, PLAYER1);
		if (is_game_over(&game))
			break ;
		ai_move = ai_turn(&game);
		add_move(&game, ai_move, PLAYER2);
	}

	get_next_line(0, CLEAN);
	ft_free_split(game.board);
	return (0);
}

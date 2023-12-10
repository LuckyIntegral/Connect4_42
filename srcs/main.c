
#include "../includes/connect4.h"

void	add_move(t_game *game, int move, char player);
void	print_board(t_game *game);
int		is_valid_number(char *str);
int		player_turn(t_game *game);
int 	is_game_over(t_game *game);

int main(int argc, char **argv)
{
	t_game	game;
	int		players_move, ai_move;
	int		winner = 0;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./connect4 [lines] [columns]\n", 2), 1);
	if (init_game(&game, argv[1], argv[2]))
		return (1);
	put_header();
	if (time(NULL) % 2 == 0)
	{
		(game.player_sign = PLAYER1, game.ai_sign = PLAYER2);
		ft_putstr_fd("You play first\n", 1);
	}
	else
	{
		(game.player_sign = PLAYER2, game.ai_sign = PLAYER1);
		ft_putstr_fd("AI plays first\n", 1);
		ai_move = ai(&game, game.player_sign);
		if (ai_move == -1)
			return (ft_putstr_fd("Error, malloc fail\n", 2), get_next_line(0, CLEAN), ft_free_split(game.board), 1);
		add_move(&game, ai_move, game.ai_sign);
	}

	while (1)
	{
		print_board(&game);
		players_move = player_turn(&game);
		if (players_move == -1)
			return (get_next_line(0, CLEAN), ft_free_split(game.board), 1);
		add_move(&game, players_move, game.player_sign);
		if (is_game_over(&game))
		{
			winner = PLAYER1;
			break ;
		}
		ai_move = ai(&game, game.player_sign);
		if (ai_move == -1)
			return (ft_putstr_fd("Error, malloc fail\n", 2), get_next_line(0, CLEAN), ft_free_split(game.board), 1);
		add_move(&game, ai_move, game.ai_sign);
		if (is_game_over(&game) != 0)
		{
			winner = PLAYER2;
			break ;
		}
	}
	if (is_draw(&game))
		ft_putstr_fd("Lol, you did it, THIS IS A DRAW!\n", 1);
	else if (winner == PLAYER1)
		ft_putstr_fd("Congrats, you won the game!\n", 1);
	else if (winner == PLAYER2)
	{
		print_board(&game);
		ft_putstr_fd("You lost after AI last move! Better luck next time!\n", 1);
	}
	ft_free_split(game.board);
	return (0);
}

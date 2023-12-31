#include "../includes/connect4.h"

typedef struct s_score
{
	int	score;
	int	column;
}	t_score;

static void	free_game(t_game *game)
{
	if (!game)
		return ;
	ft_free_split(game->board);
	free(game);
}

static t_game	*clone_game(t_game *game)
{
	t_game	*clone = ft_calloc(1, sizeof(t_game));
	if (!clone)
		return (NULL);
	
	clone->lines = game->lines;
	clone->columns = game->columns;

	clone->board = ft_calloc(game->lines + 1, sizeof(char *));
	if (!clone->board)
		return (free(clone), NULL);
	for (int line = 0; line < clone->lines; line++)
	{
		clone->board[line] = ft_strdup(game->board[line]);
		if (!clone->board[line])
		{
			ft_free_split(clone->board);
			clone->board = NULL;
			return (free(clone), NULL);
		}
	}
	return (clone);
}

static int	*possible_moves(t_game *game)
{
	int	*moves = ft_calloc(game->columns + 1, sizeof(int));
	if (!moves)
		return (NULL);

	int i = 0;
	for (int column = 0; column < game->columns; column++)
	{
		if (game->board[0][column] != EMPTY)
			continue ;
		moves[i] = column;
		i++;
	}
	moves[i] = -1;

	return (moves);
}

bool	winning_move(t_game *game, char player)
{
	// Horizontal
	for (int column = 0; column < game->columns - 3; column++)
	{
		for (int line = 0; line < game->lines; line++)
		{
			char *l = game->board[line];
			if (l[column] == player && l[column + 1] == player
				&& l[column + 2] == player && l[column + 3] == player)
				return (true);
		}
	}

	// Vertical
	for (int column = 0; column < game->columns; column++)
	{
		for (int line = 0; line < game->lines - 3; line++)
		{
			if (game->board[line][column] == player
				&& game->board[line + 1][column] == player
				&& game->board[line + 2][column] == player
				&& game->board[line + 3][column] == player
			)
				return (true);
		}
	}

	// Diagonal
	for (int column = 0; column < game->columns - 3; column++)
	{
		for (int line = 0; line < game->lines - 3; line++)
		{
			if (game->board[line][column] == player
				&& game->board[line + 1][column + 1] == player
				&& game->board[line + 2][column + 2] == player
				&& game->board[line + 3][column + 3] == player
			)
				return (true);
		}
	}

	for (int column = 0; column < game->columns - 3; column++)
	{
		for (int line = 3; line < game->lines; line++)
		{
			if (game->board[line][column] == player
				&& game->board[line - 1][column + 1] == player
				&& game->board[line - 2][column + 2] == player
				&& game->board[line - 3][column + 3] == player
			)
				return (true);
		}
	}
	return (false);
}

bool	is_end(t_game *game)
{
	int	*possible = possible_moves(game);
	if (possible && possible[0] == -1)
		return (free(possible), true);
	free(possible);
	return (winning_move(game, PLAYER1) || winning_move(game, PLAYER2));
}

# define WINDOW_LEN (4)

static int	score_window(char *window)
{
	int		player1_count = 0;
	int		player2_count = 0;
	int		empty_count = 0;

	// Count all pieces
	while (*window)
	{
		if (*window == PLAYER1)
			player1_count++;
		else if (*window == PLAYER2)
			player2_count++;
		else
			empty_count++;
		window++;
	}

	if (player1_count == 4)
		return (100);
	if (player2_count == 4)
		return (-100);

	if (player1_count == 3 && empty_count == 1)
		return (50);
	if (player2_count == 3 && empty_count == 1)
		return (-50);

	if (player1_count == 2 && empty_count == 2)
		return (5);
	if (player2_count == 2 && empty_count == 2)
		return (-5);

	return (0);
}

static int	count_center_pieces(t_game *game, char player)
{
	int	center = game->columns / 2;

	int	count = 0;
	for (int row = 0; row < game->lines; row++)
	{
		if (game->board[row][center] == player)
			count++;
	}
	return (count);
}

// TODO: optimize this to skip empty rows
static int	score_position(t_game *game, char player)
{
	char	window[WINDOW_LEN + 1] = "\0\0\0\0\0";
	int		score = 0;

	score += count_center_pieces(game, player) * 3;

	// Horizontal Score
	for (int line = 0; line < game->lines; line++)
	{
		for (int column = 0; column < game->columns - (WINDOW_LEN - 1); column++)
		{
			window[0] = game->board[line][column];
			window[1] = game->board[line][column + 1];
			window[2] = game->board[line][column + 2];
			window[3] = game->board[line][column + 3];
			score += score_window(window);
		}
	}

	// Vertical Score
	for (int column = 0; column < game->columns; column++)
	{
		for (int line = 0; line < game->lines - (WINDOW_LEN - 1); line++)
		{
			window[0] = game->board[line][column];
			window[1] = game->board[line + 1][column];
			window[2] = game->board[line + 2][column];
			window[3] = game->board[line + 3][column];
			score += score_window(window);
		}
	}

	// Diagonal Score
	for (int line = 0; line < game->lines - (WINDOW_LEN - 1); line++)
	{
		for (int column = 0; column < game->columns - (WINDOW_LEN - 1); column++)
		{
			window[0] = game->board[line][column];
			window[1] = game->board[line + 1][column + 1];
			window[2] = game->board[line + 2][column + 2];
			window[3] = game->board[line + 3][column + 3];
			score += score_window(window);
		}
	}

	for (int line = 0; line < game->lines - (WINDOW_LEN - 1); line++)
	{
		for (int column = 0; column < game->columns - (WINDOW_LEN - 1); column++)
		{
			window[0] = game->board[line + (WINDOW_LEN - 1)][column];
			window[1] = game->board[line + (WINDOW_LEN - 2)][column + 1];
			window[2] = game->board[line + (WINDOW_LEN - 3)][column + 2];
			window[3] = game->board[line + (WINDOW_LEN - 4)][column + 3];
			score += score_window(window);
		}
	}

	return (score);
}

t_score	*minimax(t_game *game, int depth, char maximizing_player)
{
	bool end = is_end(game);
	if (depth == 0 || end)
	{
		t_score	*score = ft_calloc(1, sizeof(t_score));
		if (!score)
			return (NULL);
		if (end)
		{
			if (winning_move(game, PLAYER1))
				score->score = INT_MAX;
			else if (winning_move(game, PLAYER2))
				score->score = INT_MIN;
			return (score);
		}
		score->score = score_position(game, maximizing_player);
		return (score);
	}


	int	*possible = possible_moves(game);
	if (!possible)
		return (NULL);

	if (maximizing_player == PLAYER1)
	{
		t_score *max_score = NULL;
		for (int i = 0; possible[i] != -1; i++)
		{
			t_game *copy = clone_game(game);
			if (!copy)
				return (free(possible), free(max_score), NULL);
			add_move(copy, possible[i], maximizing_player);
			t_score *eval = minimax(copy, depth - 1, PLAYER2);
			free_game(copy);
			if (!eval)
				return (free(possible), free(max_score), NULL);
			if (max_score && eval->score < max_score->score)
			{
				free(eval);
				continue ;
			}
			free(max_score);
			eval->column = possible[i];
			max_score = eval;
		}
		return (free(possible), max_score);
	}

	t_score *min_score = NULL;
	for (int i = 0; possible[i] != -1; i++)
	{
		t_game *copy = clone_game(game);
		if (!copy)
			return (free(possible), free(min_score), NULL);
		add_move(copy, possible[i], maximizing_player);
		t_score *eval = minimax(copy, depth - 1, PLAYER1);
		free_game(copy);
		if (!eval)
			return (free(possible), free(min_score), NULL);
		if (min_score && eval->score > min_score->score)
		{
			free(eval);
			continue ;
		}
		free(min_score);
		eval->column = possible[i];
		min_score = eval;
	}
	return (free(possible), min_score);
}

int	ai_turn(t_game *game, char player)
{
	srand(time(NULL));

	if (!ft_strchr(game->board[game->lines - 1], PLAYER1)
		&& !ft_strchr(game->board[game->lines - 1], PLAYER2)
	)
	{
		int column = rand() % game->lines;
		return (column);
	}
	t_score *score = minimax(game, 3, player);
	if (!score)
		return (-1);

	int column = score->column;
	return (free(score), column);
}

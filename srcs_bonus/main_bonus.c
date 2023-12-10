# include "../includes/connect4.h"

#include "./raylib/src/raylib.h"
#include "./raylib/src/raymath.h"
#include <stdio.h>

# define CIRCLE_RADIUS (15)
# define CIRCLE_DISTANCE (10)

# define BORDER_WIDTH (15)

RenderTexture2D	create_board(t_game *game, int screen_width) {
	float card_width = (game->columns + 1) * CIRCLE_DISTANCE + game->columns * (CIRCLE_RADIUS * 2);
	float card_height = (game->lines + 1) * CIRCLE_DISTANCE + game->lines * (CIRCLE_RADIUS * 2);
    Rectangle card = {
		.x = (float) screen_width / 2 - card_width / 2,
		.y = 100,
		.width = card_width,
		.height = card_height,
	};

    RenderTexture2D circle_holder = LoadRenderTexture(card.width, card.height);

    BeginTextureMode(circle_holder);
        ClearBackground(BLANK);
	    DrawRectangle(0, 0, card.width, card.height, BLUE);
		for (int line = 0; line < game->lines; line++)
		{
			for (int column = 0; column < game->columns; column++)
			{
				int x = CIRCLE_DISTANCE + CIRCLE_RADIUS +
					(CIRCLE_RADIUS * 2 + CIRCLE_DISTANCE) * column;
				int y = CIRCLE_DISTANCE + CIRCLE_RADIUS +
					(CIRCLE_RADIUS * 2 + CIRCLE_DISTANCE) * line;
				DrawCircle(x, y, CIRCLE_RADIUS, RAYWHITE);
			}
		}
    EndTextureMode();

	RenderTexture2D board = LoadRenderTexture(card_width + BORDER_WIDTH * 4, card.height + 5 + BORDER_WIDTH);

	BeginTextureMode(board);
		ClearBackground(BLANK);

		DrawRectangle(BORDER_WIDTH, BORDER_WIDTH, BORDER_WIDTH, card_height + 5, DARKBLUE);
		DrawRectangle(circle_holder.texture.width + BORDER_WIDTH * 2, BORDER_WIDTH, BORDER_WIDTH, card_height + 5, DARKBLUE);

		DrawRectangle(0, 0, card_width + BORDER_WIDTH * 4, BORDER_WIDTH, DARKBLUE);

		DrawTexture(circle_holder.texture, BORDER_WIDTH * 2, BORDER_WIDTH, WHITE);
	EndTextureMode();

	UnloadRenderTexture(circle_holder);

	return (board);
}

void draw_chips(t_game *game, RenderTexture2D *chips, int screen_width)
{
	BeginTextureMode(*chips);
		ClearBackground(BLANK);
		for (int line = 0; line < game->lines; line++)
		{
			for (int column = 0; column < game->columns; column++)
			{
				if (game->board[line][column] == EMPTY)
					continue ;
				int x = CIRCLE_DISTANCE + CIRCLE_RADIUS +
					(CIRCLE_RADIUS * 2 + CIRCLE_DISTANCE) * column;
				int y = CIRCLE_DISTANCE + CIRCLE_RADIUS +
					(CIRCLE_RADIUS * 2 + CIRCLE_DISTANCE) * (game->lines - 1 - line);
				char chip = game->board[line][column];
				DrawCircle(x, y, CIRCLE_RADIUS, chip == PLAYER1 ? RED : GREEN);
			}
		}
	EndTextureMode();

	DrawTexture(chips->texture, (float) screen_width / 2 - (float) chips->texture.width / 2 - BORDER_WIDTH, 105, WHITE);
}

void DrawThickLine(Vector2 start, Vector2 end, float thickness, Color color) {
    Vector2 direction = Vector2Subtract(end, start);
    Vector2 perp = { -direction.y, direction.x };
    perp = Vector2Normalize(perp);
    perp = Vector2Scale(perp, thickness / 2);

    Vector2 vertices[4] = {
        Vector2Add(start, perp),
        Vector2Add(end, perp),
        Vector2Subtract(end, perp),
        Vector2Subtract(start, perp)
    };

    DrawTriangle(vertices[0], vertices[1], vertices[3], color);
    DrawTriangle(vertices[1], vertices[2], vertices[3], color);
}

RenderTexture2D	create_position_pointer() {
    RenderTexture2D pointer = LoadRenderTexture(50, 25);

	BeginTextureMode(pointer);
		DrawThickLine((Vector2){0,25}, (Vector2){25,0}, 5, DARKGRAY);
		DrawThickLine((Vector2){25,0}, (Vector2){50,25}, 5, DARKGRAY);
	EndTextureMode();

	return (pointer);
}

void	draw_player_info(char player, char ai_player)
{
	if (player == ai_player)
        DrawText("AI is thinking...", 10, 10, 20, DARKGRAY);
	else
		DrawText("It's your turn!", 10, 10, 20, GREEN);
}

void	draw_pointer(int screen_width, float card_width, int column, RenderTexture2D pointer)
{
	int x = CIRCLE_RADIUS +
		(CIRCLE_RADIUS * 2 + CIRCLE_DISTANCE) * column;
	x += (float) screen_width / 2 - card_width / 2;
	DrawTexture(pointer.texture, x, 75, WHITE);
}

void	draw_game_winner(char winner, char ai_player, int screen_width, int screen_height)
{
	char *text = "You Won!";

	if (winner == ai_player)
		text = "You Lost :(";
	else if (winner == '\0')
		text = "LOL, A DRAW";

    int fontSize = 50;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);

    int paddingX = 30;
    int paddingY = 20;

    Vector2 position = {
        (screen_width - (textSize.x + paddingX)) / 2,
        (screen_height - (textSize.y + paddingY)) / 2
    };

    DrawRectangle(
        position.x - (float) paddingX / 2,
        position.y - (float) paddingY / 2,
        textSize.x + paddingX * 2,
        textSize.y + paddingY,
        winner == ai_player ? RED : GREEN
    );

    DrawText(text, position.x, position.y, fontSize, winner == ai_player ? WHITE : BLACK);
}

int bonus_main(char **argv)
{
	t_game game;

	if (init_game(&game, argv[1], argv[2]))
		return (1);

    SetTraceLogLevel(LOG_ERROR);
	float chips_width = (game.columns + 1) * CIRCLE_DISTANCE + game.columns * (CIRCLE_RADIUS * 2);
	float chips_height = (game.lines + 1) * CIRCLE_DISTANCE + game.lines * (CIRCLE_RADIUS * 2);

    int screenWidth = ft_max(800, chips_width + 100);
    int screenHeight = ft_max(450, chips_height + 200);
    InitWindow(screenWidth, screenHeight, "Connect 4");

	RenderTexture2D board = create_board(&game, screenWidth);
	float card_width = board.texture.width;
	RenderTexture2D pointer = create_position_pointer();

	RenderTexture2D chips = LoadRenderTexture(chips_width, chips_height);

	char current_player = PLAYER1;
	char ai_player = PLAYER2;
	if (time(NULL) % 2 == 0)
	{
		current_player = PLAYER1;
		ai_player = PLAYER2;
	}
	else
	{
		current_player = PLAYER2;
		ai_player = PLAYER2;
	}

	int column = 0;

	bool game_finished = false;
	char winner = '\0';

    SetTargetFPS(30);
    while (!WindowShouldClose()) {
		if (!game_finished && current_player == ai_player)
		{
			column = ai_turn(&game, ai_player);
			if (column == -1)
			{
				printf("ERROR\n");
				break ;
			}
			add_move(&game, column, current_player);
			print_board(&game);
			if (current_player == PLAYER1)
				current_player = PLAYER2;
			else
				current_player = PLAYER1;
			if (is_game_over(&game))
			{
				winner = ai_player;
				game_finished = true;
			}
			if (is_draw(&game))
				game_finished = true;
		}
        BeginDrawing();
            ClearBackground(RAYWHITE);
			if (!game_finished)
			{
				if ((IsKeyReleased(KEY_SPACE) || IsKeyReleased(KEY_DOWN)) && game.board[0][column] == EMPTY)
				{
					add_move(&game, column, current_player);
					print_board(&game);
					if (is_game_over(&game) != 0)
					{
						winner = current_player;
						game_finished = true;
					}
					if (is_draw(&game))
						game_finished = true;
					if (current_player == PLAYER1)
						current_player = PLAYER2;
					else
						current_player = PLAYER1;
				}
				if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
				{
					column = ft_max(column - 1, 0);
				}
				if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
				{
					column = ft_min(column + 1, game.columns - 1);
				}
			}

			DrawTexture(board.texture, (float) screenWidth / 2 - card_width / 2 - BORDER_WIDTH, 100, WHITE);

			draw_chips(&game, &chips, screenWidth);

			draw_pointer(screenWidth, card_width, column, pointer);

			draw_player_info(current_player, ai_player);

			if (game_finished)
				draw_game_winner(winner, ai_player, screenWidth, screenHeight);
        EndDrawing();

    }

    UnloadRenderTexture(board);
    UnloadRenderTexture(pointer);
    UnloadRenderTexture(chips);
    CloseWindow();

	ft_free_split(game.board);

    return 0;
}

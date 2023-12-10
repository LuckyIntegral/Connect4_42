###############################################################################
######                            PROPERTIES                             ######
###############################################################################

CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -MD -MP -Ofast -march=native -g

###############################################################################
######                               LIBFT                               ######
###############################################################################

LIBDIR		= ./libft
LIBFT		= ${LIBDIR}/libft.a

###############################################################################
######                              RAYLIB                               ######
###############################################################################

RAYLIBDIR	= ./srcs_bonus/raylib/src
RAYLIB		= ${RAYLIBDIR}/libraylib.a

###############################################################################
######                             MANDATORY                             ######
###############################################################################

NAME		= connect4
SRCSDIR		= srcs
SRCS		= \
			${SRCSDIR}/display.c \
			${SRCSDIR}/init.c \
			${SRCSDIR}/main.c \
			${SRCSDIR}/display.c \
			${SRCSDIR}/moves.c \
			${SRCSDIR}/player_input.c \
			${SRCSDIR}/validation_win.c \
			${SRCSDIR}/minimax.c

OBJSDIR		= ${SRCSDIR}/objs
DEPS		= $(SRCS:${SRCSDIR}/%.c=${OBJSDIR}/%.d)
OBJS		= $(SRCS:${SRCSDIR}/%.c=${OBJSDIR}/%.o)

###############################################################################
######                               BONUS                               ######
###############################################################################

NAME_B		= connect4_bonus
SRCSDIR_B	= srcs_bonus
SRCS_B		= \
			${SRCSDIR_B}/main_bonus.c \
			${SRCSDIR_B}/moves.c \
			${SRCSDIR_B}/minimax.c \
			${SRCSDIR_B}/validation_win.c \
			${SRCSDIR_B}/init.c

OBJSDIR_B	= ${SRCSDIR_B}/objs
OBJS_B      = $(SRCS_B:${SRCSDIR_B}/%.c=${OBJSDIR_B}/%.o)
DEPS_B      = $(SRCS_B:${SRCSDIR_B}/%.c=${OBJSDIR_B}/%.d)

###############################################################################
######                               RULES                               ######
###############################################################################

all					: $(NAME)

bonus				: $(NAME_B)

$(NAME)				: ${OBJS}
		make --no-print-directory -C ${LIBDIR} all
		$(CC) $(CFLAGS) -o $@ $^ -L. ${LIBFT}

$(NAME_B)			: ${OBJS_B}
		make --no-print-directory -C ${LIBDIR} all
		make --no-print-directory -C ${RAYLIBDIR} PLATFORM=PLATFORM_DESKTOP
		$(CC) $(CFLAGS) -o $(NAME_B) $^ $(LINKS) -L. ${LIBFT} ${RAYLIB} -lm

${OBJSDIR_B}/%.o		: ${SRCSDIR_B}/%.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@ -I ./includes

${OBJSDIR}/%.o		: ${SRCSDIR}/%.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@ -I ./includes

clean				:
		make --no-print-directory -C ${LIBDIR} clean
		$(RM) $(OBJSDIR) $(OBJSDIR_B)

fclean				:
		make --no-print-directory -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(OBJSDIR_B) $(NAME) $(NAME_B)

re					: fclean all

-include $(DEPS_B) $(DEPS)

.PHONY: all clean fclean bonus re reb

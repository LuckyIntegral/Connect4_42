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
######                             MANDATORY                             ######
###############################################################################

NAME		= connect4
SRCSDIR		= srcs
SRCS		= \
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
######                               RULES                               ######
###############################################################################

all					: $(NAME)

$(NAME)				: ${OBJS}
		make --no-print-directory -C ${LIBDIR} all
		$(CC) $(CFLAGS) -o $@ $^ -L. ${LIBFT}

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

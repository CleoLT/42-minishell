NAME = minishell

# ═══ COMPILATE ═══════════════════════════════════════════════════════════════#
CC			= gcc
RMF			= rm -f
RMD			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
READL_FLAG	= -lreadline
LIB_FLAG 	= -L ./libft -lft
MKDIR		= mkdir -p

# ═══ DIRECTORIES ═════════════════════════════════════════════════════════════#
INC_DIR		= inc/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIB_DIR		= libft/
ENVP_DIR	= envp/
LEX_DIR		= lexer/
EXEC_DIR	= exec/
ERR_DIR		= error/
UTILS_DIR	= utils/
BUILT_DIR	= built/

INCLUDE = Makefile libft/Makefile

# ═══ SOURCES ═════════════════════════════════════════════════════════════════#
MAIN		= minishell
ENVP_FILES  = envp
LEX_FILES	= lexer quotes spaces token_reader
ERR_FILES	= error
UTILS_FILES = envp_utils free_utils lexer_utils
EXEC_FILES	= execute
BUILT_FILES	= builtins

SRC_FILES+=$(MAIN)
SRC_FILES+=$(addprefix $(ENVP_DIR),$(ENVP_FILES))
SRC_FILES+=$(addprefix $(LEX_DIR),$(LEX_FILES))
SRC_FILES+=$(addprefix $(ERR_DIR),$(ERR_FILES))
SRC_FILES+=$(addprefix $(UTILS_DIR),$(UTILS_FILES))
SRC_FILES+=$(addprefix $(EXEC_DIR),$(EXEC_FILES))
SRC_FILES+=$(addprefix $(BUILT_DIR),$(BUILT_FILES))

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

# ═══ RULES ═══════════════════════════════════════════════════════════════════#

all:	$(NAME)

$(NAME):	$(OBJS)
			make -C $(LIB_DIR)
			$(CC) $(CFLAGS) $(READL_FLAG) -o $(NAME) $(OBJS) $(LIB_FLAG)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INCLUDE)
				$(MKDIR) $(dir $@)
				$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR)$(INC_DIR) -MMD -MP -c -o $@ $<

clean:
		$(RMD) $(OBJ_DIR)
		make clean -C $(LIB_DIR)
		
fclean:	clean
		$(RMF) $(NAME)
		$(RMF) $(LIBFT_DIR)libft.a

re:	fclean all

-include $(DEPS)
.PHONY: all clean fclean re

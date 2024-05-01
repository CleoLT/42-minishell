NAME = minishell

# ═══ COMPILATE ═══════════════════════════════════════════════════════════════#
CC			= gcc
RMF			= rm -f
RMD			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
LIB_FLAG 	= -L./libft/ -L./readline/ -lreadline -lhistory -ltermcap -lft
DEP_FLAG	= -MMD -MP
INCLUDE		= -I./libft/inc/ -I./inc/ -I./readline/ 
MKDIR		= mkdir -p

# ═══ DIRECTORIES ═════════════════════════════════════════════════════════════#
INC_DIR		= inc/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIB_DIR		= libft/
READL_DIR	= readline/
ENVP_DIR	= envp/
LEX_DIR		= lexer/
EXEC_DIR	= exec/
EXP_DIR		= expander/
ERR_DIR		= error/
UTILS_DIR	= utils/
BUILT_DIR	= built/

# ═══ SOURCES ═════════════════════════════════════════════════════════════════#
MAIN		= minishell
ENVP_FILES  = envp
LEX_FILES	= lexer quotes spaces token_reader
ERR_FILES	= error
UTILS_FILES = envp_utils free_utils lexer_utils signal ft_heredoc faker
EXEC_FILES	= execute redirections
EXP_FILES	= expander
BUILT_FILES	= builtins ft_cd ft_unset ft_export 

SRC_FILES+=$(MAIN)
SRC_FILES+=$(addprefix $(ENVP_DIR),$(ENVP_FILES))
SRC_FILES+=$(addprefix $(LEX_DIR),$(LEX_FILES))
SRC_FILES+=$(addprefix $(ERR_DIR),$(ERR_FILES))
SRC_FILES+=$(addprefix $(UTILS_DIR),$(UTILS_FILES))
SRC_FILES+=$(addprefix $(EXEC_DIR),$(EXEC_FILES))
SRC_FILES+=$(addprefix $(EXP_DIR),$(EXP_FILES))
SRC_FILES+=$(addprefix $(BUILT_DIR),$(BUILT_FILES))

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

# ═══ RULES ═══════════════════════════════════════════════════════════════════#

all:	$(NAME) 

$(NAME):	$(OBJS)
			make -C $(LIB_DIR)
			$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAG) -o $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c Makefile libft/Makefile libft/src/*/*.c 
				$(MKDIR) $(dir $@)
				$(CC) $(CFLAGS) -DREADLINE_LIBRARY $(INCLUDE) $(DEP_FLAG) -c -o $@ $<

readl: 
		cd ./readline/ && ./configure
		make -C $(READL_DIR)

cleanrl:
		make clean -C $(READL_DIR)

clean:
		$(RMD) $(OBJ_DIR)
		make clean -C $(LIB_DIR)
		
fclean:	clean
		$(RMF) $(NAME)
		$(RMF) $(LIBFT_DIR)libft.a

re:	fclean all

-include $(DEPS)
.PHONY: all clean fclean re readl

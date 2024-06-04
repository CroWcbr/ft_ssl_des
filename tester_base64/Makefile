NAME		=	test_base64

CC			=	gcc 
FLAGS		=	-Wall -Wextra -Werror

INCLUDE		= 	../include/
LIBFT_DIR	=	../libft
SRC_DIR		=	../src
OBJ_DIR		=	obj

LIBFT_LIB	=	libft.a

SRC			=	tester/tester_base64.c \
				ft_ssl_help.c \
				ssl_des/base64/base64_main.c \
				ssl_des/base64/base64_decode.c

OBJ			=	$(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(@D)
				$(CC) $(FLAGS) -c -o $@ $< -I $(INCLUDE)

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#COLORS
C_NO		=	"\033[00m"
C_OK		=	"\033[32m"
C_GOOD		=	"\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C ${LIBFT_DIR}/ all
			@$(CC) -o $(NAME) $(FLAGS) -o $@ $^ $(LIBFT_DIR)/$(LIBFT_LIB) -lssl -lcrypto
			@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)

clean:
			@make -C ${LIBFT_DIR}/ clean
			@${RM_DIR} ${OBJ_DIR}
			@echo "\tCleaning...\t" [ $(NAME) ] $(OK)

fclean:		clean
			@${RM_FILE} $(LIBFT_DIR)/$(LIBFT_LIB)
			@echo "\tDeleting...\t" [ $(LIBFT_LIB) ] $(OK)
			@${RM_FILE} $(NAME)
			@echo "\tDeleting...\t" [ $(NAME) ] $(OK)

re:			fclean all

.PHONY: all clean fclean re bonus

NAME = btc

SRCS =	main.cpp \
	BitcoinExchange.cpp

OBJS = ${SRCS:.cpp=.o}

CC = c++
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	@$(RM)  $(OBJS)
	@rm -rf data.csv

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run : all data.csv 

.PHONY: all clean fclean re csv run
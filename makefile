all:
	gcc main.c th_mq.c -o Chat -lncurses -lpthread -lrt

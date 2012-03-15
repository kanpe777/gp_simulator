CFLAGS = -W -O2
#CFLAGS = -g
CC = gcc

all:main tree rank choice cross mutate simulate stage
	$(CC) -lcurses $(CFLAGS) -o simulator main.o tree.o rank.o choice.o cross.o mutate.o simulate.o stage.o
	rm *.o 

main:main.o
	$(CC) $(CFLAGS) -c main.c

tree:tree.o 
	$(CC) $(CFLAGS) -c tree.c

rank:rank.o
	$(CC) $(CFLAGS) -c rank.c

choice:choice.o
	$(CC) $(CFLAGS) -c choice.c

cross:cross.o
	$(CC) $(CFLAGS) -c cross.c

mutate:mutate.o
	$(CC) $(CFLAGS) -c mutate.c

simulate:simulate.o
	$(CC) $(CFLAGS) -c simulate.c

stage:stage.o
	$(CC) $(CFLAGS) -c stage.c


#--------引数
#第一引数：ステージの最大個数
#第二引数：Manual->1、Auto->2
#第三引数：個体数
#第四引数：世代数
#第五引数：低速->0、高速->1

high:
	./simulator 10 2 80 300 1

low:
	./simulator 10 2 10 20 0

test:
	./simulator 10 2 5 10 1


clean:
	rm simulator

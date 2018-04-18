cc = arm-linux-androideabi-gcc

all: b_tp.c b_tp.h
	$(cc) -Wall -g -fPIC -c b_tp.c -o libb_tp.o
	$(cc) -shared libb_tp.o -o libb_tp.so

OBJ = test.o ./b_tp/src/b_tp.o ./b_tp/b_tp_port/b_tp_port.o ./b_tp/check/crc16/crc16.o
INCLUDE = -I ./b_tp/src/ -I ./b_tp/inc/ -I ./b_tp/b_tp_port/ -I ./b_tp/check/crc16/

TEST: $(OBJ)
	gcc -o $@ $^

%.o: %.c
	gcc $(DEF) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o TEST ./b_tp/src/*.o ./b_tp/b_tp_port/*.o ./b_tp/check/crc16/*.o

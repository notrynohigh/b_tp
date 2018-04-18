OBJ = testlib.o ./b_tp/b_tp.o 
INCLUDE = -I ./b_tp

TEST: $(OBJ)
	gcc -o $@ $^

%.o: %.c
	gcc $(DEF) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o TEST ./b_tp/*.o 

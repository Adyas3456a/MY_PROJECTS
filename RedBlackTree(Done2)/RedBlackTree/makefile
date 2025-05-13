OBJ := $(patsubst %.c, %.o, $(wildcard *.c))

rbt.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm -f *.o *.exe
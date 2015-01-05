all: jvm

jvm: bytereader.c c_pool.o class_type.o util.o opcode.o common.h
	gcc -o bytereader bytereader.c class_type.o util.o c_pool.o opcode.o

class_type.o: class_type.c
	gcc -c class_type.c

c_pool.o: c_pool.c 
	gcc -c c_pool.c

opcode.o: opcode.c
	gcc -c opcode.c

util.o: util.c
	gcc -c util.c

clean:
	rm -rf *.o bytereader 


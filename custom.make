CC=mpic++
CFLAGS = -g
OBJDIR := dist/MPIcpp/GNU-Linux-x86/
MKDIR_P = mkdir -p

.PHONY: directories

# all: directories program
all: program
	@echo "\nrun with:"
	@echo "mpirun -np 1 master"

directories: ${OUT_DIR}


${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

program: master calculator_slave coordinator_slave

# master
master: master.cpp utils.o
	$(CC) $(LDFLAGS) -o $@ $^


# calculator_slave
calculator_slave: calculator_slave.o utils.o
	$(CC) $(LDFLAGS) -o $@ $^

calculator_slave.o: calculator_slave.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# coordinator_slave
coordinator_slave: coordinator_slave.o utils.o
	$(CC) $(LDFLAGS) -o $@ $^

coordinator_slave.o: coordinator_slave.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

utils.o: utils.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o

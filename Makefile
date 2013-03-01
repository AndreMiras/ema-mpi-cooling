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

program: master coordinator_slave calculator_slave

# master
master: master.h master.cpp utils.o
	$(CC) $(CFLAGS) -o $@ $^

# coordinator_slave
coordinator_slave: coordinator_slave.h coordinator_slave.cpp utils.o
	$(CC) $(CFLAGS) -o $@ $^

# calculator_slave
calculator_slave: calculator_slave.h calculator_slave.cpp utils.o
	$(CC) $(CFLAGS) -o $@ $^

utils.o: utils.cpp utils.h
	$(CC) $(CFLAGS) -c -o $@ $<
	@# $(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o
	rm -f master coordinator_slave calculator_slave

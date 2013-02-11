CC=mpic++
CFLAGS = -g
OBJDIR := dist/MPIcpp/GNU-Linux-x86/
MKDIR_P = mkdir -p

.PHONY: directories

# all: directories program
all: program

directories: ${OUT_DIR}


${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

program: master calculator_slave coordinator_slave
	# $(CC) $(LDFLAGS) -o $@ $^
	$(CC) $(LDFLAGS) -o master master.o utils.o
	$(CC) $(LDFLAGS) -o calculator_slave calculator_slave.o utils.o
	$(CC) $(LDFLAGS) -o coordinator_slave.cpp coordinator_slave.o utils.o

# master
master: master.o utils.o
	$(CC) $(LDFLAGS) -o $@ $^

master.o: master.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

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

BIN=server_test_main queue_test_main bfs_test_main williamsClient_test_main astonClient_test_main haasClient_test_main rules_test_main display_test_main
SRC=src
SERV_DIR=server
CLI_DIR=client
DEBUG_DIR=server_debug
DISP_DIR=display

CC ?= cc 
GSL_PATH?=~/gsl
CFLAGS = -Wall -Wextra -std=c99 -g -fPIC -I $(GSL_PATH)/include -I ${SRC}/ -I ${SRC}/${CLI_DIR} -I ${SRC}/${CLI_DIR}/queue -fprofile-arcs -ftest-coverage
CFLAGS_TEST = -std=c99 -g -I $(GSL_PATH)/include -I ${SRC}/${CLI_DIR} -I ${SRC}/ -I ${SRC}/${CLI_DIR}/queue -fprofile-arcs -ftest-coverage
LDFLAGS=-L$(GSL_PATH)/lib -lgsl -lgslcblas -lm -lgcov --coverage

SDL_CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags sdl2)
SDL_LDFLAGS = $(shell pkg-config --libs sdl2)

.PHONY: clean doc

all: build

doc: doc/Doxyfile
	mkdir -p doc/documentation_flood
	rm -rf doc/documentation_flood/*  || true
	doxygen doc/Doxyfile

build: libWilliams.so libAston.so libHaas.so server

libWilliams.so: ${SRC}/${CLI_DIR}/williamsClient.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${CLI_DIR}/queue/queue.o 
	${CC} ${CFLAGS_TEST} -shared -o libWilliams.so ${SRC}/${CLI_DIR}/williamsClient.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o

libAston.so: ${SRC}/${CLI_DIR}/astonClient.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${CLI_DIR}/queue/queue.o 
	${CC} ${CFLAGS_TEST} -shared -o libAston.so ${SRC}/${CLI_DIR}/astonClient.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o

libHaas.so: ${SRC}/${CLI_DIR}/haasClient.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${CLI_DIR}/queue/queue.o 
	${CC} ${CFLAGS_TEST} -shared -o libHaas.so ${SRC}/${CLI_DIR}/haasClient.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o

server: ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${SERV_DIR}/server.o ${SRC}/${SERV_DIR}/input.o ${SRC}/${SERV_DIR}/game.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${SERV_DIR}/board.o 
	${CC} ${SRC}/${SERV_DIR}/server.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${SERV_DIR}/input.o ${SRC}/${SERV_DIR}/game.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${SERV_DIR}/board.o -o server ${LDFLAGS} -ldl

install: alltests build
	cp alltests ./install/
	cp libWilliams.so ./install/
	cp libAston.so ./install/
	cp libHaas.so ./install/
	cp server ./install

test: ${BIN}

clean:
	rm -rf doc/documentation_flood/*  || true
	find . -name "*.o" -type f -delete
	find . -name "*.gcno" -type f -delete
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcov" -type f -delete
	find . -name "*.png" -type f -delete
	find . -name "*.html" -type f -delete
	find . -name "*.css" -type f -delete
	find . -name "*.info" -type f -delete
	find . -name "*.so" -type f -delete
	find . -path ./${SERV_DIR} -type d -exec rm -rf {} +
	find . -path ./${CLI_DIR} -type d -exec rm -rf {} +
	find . -path ./${DISP_DIR} -type d -exec rm -rf {} +
	find . -name ${DEBUG_DIR} -type d -exec rm -rf {} + 	 
	find . -name queue_test_main -type f -delete
	find . -name bfs_test_main -type f -delete
	find . -name rules_test_main -type f -delete
	find . -name server_test_main -type f -delete
	find . -name display_test_main -type f -delete
	find . -name williamsClient_test_main -type f -delete
	find . -name astonClient_test_main -type f -delete
	find . -name haasClient_test_main -type f -delete
	find . -name alltests -type f -delete
	find . -name server -type f -delete
	find . -name sdl -type f -delete
	find . -name coverage -type d -exec rm -rf {} +

game.o: game.c
	${CC} ${CFLAGS} $(LDFLAG$) ${SRC}/${SERV_DIR}/game.c -c 

server.o: server.c
	${CC} ${CFLAGS} $(LDFLAG$) ${SRC}/${SERV_DIR}/server.c -c 

server_test.o:  ${SRC}/${SERV_DIR}/server_test.c
	${CC} ${CFLAGS} $(LDFLAG$) ${SRC}/${SERV_DIR}/server_test.c -c

server_test_main.o:  ${SRC}/${SERV_DIR}/server_test_main.c
	${CC} ${CFLAGS} $(LDFLAG$) ${SRC}/${SERV_DIR}/server_test_main.c -c

server_test_main: ${SRC}/${SERV_DIR}/server_test_main.o ${SRC}/${SERV_DIR}/server_test.o ${SRC}/${SERV_DIR}/server.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${SERV_DIR}/board.o ${SRC}/${SERV_DIR}/input.o
	mkdir -p ${SRC}/${SERV_DIR}/${DEBUG_DIR}
	${CC} ${SRC}/${SERV_DIR}/server_test_main.o ${SRC}/${SERV_DIR}/server_test.o ${SRC}/${SERV_DIR}/server.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${SERV_DIR}/board.o ${SRC}/${SERV_DIR}/input.o -o $@ ${LDFLAGS}

input.o: input.c
	${CC} ${CFLAGS} ${SRC}/${SERV_DIR}/input.c -c

board.o: board.c
	${CC} ${CFLAGS} ${SRC}/${SERV_DIR}/board.c -c

queue.o: queue.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/queue/queue.c -c

queue_test.o: ${SRC}/${CLI_DIR}/queue/queue_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/queue/queue_test.c -c

queue_test_main.o: ${SRC}/${CLI_DIR}/queue/queue_test_main.c 
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/queue/queue_test_main.c -c

queue_test_main: ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/queue/queue_test.o ${SRC}/${CLI_DIR}/queue/queue_test_main.o
	${CC} ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/queue/queue_test.o ${SRC}/${CLI_DIR}/queue/queue_test_main.o -o $@ ${LDFLAGS}

bfs.o: bfs.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/graph/bfs.c -c

bfs_test.o: ${SRC}/${CLI_DIR}/graph/bfs_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/graph/bfs_test.c -c

bfs_test_main.o: ${SRC}/${CLI_DIR}/graph/bfs_test_main.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/graph/bfs_test_main.c -c

bfs_test_main: ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${CLI_DIR}/graph/bfs_test.o ${SRC}/${CLI_DIR}/graph/bfs_test_main.o
	${CC} ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${CLI_DIR}/graph/bfs_test.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs_test_main.o -o $@ ${LDFLAGS}

rules.o: rules.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/rules.c -c

rules_test.o: ${SRC}/${CLI_DIR}/rules_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/rules_test.c -c

rules_test_main.o: ${SRC}/${CLI_DIR}/rules_test_main.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/rules_test_main.c -c

rules_test_main: ${SRC}/${CLI_DIR}/rules_test_main.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/rules_test.o
	${CC} ${SRC}/${CLI_DIR}/rules_test_main.o ${SRC}/${CLI_DIR}/rules_test.o ${SRC}/${CLI_DIR}/rules.o -o $@ ${LDFLAGS}

williamsClient.o: williamsClient.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/williamsClient.c -c

williamsClient_test.o: ${SRC}/${CLI_DIR}/williamsClient_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/williamsClient_test.c -c

williamsClient_test_main.o: ${SRC}/${CLI_DIR}/williamsClient_test_main.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/williamsClient_test_main.c -c

astonClient.o: astonClient.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/astonClient.c -c

astonClient_test.o: ${SRC}/${CLI_DIR}/astonClient_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/astonClient_test.c -c

astonClient_test_main.o: ${SRC}/${CLI_DIR}/astonClient_test_main.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/astonClient_test_main.c -c

haasClient.o: haasClient.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/haasClient.c -c

haasClient_test.o: ${SRC}/${CLI_DIR}/haasClient_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/haasClient_test.c -c

haasClient_test_main.o: ${SRC}/${CLI_DIR}/haasClient_test_main.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/haasClient_test_main.c -c

client_test.o: ${SRC}/${CLI_DIR}/client_test.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/client_test.c -c

williamsClient_test_main: ${SRC}/${CLI_DIR}/williamsClient.o  ${SRC}/${CLI_DIR}/williamsClient_test_main.o ${SRC}/${CLI_DIR}/williamsClient_test.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o
	${CC} ${SRC}/${CLI_DIR}/williamsClient.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/williamsClient_test.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/williamsClient_test_main.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o -o $@ ${LDFLAGS}

astonClient_test_main: ${SRC}/${CLI_DIR}/astonClient.o  ${SRC}/${CLI_DIR}/astonClient_test_main.o ${SRC}/${CLI_DIR}/astonClient_test.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o
	${CC} ${SRC}/${CLI_DIR}/astonClient.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/astonClient_test.o ${SRC}/${CLI_DIR}/astonClient_test_main.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o -o $@ ${LDFLAGS}

haasClient_test_main: ${SRC}/${CLI_DIR}/haasClient.o  ${SRC}/${CLI_DIR}/haasClient_test_main.o ${SRC}/${CLI_DIR}/haasClient_test.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o
	${CC} ${SRC}/${CLI_DIR}/haasClient.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/haasClient_test.o ${SRC}/${CLI_DIR}/haasClient_test_main.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/graph/bfs.o -o $@ ${LDFLAGS}

display.o: display.c
	${CC} ${CFLAGS} ${SRC}/${DISP_DIR}/display.c -c

display_test.o: ${SRC}/${DISP_DIR}/display_test.c
	${CC} ${CFLAGS} ${SRC}/${DISP_DIR}/display_test.c -c

display_test_main.o: ${SRC}/${DISP_DIR}/display_test_main.c
	${CC} ${CFLAGS} ${SRC}/${DISP_DIR}/display_test_main.c -c

display_test_main: ${SRC}/${DISP_DIR}/display_test_main.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${DISP_DIR}/display_test.o
	${CC} ${SRC}/${DISP_DIR}/display_test_main.o ${SRC}/${DISP_DIR}/display_test.o ${SRC}/${DISP_DIR}/display.o -o $@ ${LDFLAGS}

alltests.o: alltests.c
	${CC} ${CFLAGS} ${SRC}/${CLI_DIR}/alltests.c -c

alltests: ${SRC}/${CLI_DIR}/williamsClient.o ${SRC}/${CLI_DIR}/alltests.o ${SRC}/${SERV_DIR}/server.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${CLI_DIR}/queue/queue_test.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/williamsClient_test.o ${SRC}/${CLI_DIR}/rules_test.o ${SRC}/${CLI_DIR}/graph/bfs_test.o ${SRC}/${SERV_DIR}/server_test.o ${SRC}/${DISP_DIR}/display_test.o ${SRC}/${SERV_DIR}/board.o ${SRC}/${SERV_DIR}/input.o
	${CC} ${SRC}/${CLI_DIR}/williamsClient.o ${SRC}/${CLI_DIR}/alltests.o ${SRC}/${SERV_DIR}/server.o ${SRC}/${CLI_DIR}/queue/queue.o ${SRC}/${CLI_DIR}/rules.o ${SRC}/${CLI_DIR}/graph/bfs.o ${SRC}/${DISP_DIR}/display.o ${SRC}/${CLI_DIR}/queue/queue_test.o ${SRC}/${CLI_DIR}/client_test.o ${SRC}/${CLI_DIR}/williamsClient_test.o ${SRC}/${CLI_DIR}/rules_test.o ${SRC}/${CLI_DIR}/graph/bfs_test.o ${SRC}/${SERV_DIR}/server_test.o ${SRC}/${DISP_DIR}/display_test.o ${SRC}/${SERV_DIR}/board.o ${SRC}/${SERV_DIR}/input.o -o $@ ${LDFLAGS}

coverage: test
	./server_test_main
	./queue_test_main
	./bfs_test_main
	./williamsClient_test_main
	./astonClient_test_main
	./haasClient_test_main
	./rules_test_main
	./display_test_main
	gcov ${SRC}/${SERV_DIR}/server_test_main.gcno
	gcov ${SRC}/${CLI_DIR}/queue/queue_test_main.gcno
	gcov ${SRC}/${CLI_DIR}/graph/bfs_test_main.gcno
	gcov ${SRC}/${CLI_DIR}/williamsClient_test_main.gcno
	gcov ${SRC}/${CLI_DIR}/astonClient_test_main.gcno
	gcov ${SRC}/${CLI_DIR}/haasClient_test_main.gcno
	gcov ${SRC}/${CLI_DIR}/rules_test_main.gcno
	gcov ${SRC}/${DISP_DIR}/display_test_main.gcno
	lcov -c -d .. -o coverage.info
	mkdir -p coverage
	genhtml -o coverage coverage.info

sdl: sdl_dir/sdl.c
	gcc $(SDL_CFLAGS) sdl_dir/sdl.c $(SDL_LDFLAGS) -o sdl

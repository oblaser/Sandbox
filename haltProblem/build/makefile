#
# author:       Oliver Blaser
#
# date c:       07.11.2020
# date e:       12.11.2020
#

CC = g++
LINK = g++

CFLAGS = -c -Wall -W -O0 -pedantic
LFLAGS = -Wall -W -O0 -pedantic

OBJS = main.o
EXE = haltProblem

$(EXE): $(OBJS)
	$(LINK) $(LFLAGS) -o $(EXE) $(OBJS)

main.o: ../main.cpp
	$(CC) $(CFLAGS) ../main.cpp

run: $(EXE)
	@echo ""
	@echo "--================# run #================--"
	./$(EXE) -h

clean:
	rm $(OBJS)
	rm $(EXE)

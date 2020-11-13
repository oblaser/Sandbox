#
# author:       Oliver Blaser
#
# date c:       25.10.2020
# date e:       13.11.2020
#

CC = g++
LINK = g++

#CC = aarch64-linux-gnu-g++
#LINK = aarch64-linux-gnu-g++

CFLAGS = -c -D _DEBUG -Wall -W -O0 -pedantic
LFLAGS = -D _DEBUG -Wall -W -O0 -pedantic

#CFLAGS = -c -Wall -W -O0 -pedantic
#LFLAGS = -Wall -W -O0 -pedantic

DEFAULTDEPENDENCIES = ../project.h

OBJS = main.o cli.o
EXE = cliTextFormat

$(EXE): $(OBJS)
	$(LINK) $(LFLAGS) -o $(EXE) $(OBJS)

main.o: ../main.cpp ../cli.h $(DEFAULTDEPENDENCIES)
	$(CC) $(CFLAGS) ../main.cpp

cli.o: ../cli.cpp ../cli.h $(DEFAULTDEPENDENCIES)
	$(CC) $(CFLAGS) ../cli.cpp

run: $(EXE)
	@echo ""
	@echo "--================# run #================--"
	./$(EXE)

clean:
	rm $(OBJS)
	rm $(EXE)

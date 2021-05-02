CFLAGS=-std=c11 -g -Wall -Wunused-parameter

SRC=$(wildcard *.c)
EXE=whatisalpha
TXT=class_ALL.txt
SUMMARY=SUMARRY.txt
SH=$(EXE).sh

all:	../$(TXT)

../$(TXT):	$(EXE)
	./$(EXE) > $(TXT)
	./$(SH) | tee $(SUMMARY)
	mv *.txt ..

$(EXE):  $(SRC)
	$(CC) $(CFLAGS) -I. -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -f $(EXE) *.txt ../*.txt

.PHONY: all clean

CFLAGS=-std=c11 -g -Wall -Wunused-parameter

SRC=$(wildcard *.c)
EXE=whatisalpha
DATA=UnicodeData.txt
ALL=class_ALL.txt
SUMMARY=SUMARRY.txt
SH=$(EXE).sh

all:	../$(ALL) $(DATA)

$(DATA):
	if [ ! -e $(DATA) ]; then wget http://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt; fi

../$(ALL):	$(EXE)
	./$(EXE) > $(ALL)
	./$(SH) | tee $(SUMMARY)
	mv class_*.txt $(SUMMARY) ..

$(EXE):  $(SRC)
	$(CC) $(CFLAGS) -I. -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -f $(EXE) *.txt ../*.txt

.PHONY: all clean

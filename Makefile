OUTNAME="sws"

all: *.c
	cc -Wall -pedantic main.c net.c util.c -o $(OUTNAME) -lbsd

clean:
	rm $(OUTNAME)

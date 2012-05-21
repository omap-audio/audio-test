include ../Makefile.inc

DIRS	= omap4plus
BIN	= socfw
OBJS	= socfw.o
SOURCE	= socfw.c socfw.h

all : $(BIN)
	-for d in $(DIRS); do (cd $$d; make $(MFLAGS) ); done

$(BIN) : $(SOURCE)
	gcc -o $(BIN) $(SOURCE) -I $(ALSA_INC_DIR)

clean :
	rm -f $(BIN) $(OBJS)
	-for d in $(DIRS); do (cd $$d; make clean ); done

force_look :
	true

include ../../Makefile.inc

DIRS	= dapm coeffs
BIN	= abefw
OBJS	= abefw.o
SOURCE	= abefw.c abefw.h

all : $(BIN)
	-for d in $(DIRS); do (cd $$d; make $(MFLAGS) ); done

$(BIN) : $(SOURCE)
	gcc -o $(BIN) $(SOURCE) -I $(ALSA_INC_DIR) -I $(KERNEL_INC_DIR)

clean :
	rm -f $(BIN) $(OBJS)
	-for d in $(DIRS); do (cd $$d; make clean ); done

force_look :
	true

include ../../../Makefile.inc
include ../Makefile.inc

OBJS	= abe-dl1dl2-twl6040.o
SOBJS	= abe-dl1dl2-twl6040.so
SOURCE	= abe-dl1dl2-twl6040.c

all : $(SOBJS)
	-for d in $(DIRS); do (cd $$d; make $(MFLAGS) ); done

$(SOBJS) : $(SOURCE) $(OBJS)
	gcc -c -I../../ -I $(ALSA_INC_DIR) -I $(ABE_INC_DIR) -g -O2 -pipe $(SOURCE) -shared -fPIC -DPIC
	ld -module -fPIC -DPIC $(OBJS) -o $(SOBS)

clean :
	rm -f $(SOBJS)

force_look :
	true


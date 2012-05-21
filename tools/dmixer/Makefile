include Makefile.inc

DIRS	= src

all :
	-for d in $(DIRS); do (cd $$d; make $(MFLAGS) ); done

clean :
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_check :
	true

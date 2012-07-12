gen: ../abe/abe_hal/abe_firmware.c abe_addr.c abe_asrc.c header.c
	gcc abe_addr.c abe_asrc.c header.c -o gen

fw:	gen
	./header

all:	gen fw


.PHONY: all cleansub
all:
	mkpsxiso -y isoconfig.xml
	rm -f rotating-cube rotating-cube.bin
	rm -f *.map
	rm -f *.elf
	rm -f *.o rm -f *.dep
	rm -f *.ps-exe

cleansub:
	$(MAKE) clean
	rm -f rotating-cube.cue rotating-cube.bin

TARGET = rotating-cube
SRCS = Main.c

include ../../Makefile
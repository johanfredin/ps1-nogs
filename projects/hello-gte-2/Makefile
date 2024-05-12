.PHONY: all cleansub
all:
	mkpsxiso -y isoconfig.xml
	rm -f hello-gte-2 hello-gte-2.bin
	rm -f *.map
	rm -f *.elf
	rm -f *.o rm -f *.dep
	rm -f *.ps-exe

cleansub:
	$(MAKE) clean
	rm -f hello-gte-2.cue hello-gte-2.bin

TARGET = hello-gte-2
SRCS = Main.c

include ../../Makefile
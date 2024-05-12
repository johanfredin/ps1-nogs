.PHONY: all cleansub
all:
	mkpsxiso -y isoconfig.xml
	rm -f hello-gte-1 hello-gte-1.bin
	rm -f *.map
	rm -f *.elf
	rm -f *.o rm -f *.dep
	rm -f *.ps-exe

cleansub:
	$(MAKE) clean
	rm -f hello-gte-1.cue hello-gte-1.bin

TARGET = hello-gte-1
SRCS = Main.c

include ../../Makefile
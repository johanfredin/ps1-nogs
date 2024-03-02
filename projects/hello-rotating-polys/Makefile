.PHONY: all cleansub
all:
	mkpsxiso -y isoconfig.xml
	rm -f hello-rotating-polys hello-rotating-polys.bin
	rm -f *.map
	rm -f *.elf
	rm -f *.o rm -f *.dep
	rm -f *.ps-exe

cleansub:
	$(MAKE) clean
	rm -f hello-rotating-polys.cue hello-rotating-polys.bin

TARGET = hello-rotating-polys
SRCS = Main.c

include ../../Makefile
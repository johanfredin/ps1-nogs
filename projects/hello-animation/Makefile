.PHONY: all cleansub
all:
	mkpsxiso -y isoconfig.xml
	rm -f hello-animation hello-animation.bin
	rm -f *.map
	rm -f *.elf
	rm -f *.o rm -f *.dep
	rm -f *.ps-exe

cleansub:
	$(MAKE) clean
	rm -f hello-animation.cue hello-animation.bin

TARGET = hello-animation
SRCS = Main.c

include ../../Makefile
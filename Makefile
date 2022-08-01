TARGET = microsexual

SRCS = main.c \

.PHONY: all cleansub

all:
	mkpsxiso -y ./isoconfig.xml

cleansub:
	$(MAKE) clean
	rm -f $(TARGET).cue $(TARGET).bin

include ./common.mk

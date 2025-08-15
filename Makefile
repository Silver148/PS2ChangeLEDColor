EE_BIN = PS2ChangeLEDColor.elf
EE_OBJS = main.o
EE_LIBS = -lkernel -ldebug -lcdvd
EE_CFLAGS = -O3 -Wall

all:$(EE_BIN)
	$(EE_STRIP) --strip-all $(EE_BIN)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

run:
	ps2client execee host:$(EE_BIN)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
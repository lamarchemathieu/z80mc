# définition de quelques variables
TARGET  := out
CC      := sdcc
AS	:= sdasz80
LFLAGS  := -Wl-u
MFLAGS  := -mz80 --code-loc 0x8200 --data-loc 0x0000 --vc --no-std-crt0

SRCS=${wildcard *.c}
ASMS=${wildcard *.s}
RELS=${ASMS:.s=.rel} ${SRCS:.c=.rel}

all: ${TARGET}.bin

%.rel:%.s
	@echo " [AS] $<"
	@$(AS) -plosgffw $@ $<

%.rel:%.c
	@echo " [CC] $<"
	@$(CC) $(MFLAGS) $(LFLAGS) -o $@ -c $<

${TARGET}.ihx: ${RELS}
	@echo " [LD] $@"
	@$(CC) $(MFLAGS) $(LFLAGS) -o $@  ${RELS}

${TARGET}.bin: ${TARGET}.ihx
	@echo " [BIN] $<"
	@objcopy -I ihex --output-target=binary $< $@

clean:
	@echo " [RM] $@"
	@rm -f *.cdb *.rel *.hex *.ihx *.lst *.map *.o *.rst \
	*.sym *.lnk *.lib *.bin *.mem *.lk *.noi *.asm *.txt *.com

print-%:
	@echo "$* = ${$*}"


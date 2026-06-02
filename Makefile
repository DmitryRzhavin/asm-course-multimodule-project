CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

.PHONY: all clean test

# Сборка:
#   make
all: integral

integral: main.o integral.o root.o functions.o functions_asm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o: main.c functions.h

integral.o: integral.c functions.h

root.o: root.c functions.h

functions.o: functions.c functions.h

functions_asm.o: functions.asm
	nasm -f elf32 -o $@ $<

# Тестирование:
#   make test
test: integral
	@echo "=== ROOT TESTS ==="
	./integral -R 1:2:4:6:0.000001:5.09838671
	./integral -R 1:3:1:2:0.000001:1.37701474
	./integral -R 2:3:4:5:0.000001:4.26854404

	@echo ""
	@echo "=== INTEGRAL TESTS ==="
	./integral -I 1:0:1:0.000001:4.039720771
	./integral -I 2:0:1:0.000001:-8.25000000
	./integral -I 3:1:5:0.000001:8.04718956

# Очистка:
#   make clean
clean:
	rm -f *.o integral
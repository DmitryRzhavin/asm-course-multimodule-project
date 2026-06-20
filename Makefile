CFLAGS ?= -O2 -g
CFLAGS += -std=gnu99
CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
          -Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
          -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
          -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
          -Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value
CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error
CFLAGS += -m32 -no-pie -fno-pie

LDLIBS = -lm

# По умолчанию используется метод хорд
ROOT_OBJ = root_hord.o

.PHONY: all clean test newton

##################################################
# Основная цель
##################################################
all: integral

##################################################
# Метод Ньютона
##################################################
newton:
	$(MAKE) clean
	$(MAKE) integral CFLAGS="$(CFLAGS) -DUSE_NEWTON" ROOT_OBJ=root_newton.o

##################################################
# Линковка
##################################################
integral: main.o integral.o $(ROOT_OBJ) functions.o functions_asm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

##################################################
# Шаблоны компиляции
##################################################
%.o: %.c functions.h
	$(CC) $(CFLAGS) -c $< -o $@

functions_asm.o: functions.asm
	nasm -f elf32 -o $@ $<

##################################################
# Тесты (тестовые функции f4 и f5)
##################################################
test: integral
	@echo "=== ROOT TESTS (f4, f5) ==="
	./integral -R 4:5:3.0:4.0:0.000001:3.3027756
	./integral -R 4:5:-1.0:0.0:0.000001:-0.3027756
	./integral -R 4:5:0.0:4.0:0.000001:3.3027756
	@echo ""
	@echo "=== INTEGRAL TESTS (f4, f5) ==="
	./integral -I 4:0.0:2.0:0.000001:2.6666667
	./integral -I 5:0.0:3.0:0.000001:16.5000000
	./integral -I 4:1.0:3.0:0.000001:8.6666667

##################################################
# Очистка
##################################################
clean:
	rm -f *.o integral
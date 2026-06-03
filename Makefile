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

##################################################
# Основное задание (метод хорд)
##################################################

all: integral

integral: main_hord.o integral.o root_hord.o functions.o functions_asm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

##################################################
# Дополнительное задание (метод Ньютона)
##################################################

newton: integral_newton

integral_newton: main_newton.o integral.o root_newton.o functions.o functions_asm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

##################################################
# Объектные файлы
##################################################

main_hord.o: main_hord.c functions.h

main_newton.o: main_newton.c functions.h

integral.o: integral.c functions.h

root_hord.o: root_hord.c functions.h

root_newton.o: root_newton.c functions.h

functions.o: functions.c functions.h

functions_asm.o: functions.asm
	nasm -f elf32 -o $@ $<

##################################################
# Тесты метода хорд
##################################################

test: integral
	@echo "=== CHORD METHOD ==="
	./integral -R 1:2:4:6:0.000001:5.09838671
	./integral -R 1:3:1:2:0.000001:1.37701474
	./integral -R 2:3:4:5:0.000001:4.26854404

	@echo ""
	@echo "=== INTEGRAL TESTS ==="
	./integral -I 1:0:1:0.000001:4.039720771
	./integral -I 2:0:1:0.000001:-8.25000000
	./integral -I 3:1:5:0.000001:8.04718956

##################################################
# Тесты метода Ньютона
##################################################

test_newton: integral_newton
	@echo "=== NEWTON METHOD ==="
	./integral_newton -R 1:2:4:6:0.000001:5.09838671
	./integral_newton -R 1:3:1:2:0.000001:1.37701474
	./integral_newton -R 2:3:4:5:0.000001:4.26854404

	@echo ""
	@echo "=== INTEGRAL TESTS ==="
	./integral_newton -I 1:0:1:0.000001:4.039720771
	./integral_newton -I 2:0:1:0.000001:-8.25000000
	./integral_newton -I 3:1:5:0.000001:8.04718956

##################################################
# Очистка
##################################################

clean:
	rm -f *.o integral integral_newton
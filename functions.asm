; Реализация целевых функций на языке NASM
;
; Все функции используют соглашение вызова cdecl
; и возвращают значение типа double

section .data

half        dq 0.5
one         dq 1.0
three       dq 3.0

two_half    dq 2.5
nine_half   dq 9.5

five        dq 5.0

section .text

global f1
global f2
global f3

; double f1(double x)
f1:
    push    ebp
    mov     ebp, esp

    fld     qword [ebp + 8]
    fld1
    faddp

    fld     qword [half]
    fdivrp

    fld1
    faddp

    fld     qword [three]
    fmulp

    mov     esp, ebp
    pop     ebp
    ret

; double f2(double x)
f2:
    push    ebp
    mov     ebp, esp

    fld     qword [ebp + 8]

    fld     qword [two_half]
    fmulp

    fld     qword [nine_half]
    fsubp

    mov     esp, ebp
    pop     ebp
    ret

; double f3(double x)
f3:
    push    ebp
    mov     ebp, esp

    fld     qword [five]
    fld     qword [ebp + 8]
    fdivp

    mov     esp, ebp
    pop     ebp
    ret
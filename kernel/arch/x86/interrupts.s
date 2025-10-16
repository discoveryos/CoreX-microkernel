[extern keyboard_handler_main]
section .text
global keyboard_handler_int

keyboard_handler_int:
    pushad
    call keyboard_handler_main
    mov al, 0x20
    out 0x20, al
    popad
    iret


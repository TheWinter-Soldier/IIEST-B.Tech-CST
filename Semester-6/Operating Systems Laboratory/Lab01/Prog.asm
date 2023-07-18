; This is the assembly code for our Bootloader

BITS 16             ; Instruct the system this is 16 bit code

jmp start           ; Jump to the start routine, short being never to return
nop             ; No operations from here

; This is the entry point put nothing else above this, not even
; include statements
start:
    mov ax, 07C0h       ; Setup 4k stack space after this bootloader
    add ax, 288     ; (4096+515) / 16 bytes per paragraph
    cli         ; Disable Interrupts
    mov ss, ax
    mov sp, 4096
    sti         ; Enable Interrupts

    mov ax, 07C0h       ; Set data segment to the load point of
    mov ds, ax      ; our application

    call PrintWelcome   ; Call the print welcome message routine
    jmp .loopHere       ; Jump to the loop here label

   .loopHere:
    jmp .loopHere       ; Jump to the loop here label
                ; this is now an infinite loop
                ; so all our system did was boot
                ; welcome us and sit spinning
                ; on this label


;------------------------------
; Constants
;------------------------------
c_WelcomeMessage    db  "Hello, Kuldip Kundu!", 0x0
;------------------------------


;----------------------------------------
; Routine to print the welcome message
; this is our only procedure in the
; application, so enjoy!
;----------------------------------------
PrintWelcome:
    mov si, c_WelcomeMessage        ; Move the string into si
    call PrintString            ; Call our routine to output til 0x00
    ret                 ; Return to the call point
;----------------------------------------


;----------------------------------------
; Print string Routine
;    PrintString (SI)
;----------------------------------------
PrintString:            ; Routine to output string in SI to the Screen
    push ax         ; Push the AX register to the stack
    mov ah, 0Eh     ; int 10h 'print char' function code

.repeat:
    lodsb           ; Get character from string
    cmp al, 0x00        ; Compare the character with zero (0)
    je .done        ; if the character is zero then end of string
    int 10h         ; Otherwise call BIOS interupt 10 to print
    jmp .repeat     ; And now jump back up to the repeat label

.done:
    pop ax          ; Pop the copy of the AX register off the stack
    ret         ; Return the call stack back to the call point
;----------------------------------------



; Now we need to pad the remainder of the boot sector with 0s
times 510-($-$$) db 0       ; Times is a macro for nasm to repeat an action during
                ; compilation of the the application binary, in this
                ; case to add 510 lest the amount of data and code in
                ;the program to the output file

; Why 510, why not 512? A boot sector being 512 bytes?... well...
; to tell the BIOS this application, when written to the MBR, is
; a boot sector, we need to add two bytes to the end of the
; application, so we call define word with 0xaa and 0x55 now

dw 0xAA55       ; Standard PC boot Signature



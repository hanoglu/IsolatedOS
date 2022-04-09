;kernel.asm
;Copyright (C) 2021  Yusuf K. Hanoğlu
;This program is free software; you can redistribute it and/or
;modify it under the terms of the GNU General Public License
;as published by the Free Software Foundation; version 2
;of the License.
;This program is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.
;You should have received a copy of the GNU General Public License
;along with this program; if not, write to the Free Software
;Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

section .boot
bits 16
global boot
boot:

	jmp word 0:flush ;#FAR jump so that you set CS to 0. (the first argument is what segment to jump to. The argument(after the `:`) is what offset to jump to)
	;# Without the far jmp, CS could be `0x7C0` or something similar, which will means that where the assembler thinks the code is loaded and where your computer loaded the code is different. Which in turn messes up the absolute addresses of labels.
	flush: ;#We go to here, but we do it ABSOLUTE. So with this, we can reset the segment and offset of where our code is loaded.
	mov BP,0 ;#use BP as a temp register
	mov DS,BP ;#can not assign segment registers a literal number. You have to assign to a register first.
	mov ES,BP ;#do the same here too
	;#without setting DS and ES, they could have been loaded with the old 0x7C0, which would mess up absolute address calculations for data. 
	jmp devam1







enable_vesa:
	pusha
vbe_get_info:

    mov ah, 4Fh;        Super VGA support
    mov al, 00h;        Return Super VGA information
    mov di, vbe_info;   Pointer to buffer

    int 0x10;

    cmp ax, 0x4F                ; BIOS doesn't support VBE?
    call error

get_mode_info:

    mov ax, 4F01h;        Return mode information
    mov cx, 0x105;[vbe_info.video_modes]; first mode 0x101
    mov di, mode_info;  Pointer to buffer

    int 0x10;

    cmp ax, 0x4F                ; BIOS doesn't support VBE?
    call error

;jmp komutmodu
popa
ret
  
draw:

    ;Assume first window is valid 
    mov ax, WORD [es:mode_info + 08h]
    mov es, ax

    ;Example of how to change the window 
    mov ax, 4f05h
    xor bx, bx
    mov dx, 5       ;This is granularity units
    int 10h

    ;fist atempt
    mov edi, [mode_info.framebuffer];   framebuffer
    add edi, 290050;                        pixel_offset = y * pitch + ( x * ( bpp/8 )) + framebuffer;
    mov al,0x0F;                        the color of the pixel
    mov [edi], al


   

	

error:
popa

pusha
ret
yazdir:
	pusha
	mov ah, 0x0e
yazdir_1:
	lodsb
	int 10h
	cmp al,0
	jnz yazdir_1
	popa
	ret

devam1:

;mov edi,0x0A0000
;mov al,0x0F
;mov [edi],al

	;mov [disk],dl

	mov ah, 0x02    ;read sectors
	mov al, 0x40      ; 0x40 sectors to read
	mov ch, 0      ;cylinder idx
	mov dh, 0      ;head idx
	mov cl, 2      ;sector idx
	mov dl, 0x80 ;disk idx	[disk]
	mov bx, copy_target;target pointer

	;push bx
	;mov bx,0x0000
	;mov es,bx
	;pop bx
	;mov bx,copy_target
	
	int 0x13
	jc disk_hatasi

	mov ax, 0x3
	int 0x10

	;vga
	mov ax, 0x2401
	int 0x15
			;0x3 text mode
	;mov ax, 0x13
	;int 0x10
	

call enable_vesa

mov ax, 0x4F02
mov bx, 0105h;0105h vesa video mode 1024x768  256C ilk bit lfb
	     ;0107h vesa video mode 1280x1024 256C
	     ;011Ch vesa video mode 1600x1200 256C
int 0x10


	

call enable_vesa

mov ax, 0x4F02
mov bx, 0105h;0105h vesa video mode 1024x768  256C ilk bit lfb
	     ;0107h vesa video mode 1280x1024 256C
	     ;011Ch vesa video mode 1600x1200 256C
int 0x10

	jmp devam3

komutmodu:
	mov [hangi_mod], byte 1
	mov ax, 0x2401
	int 0x15
			;0x3 text mode
	mov ax, 0x3
	int 0x10

devam3:
	;disk okuma isleminin eski konumu

	jmp devam2
disk_hatasi:
	mov si, disk_hata_mesaji
	call yazdir
disk_hatasi_1:
	jmp disk_hatasi_1

	popa	
	ret
devam2:
	cli
	lgdt [gdt_pointer]
	mov eax, cr0
	or eax,1
	mov cr0, eax
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp CODE_SEG:boot2
	;jmp 0x0000:boot2
gdt_start:
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start
	dd gdt_start
disk:
	db 0x0
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
disk_hata_mesaji: db "Disk read ERROR",0x000a,0x000d,0
hangi_mod: db 0
times 510 - ($-$$) db 0
dw 0xaa55
section .bss
vbe_info:

    .signature db "VBE2";   // must be "VESA" to indicate valid VBE support
    .version resw 1;            // VBE version; high byte is major version, low byte is minor version
    .oem resd 1;            // segment:offset pointer to OEM
    .capabilities resd 1;       // bitfield that describes card capabilities
    .video_modes resd 1;        // segment:offset pointer to list of supported video modes
    .video_memory resw 1;       // amount of video memory in 64KB blocks
    .software_rev resw 1;       // software revision
    .vendor resd 1;         // segment:offset to card vendor string
    .product_name resd 1;       // segment:offset to card model name
    .product_rev resd 1;        // segment:offset pointer to product revision
    .reserved resb 222;     // reserved for future expansion
    .oem_data resb 256;     // OEM BIOSes store their strings in this area

mode_info:

    .attributes resw 1;     // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    .window_a resb 1;           // deprecated
    .window_b resb 1;           // deprecated
    .granularity resw 1;        // deprecated; used while calculating bank numbers
    .window_size resw 1;
    .segment_a resw 1;
    .segment_b resw 1;
    .win_func_ptr resd 1;       // deprecated; used to switch banks from protected mode without returning to real mode
    .pitch resw 1;          // number of bytes per horizontal line
    .width resw 1;          // width in pixels
    .height resw 1;         // height in pixels
    .w_char resb 1;         // unused...
    .y_char resb 1;         // ...
    .planes resb 1;
    .bpp resb 1;            // bits per pixel in this mode
    .banks resb 1;          // deprecated; total number of banks in this mode
    .memory_model resb 1;
    .bank_size resb 1;      // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    .image_pages resb 1;
    .reserved0 resb 1;

    .red_mask resb 1;
    .red_position resb 1;
    .green_mask resb 1;
    .green_position resb 1;
    .blue_mask resb 1;
    .blue_position resb 1;
    .reserved_mask resb 1;
    .reserved_position resb 1;
    .direct_color_attributes resb 1;

    .framebuffer resd 1;        // physical address of the linear frame buffer; write here to draw to the screen
    .off_screen_mem_off resd 1;
    .off_screen_mem_size resw 1;    // size of memory in the framebuffer but not being displayed on the screen
    .reserved1 resb 206;


section .boot


copy_target:
bits 32
	hello: db "                                 IsolatedOS Version: A                                     ",0
boot2:

; Disable blink
	; Read I/O Address 0x03DA to reset index/data flip-flop
	mov dx, 0x03DA
	in al, dx
	; Write index 0x30 to 0x03C0 to set register index to 0x30
	mov dx, 0x03C0
	mov al, 0x30
	out dx, al
	; Read from 0x03C1 to get register contents
	inc dx
	in al, dx
	; Unset Bit 3 to disable Blink
	and al, 0xF7
	; Write to 0x03C0 to update register with changed value
	dec dx
	out dx, al



	mov esi,hello
	mov ebx,0xb8000
.loop:
	lodsb
	or al,al
	jz halt
	or eax,0xe000 ;0x0F00
	mov word [ebx], ax
	add ebx,2
	jmp .loop
halt:

	mov esp,kernel_stack_top
	cmp [hangi_mod],byte 1
	jz sadecekomut
	extern wmain



	mov edi, [mode_info.framebuffer]
	push edi
	call wmain
	jmp devam4
sadecekomut:
	extern kmain
	call kmain
devam4:

	cli
	hlt

section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384 ; 16 KB
kernel_stack_top:

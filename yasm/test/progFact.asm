extern __imp__MessageBoxA@16
extern __imp__ExitProcess@4
extern __imp__wsprintfA
%assign MB_ICONINFORMATION 40h

       section .text
       global _start

_start:  
	mov ecx,5
	mov eax,1
l1:
	mul ecx
	dec ecx
	jnz l1
	
	push eax
	push format
	push buffer	
	call [__imp__wsprintfA]
	add esp,12
	push MB_ICONINFORMATION
	push hello_title
	push buffer
	push 0
	call [__imp__MessageBoxA@16]
	push 0
	call [__imp__ExitProcess@4]

	section .rdata
hello_title:	db "Title1",0
format:			db "%i",0
	section .bss
buffer:			resb 12
	end

extern __imp__MessageBoxA@16
extern __imp__ExitProcess@4
extern __imp__wsprintfA
%assign MB_ICONINFORMATION 40h

       section .text
       global _start

_start:  
	push 42
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
		section .data
buffer:			db "      ",0

end

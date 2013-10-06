extern __imp__MessageBoxA@16
extern __imp__ExitProcess@4

%assign MB_ICONINFORMATION 40h

	section .text
	global _start

_start:
	push MB_ICONINFORMATION
	push hello_title
	push message
	push 0
	call [__imp__MessageBoxA@16]
	push 0
	call [__imp__ExitProcess@4]

	section .rdata

hello_title: db "title", 0
message: db "hello, world", 0
	
	end
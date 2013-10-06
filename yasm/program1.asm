extern __imp__MessageBoxA@16
extern __imp__ExitProcess@4
extern __imp__wsprintfA
%assign MB_ICONIFORMATION 40h

       section .txt
       global _start

_start:
       push buffer
       push format
       push 42
       call [__imp__wsprintfA]
       push MB_ICONIFORMATION
       push hello_title
       push buffer
       push 0
       call [__imp__MessageBoxA@16]
       push 0
       call [__imp__ExitProcess@4]

       section .rdata
hello_title: db "okoIIIe4ko",0
format: db "%d",0
buffer: db "      ",0
end

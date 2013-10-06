extern __imp__MessageBoxA@16
extern __imp__ExitProcess@4

%assign MB_ICONINFORMATION 40h

	section .text
	global _start
	
str2dw:
	xor dx,dx		;�����
@lp1:	xor ax,ax
	lodsb			;����� c�����
	test al,al		;���� ��� ����� ����, �� �����������
	jz @ex
	cmp al,'9'		;���� ��� �� �����, �� ����������
	jnbe @lp1
	cmp al,'0'      ;���� ��� �� �����, �� ����������
	jb @lp1
	sub ax,'0'		;�������� �������� ��������
	shl dx,1		;�������� ����� �� 10
	add ax, dx
	shl dx, 2
	add dx, ax		;���������� ������� ��������
	jmp @lp1
@ex:	mov ax,dx
	ret

	
	
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
message: db "123", 0
	
	end
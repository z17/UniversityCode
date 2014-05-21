	section .text
	global _fdct
	global _idct

_fdct:
	mov eax, [esp+4] ; in
	mov edx, [esp+8] ; out
	mov ecx, [esp+12] ; n
	pushad
	xor ch, ch ; счетчик блоков
	sub esp, 4
fstart:
	mov ebp, matrix ; a
	mov [esp], eax ; b
	mov edi, buffer	; result
	xor bh, bh ; счетчик матриц
fmult0:
	mov bl, 16 ; для целой матрицы
fmult1:
	mov esi, [esp] ; начальное положение
	movups xmm7, [ebp]
	pshufd xmm0, xmm7, 0
	movups xmm1, [esi]
	movups xmm2, [esi + 16]
	add esi, 32
	mulps xmm1, xmm0
	mulps xmm2, xmm0
frow1:
	pshufd xmm0, xmm7, 1
	pshufd xmm0, xmm0, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	pshufd xmm0, xmm7, 2
	pshufd xmm0, xmm0, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	pshufd xmm0, xmm7, 3
	pshufd xmm0, xmm0, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	dec bl
	test bl, 1	
	jnp fpart2 ; если нечетное - идем в fpart2
	test bh, bh
	jz fwrite
	mulps xmm1, [norm1]
	mulps xmm2, [norm1]
fwrite:	
	movups [edi], xmm1
	movups [edi + 16], xmm2 ; записали строчку
	add edi, 32
	;dec bl
	test bl, bl ; счетчик четвертей
	jz fnext0
	jmp fmult1
fpart2:
	; вторая часть строки
	movups xmm7, [ebp + 16]
	add ebp, 32
	pshufd xmm0, xmm7, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	jmp frow1	
fnext0:
	test bh, bh
	jnz fnext1
	inc bh
	mov eax, esi
	mov ebp, buffer
	mov [esp], dword matrix_t
	mov edi, edx
	jmp fmult0
fnext1:
	inc ch ; счетчик блоков
	cmp ch, cl
	je freturn
	mov edx, edi
	jmp fstart
freturn:
	add esp, 4
	popad
	ret	
;---------------------------------------------------------	
_idct:
	mov eax, [esp+4] ; in
	mov edx, [esp+8] ; out
	mov ecx, [esp+12] ; n
	pushad	
	xor ch, ch ; счетчик блоков
	sub esp, 4
istart:
	mov ebp, matrix_t ; a
	mov [esp], eax ; b
	mov edi, buffer ; result
	xor bh, bh ; для смены матриц
imult0:
	mov bl, 16 ; для целой матрицы
imult1:
	mov esi, [esp] ; начальное положение
	movups xmm7, [ebp]
	pshufd xmm0, xmm7, 0
	movups xmm1, [esi]
	movups xmm2, [esi + 16]
	add esi, 32
	mulps xmm1, xmm0
	mulps xmm2, xmm0
irow1:
	pshufd xmm0, xmm7, 1
	pshufd xmm0, xmm0, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	pshufd xmm0, xmm7, 2
	pshufd xmm0, xmm0, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	pshufd xmm0, xmm7, 3
	pshufd xmm0, xmm0, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	dec bl
	test bl, 1
	jnp ipart2 ; если нечетное - идем в fpart2
	test bh, bh
	jz iwrite
	mulps xmm1, [norm2]
	mulps xmm2, [norm2]
iwrite:
	movups [edi], xmm1
	movups [edi + 16], xmm2
	add edi, 32
	test bl, bl ; счетчик четвертей
	jz inext0
	jmp imult1
ipart2:
	; вторая часть строки
	movups xmm7, [ebp + 16]
	add ebp, 32
	pshufd xmm0, xmm7, 0
	movups xmm3, [esi]
	movups xmm4, [esi + 16]
	add esi, 32
	mulps xmm3, xmm0
	mulps xmm4, xmm0
	addps xmm1, xmm3
	addps xmm2, xmm4
	jmp irow1
inext0:
	test bh, bh
	jnz inext1
	inc bh
	mov eax, esi	
	mov ebp, buffer	
	mov [esp], dword matrix
	mov edi, edx
	jmp imult0	
inext1:
	inc ch ; счетчик блоков
	cmp ch, cl
	je ireturn
	mov edx, edi
	jmp istart
ireturn:
	add esp, 4
	popad
	ret
	
	section .data
align 16
buffer: resd 64	
	section .rdata
align 16
norm1: dd 0.125, 0.125, 0.125, 0.125
norm2: dd 8.000, 8.000, 8.000, 8.000
matrix: dd \
 0.35355339059327379, 0.35355339059327379, 0.35355339059327379, 0.35355339059327379,\
 0.35355339059327379, 0.35355339059327379, 0.35355339059327379, 0.35355339059327379,\
 0.49039264020161522, 0.41573480615127262, 0.27778511650980114, 0.09754516100806417,\
-0.09754516100806410,-0.27778511650980098,-0.41573480615127267,-0.49039264020161522,\
 0.46193976625564337, 0.19134171618254492,-0.19134171618254486,-0.46193976625564337,\
-0.46193976625564342,-0.19134171618254517, 0.19134171618254500, 0.46193976625564326,\
 0.41573480615127262,-0.09754516100806410,-0.49039264020161522,-0.27778511650980109,\
 0.27778511650980092, 0.49039264020161522, 0.09754516100806439,-0.41573480615127256,\
 0.35355339059327379,-0.35355339059327373,-0.35355339059327384, 0.35355339059327368,\
 0.35355339059327384,-0.35355339059327334,-0.35355339059327356, 0.35355339059327329,\
 0.27778511650980114,-0.49039264020161522, 0.09754516100806415, 0.41573480615127273,\
-0.41573480615127256,-0.09754516100806401, 0.49039264020161533,-0.27778511650980076,\
 0.19134171618254492,-0.46193976625564342, 0.46193976625564326,-0.19134171618254495,\
-0.19134171618254528, 0.46193976625564337,-0.46193976625564320, 0.19134171618254478,\
 0.09754516100806417,-0.27778511650980109, 0.41573480615127273,-0.49039264020161533,\
 0.49039264020161522,-0.41573480615127251, 0.27778511650980076,-0.09754516100806429 
matrix_t: dd \
 0.35355339059327379, 0.49039264020161522, 0.46193976625564337, 0.41573480615127262,\
 0.35355339059327379, 0.27778511650980114, 0.19134171618254492, 0.09754516100806417,\
 0.35355339059327379, 0.41573480615127262, 0.19134171618254492,-0.09754516100806410,\
-0.35355339059327373,-0.49039264020161522,-0.46193976625564342,-0.27778511650980109,\
 0.35355339059327379, 0.27778511650980114,-0.19134171618254486,-0.49039264020161522,\
-0.35355339059327384, 0.09754516100806415, 0.46193976625564326, 0.41573480615127273,\
 0.35355339059327379, 0.09754516100806417,-0.46193976625564337,-0.27778511650980109,\
 0.35355339059327368, 0.41573480615127273,-0.19134171618254495,-0.49039264020161533,\
 0.35355339059327379,-0.09754516100806410,-0.46193976625564342, 0.27778511650980092,\
 0.35355339059327384,-0.41573480615127256,-0.19134171618254528, 0.49039264020161522,\
 0.35355339059327379,-0.27778511650980098,-0.19134171618254517, 0.49039264020161522,\
-0.35355339059327334,-0.09754516100806401, 0.46193976625564337,-0.41573480615127251,\
 0.35355339059327379,-0.41573480615127267, 0.19134171618254500, 0.09754516100806439,\
-0.35355339059327356, 0.49039264020161533,-0.46193976625564320, 0.27778511650980076,\
 0.35355339059327379,-0.49039264020161522, 0.46193976625564326,-0.41573480615127256,\
 0.35355339059327329,-0.27778511650980076, 0.19134171618254478,-0.09754516100806429
end

TITLE MASM Template						(main.asm)

; Description:
; 
; Revision date:

.686P		; Pentium Pro or later
.MODEL flat, stdcall
.STACK 4096
option casemap:none;  大小写敏感

includelib	msvcrt.lib
printf      PROTO C :ptr byte,:vararg
scanf       PROTO C :dword,:vararg
getchar		PROTO C
_getche		PROTO C
_getch		PROTO C
ExitProcess	PROTO :DWORD	  	; exit program
exit		 equ <INVOKE ExitProcess,0>

chr$ MACRO any_text:VARARG
	LOCAL txtname
	.data      
		txtname db any_text,0
		align 4
	.code
		EXITM <OFFSET txtname>
ENDM

.data
	 buf	BYTE	16 dup (0ffh)
	 ip		DWORD	0
	 op		DWORD	0
	 n		DWORD	0
	 chr	BYTE	0
 .code
main	PROC
	invoke	printf,chr$("请选择：ESC 退出；- 从队列提取元素显示 +打印当前队列；0-9A-Z进入队列，其他抛弃。",0dh,0ah)
start:invoke _getch		;注意用scanf后一定要有这个调用，去掉键盘缓冲区的回车符。
	cmp		al,1BH   ;  ESC 退出
	jz		over
	cmp     al, '+'
	jz		printq
	cmp     al,'-'
	jnz		insert

	push	offset chr
	push	offset op
	push	offset buf
	call	oq				;invoke	oq,offset buf,offset op,offset chr
	add		esp,12
	
	.if eax!=0
	   invoke	printf,chr$("	提取的元素为：%c",0dh,0ah),chr
	.else
	   invoke	printf,chr$("	EMPTY!",0dh,0ah)
	.endif
	jmp	start
insert:
	.if al>='A' && al <='Z' || al>='0' && al <='9'
		push	eax
		invoke	printf, chr$("%c"),al
		pop		eax
		push	eax
		push	offset ip
		push	offset buf
		call	iq		;invoke	iq,offset buf,offset ip,al
		add		esp,12
		.if eax==0
			invoke printf,chr$(0dh, 0ah,"FULL!",0dh,0ah)
		.endif
	.endif
	jmp	start
printq: 
	push	op
	push	ip
	push	offset buf
	call	pq
	add		esp,12
	jmp		start
over:	exit
main	ENDP

incp proc
	push	ebp
	mov		ebp,esp
	push	ebx
	mov		ebx,[ebp+8]
	inc		dword ptr [ebx]
	and		dword ptr[ebx],00000000FH
	pop		ebx
	mov		esp,ebp
	pop		ebp
	ret
incp endp


iq	proc
	push	ebp
	mov		ebp,esp
	push	ebx
	push	edi
	mov		eax,0		;插入了0个元素
	.if n==16
	  jmp	iqover
	.endif	
	mov		ebx,[ebp+8]
	mov		edi,[ebp+12]
	add		ebx,[edi]
	mov		al,[ebp+16]
	mov		[ebx],al
	push	edi
	call	incp
	add		esp,4
	inc		n
	mov		eax,1		;插入了一个元素
iqover:	pop		edi
	pop		ebx
	leave
	ret
iq	endp

oq	proc
	push	ebp
	mov		ebp,esp
	push	ebx
	push	edi
	mov		eax,0		;提取了0个元素
	.if n==0
	  jmp	oqover
	.endif
	mov		ebx,[ebp+8]
	mov		edi,[ebp+12]
	add		ebx,[edi]
	mov		al,[ebx]
	mov		ebx,[ebp+16]
	mov		[ebx],al
	push	edi
	call	incp
	add		 esp, 4
	dec		n
	mov		eax,1		;提取了1个元素
oqover:	pop edi
	pop		ebx
	leave
	ret
oq	endp

pq	proc
	push	ebp
	mov		ebp,esp
	push	ebx
	push	ecx
	push	esi
	push	edi
	
	invoke	printf, chr$(0dh, 0ah,"	当前队列内容为：")
	mov		ebx, [ebp + 8]; buf地址
	mov		esi, [ebp + 12]; ip
	mov		edi, [ebp + 16]; op
	mov		eax,0		;打印了0个元素
	mov		ecx,n
	cmp		ecx,0
	jle		ovl
@@:	mov		al,[ebx+edi]
	push	ecx
	invoke	printf,chr$("%c"),al
	pop		ecx
	inc		edi
	and		edi,0fh
	inc		eax
	loop	 @B
ovl:invoke	printf, chr$("	队首下标为:%2d 队尾下标为:%2d 元素个数为:%2d",0dh,0ah),dword ptr [ebp+16],esi,n
pqover:	pop	edi
	pop		esi
	pop		ecx
	pop		ebx
	leave
	ret
pq	endp

	END main
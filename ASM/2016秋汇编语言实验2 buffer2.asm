TITLE MASM Template						(main.asm)

; Description:
; 
; Revision date:

.686P		; Pentium Pro or later
.MODEL flat, stdcall
.STACK 4096
option casemap:none;  ��Сд����

includelib	msvcrt.lib
printf      PROTO C :ptr byte,:vararg
scanf       PROTO C :dword,:vararg
getchar		PROTO C
_getche		PROTO C
_getch		PROTO C
ExitProcess	PROTO :DWORD	  	; exit program
exit		 equ <INVOKE ExitProcess,0>

incp PROTO C :ptr DWORD
iq   PROTO C :ptr BYTE ,:ptr DWORD,:BYTE
oq   PROTO C :ptr BYTE, :ptr DWORD,:ptr BYTE
pq   PROTO C :ptr BYTE, :DWORD,    :DWORD


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
	invoke	printf,chr$("��ѡ��ESC �˳���- �Ӷ�����ȡԪ����ʾ +��ӡ��ǰ���У�0-9A-Z������У�����������",0dh,0ah)
start:invoke _getche		;ע����scanf��һ��Ҫ��������ã�ȥ�����̻������Ļس�����
	cmp		al,1BH   ;  ESC �˳�
	jz		over
	cmp     al, '+'
	jz		printq
	cmp     al,'-'
	jnz		insert

	invoke	oq,offset buf,offset op,offset chr
	.if eax!=0
	   invoke	printf,chr$("	��ȡ��Ԫ��Ϊ��%c",0dh,0ah),chr
	.else
	   invoke	printf,chr$("	EMPTY!",0dh,0ah)
	.endif
	jmp	start
insert:
	.if al>='A' && al <='Z' || al>='0' && al <='9'
		invoke	iq,offset buf,offset ip,al
		.if eax==0
			invoke printf,chr$(0dh, 0ah," FULL!",0dh,0ah)
		.endif
	.endif
	jmp	start
printq: 
	invoke	pq, offset buf,ip,op
	jmp		start
over:	exit
main	ENDP

incp proc C uses ebx p:ptr DWORD
	mov		ebx,p
	inc		dword ptr [ebx]
	and		dword ptr[ebx],00000000FH
	ret
incp endp


iq	proc C uses ebx edi s:ptr BYTE, p:ptr DWORD, cc:BYTE
	mov		eax,0		;������0��Ԫ��
	.if n==16
	  jmp	iqover
	.endif	
	mov		ebx,s
	mov		edi,p
	add		ebx,[edi]
	mov		al,cc
	mov		[ebx],al
	invoke 	incp,edi
	inc		n
	mov		eax,1		;������һ��Ԫ��
iqover:	ret
iq	endp

oq	proc C uses ebx edi s:ptr BYTE, p:ptr DWORD, cc:ptr BYTE
	mov		eax,0		;��ȡ��0��Ԫ��
	.if n==0
	  jmp	oqover
	.endif
	mov		ebx,s
	mov		edi,p
	add		ebx,[edi]
	mov		al,[ebx]
	mov		ebx,cc
	mov		[ebx],al
	invoke  incp,edi
	dec		n
	mov		eax,1		;��ȡ��1��Ԫ��
oqover:	ret
oq	endp

pq	proc C  uses ebx ecx esi edi s:ptr BYTE, r:DWORD, cc:DWORD
	invoke	printf, chr$(0dh, 0ah,"	��ǰ��������Ϊ��")
	mov		ebx, s; buf��ַ
	mov		esi, r	; ip
	mov		edi, cc	; op
	mov		eax,0		;��ӡ��0��Ԫ��
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
ovl:invoke	printf, chr$("	�����±�Ϊ:%2d ��β�±�Ϊ:%2d Ԫ�ظ���Ϊ:%2d",0dh,0ah),dword ptr [ebp+16],esi,n
pqover:	ret
pq	endp

	END main
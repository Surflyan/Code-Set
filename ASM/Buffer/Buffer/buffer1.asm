INCLUDE ASM32.INC
; ѭ�����е�ʵ��

.data
		buf BYTE 16 dup(? )
		pi DD  0
		po DD  0
		N  DD 0
	    chr DB ?
.code
;��Ӻ���
qi      PROC
		PUSH EBP
		MOV EBP, ESP
		PUSH  EBX
		PUSH  ECX
		PUSH  EDX
		MOV EAX, 0
		CMP N, 16D                       ;�ж��Ƿ�����
		JZ  FULL              

		MOV  EBX, [EBP + 8]                  ;&buf
		MOV  DL, BYTE PTR[EBP + 16]          ;&chr
		MOV  ECX, [EBP+12]
	    MOV  ECX, [ECX]
		LEA  EBX, [EBX + ECX]              
		MOV  BYTE PTR[EBX], DL                ;д��

		PUSH [EBP + 12]                        ;&pi
		CALL incp                              ;�����±�
		ADD  ESP, 4                          
	                                           
		ADD N, 1
		MOV EAX, 1

FULL :  POP  EDX                          ;����
		POP  ECX
		POP  EBX
		LEAVE
		RET
qi      ENDP

;ģ16���ҵ��±�
incp    PROC
		PUSH EBP
		MOV EBP, ESP
		PUSH EAX
		PUSH EBX

		MOV EBX, [EBP + 8]          ;&�±�
		MOV EAX, 0FH
		MOV ECX, [EBX]
		INC ECX
		MOV [EBX], ECX
		AND [EBX], EAX               ;ģ16

		POP EBX
		POP EAX
		LEAVE
		RET
incp    ENDP
; ���Ӻ���
qo	    PROC
		PUSH EBP
		MOV  EBP, ESP
		PUSH EBX
		PUSH EDX
		PUSH ESI

		MOV EAX, 0
		CMP N, 0
		JZ NONE                 ;Ϊ��

		MOV EAX, 1

	    MOV EBX, [EBP + 8]          ;&buf
		MOV ESI, [EBP + 12]         ;&po
		MOV ESI, [ESI] 
		LEA EBX, [EBX + ESI]
		MOV DL, BYTE PTR[EBX]       ;����
	    
	    MOV EBX, [EBP+16]
		MOV BYTE PTR[EBX], DL             ; &chr 

	    PUSH EAX
		PUSH [EBP+12]
		CALL incp                 ;�����±�
		ADD  ESP, 4
	    POP EAX
		ADD N, -1

NONE:   POP ESI              ;��
		POP EDX
		POP EBX
        LEAVE
		RET
qo      ENDP
;��ӡ����
 qp     PROC
		PUSH EBP
		MOV  EBP, ESP
		PUSH EAX
		PUSH EBX
		PUSH EDX
		PUSH ECX

		MOV ECX, N
		CMP ECX, 0
		JZ  NO                 ;Ϊ��

		PUSH ECX
		INVOKE printf, chr$(0ah,0dh,"��ǰ��������Ϊ��")
		POP ECX

		MOV EDX, [EBP + 16]             ;&po
GOON:   MOV EBX, [EBP + 8]              ;&buf
		LEA EBX, [EBX + EDX]
		MOV AL, BYTE PTR[EBX]           ;�������
  
		PUSH ECX
		PUSH EDX
		INVOKE printf, chr$("%c"), AL
		POP EDX
		POP  ECX

        INC EDX
        AND EDX ,0FH

		DEC ECX
		CMP ECX, 0               ;�Ƿ������
		JNZ GOON

        PUSH ECX
        MOV EDX, [EBP + 16]
        MOV EBX, [EBP + 12]
        INVOKE printf, chr$("�����±�Ϊ %d����β�±�Ϊ %d,Ԫ�ظ���Ϊ %d", 0dh, 0ah), EDX, EBX, N
        POP  ECX
        JMP  EXIT

NO :    PUSH ECX
		MOV EDX, [EBP + 16]
		MOV EBX, [EBP + 12]
		INVOKE printf, chr$(0dh,0ah,"��ǰ��������Ϊ�������±�Ϊ %d����β�±�Ϊ %d��Ԫ�ظ���Ϊ %d",0dh,0ah), EBX, EBX,N
		PUSH ECX
EXIT :  POP ECX
		POP EDX
		POP EBX
		POP  EAX
		LEAVE
		RET
 qp     ENDP
 

MAIN    PROC
		INVOKE printf, chr$("��ѡ��ESC �˳��� - �Ӷ�����ȡԪ����ʾ + ��ӡ��ǰ���У�0 - 9A - Z������У�����������", 0dh, 0ah)
INP:    INVOKE _getche
		CMP EAX, 1BH
		JZ  OVER
		CMP EAX, '-'
		JZ  FPO
		CMP EAX, '+'
		JZ  FQP
		CMP EAX, '0'
		JB  INP
		CMP EAX, '9'
		JBE FPI
		CMP EAX, 'A'
		JB INP
		CMP EAX, 'Z'
		JBE FPI
		JMP INP
FPI :   PUSH EAX
		PUSH OFFSET pi
		PUSH OFFSET buf
		CALL qi
		ADD	 ESP, 12
		CMP EAX, 1
		JNZ  FUL
		JMP  INP

FUL:    INVOKE printf, chr$(0dh, 0ah, "full!", 0dh, 0ah)
		JMP INP
FPO:    PUSH OFFSET chr
		PUSH OFFSET po
		PUSH OFFSET buf
		CALL qo
		ADD ESP, 12
		CMP EAX, 1		
		JNZ NON
		INVOKE printf,chr$("��ȡ��Ԫ��Ϊ��%c",0dh,0ah),chr
		JMP INP

NON :   INVOKE printf, chr$(0dh, 0ah, "none", 0dh, 0ah)
		JMP INP

FQP :   PUSH po
		PUSH pi
		PUSH OFFSET buf
		CALL qp
		ADD ESP, 12
		JMP INP

OVER :  INVOKE	 ExitProcess, 0
  MAIN  ENDP
	    END MAIN



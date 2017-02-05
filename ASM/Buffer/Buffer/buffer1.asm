INCLUDE ASM32.INC
; 循环队列的实现

.data
		buf BYTE 16 dup(? )
		pi DD  0
		po DD  0
		N  DD 0
	    chr DB ?
.code
;入队函数
qi      PROC
		PUSH EBP
		MOV EBP, ESP
		PUSH  EBX
		PUSH  ECX
		PUSH  EDX
		MOV EAX, 0
		CMP N, 16D                       ;判断是否已满
		JZ  FULL              

		MOV  EBX, [EBP + 8]                  ;&buf
		MOV  DL, BYTE PTR[EBP + 16]          ;&chr
		MOV  ECX, [EBP+12]
	    MOV  ECX, [ECX]
		LEA  EBX, [EBX + ECX]              
		MOV  BYTE PTR[EBX], DL                ;写入

		PUSH [EBP + 12]                        ;&pi
		CALL incp                              ;更新下标
		ADD  ESP, 4                          
	                                           
		ADD N, 1
		MOV EAX, 1

FULL :  POP  EDX                          ;队满
		POP  ECX
		POP  EBX
		LEAVE
		RET
qi      ENDP

;模16，找到下标
incp    PROC
		PUSH EBP
		MOV EBP, ESP
		PUSH EAX
		PUSH EBX

		MOV EBX, [EBP + 8]          ;&下标
		MOV EAX, 0FH
		MOV ECX, [EBX]
		INC ECX
		MOV [EBX], ECX
		AND [EBX], EAX               ;模16

		POP EBX
		POP EAX
		LEAVE
		RET
incp    ENDP
; 出队函数
qo	    PROC
		PUSH EBP
		MOV  EBP, ESP
		PUSH EBX
		PUSH EDX
		PUSH ESI

		MOV EAX, 0
		CMP N, 0
		JZ NONE                 ;为空

		MOV EAX, 1

	    MOV EBX, [EBP + 8]          ;&buf
		MOV ESI, [EBP + 12]         ;&po
		MOV ESI, [ESI] 
		LEA EBX, [EBX + ESI]
		MOV DL, BYTE PTR[EBX]       ;读出
	    
	    MOV EBX, [EBP+16]
		MOV BYTE PTR[EBX], DL             ; &chr 

	    PUSH EAX
		PUSH [EBP+12]
		CALL incp                 ;更新下标
		ADD  ESP, 4
	    POP EAX
		ADD N, -1

NONE:   POP ESI              ;空
		POP EDX
		POP EBX
        LEAVE
		RET
qo      ENDP
;打印队列
 qp     PROC
		PUSH EBP
		MOV  EBP, ESP
		PUSH EAX
		PUSH EBX
		PUSH EDX
		PUSH ECX

		MOV ECX, N
		CMP ECX, 0
		JZ  NO                 ;为空

		PUSH ECX
		INVOKE printf, chr$(0ah,0dh,"当前队列内容为：")
		POP ECX

		MOV EDX, [EBP + 16]             ;&po
GOON:   MOV EBX, [EBP + 8]              ;&buf
		LEA EBX, [EBX + EDX]
		MOV AL, BYTE PTR[EBX]           ;依次输出
  
		PUSH ECX
		PUSH EDX
		INVOKE printf, chr$("%c"), AL
		POP EDX
		POP  ECX

        INC EDX
        AND EDX ,0FH

		DEC ECX
		CMP ECX, 0               ;是否输出完
		JNZ GOON

        PUSH ECX
        MOV EDX, [EBP + 16]
        MOV EBX, [EBP + 12]
        INVOKE printf, chr$("队首下标为 %d，队尾下标为 %d,元素个数为 %d", 0dh, 0ah), EDX, EBX, N
        POP  ECX
        JMP  EXIT

NO :    PUSH ECX
		MOV EDX, [EBP + 16]
		MOV EBX, [EBP + 12]
		INVOKE printf, chr$(0dh,0ah,"当前队列内容为：队首下标为 %d，队尾下标为 %d，元素个数为 %d",0dh,0ah), EBX, EBX,N
		PUSH ECX
EXIT :  POP ECX
		POP EDX
		POP EBX
		POP  EAX
		LEAVE
		RET
 qp     ENDP
 

MAIN    PROC
		INVOKE printf, chr$("请选择：ESC 退出； - 从队列提取元素显示 + 打印当前队列；0 - 9A - Z进入队列，其他抛弃。", 0dh, 0ah)
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
		INVOKE printf,chr$("提取的元素为：%c",0dh,0ah),chr
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



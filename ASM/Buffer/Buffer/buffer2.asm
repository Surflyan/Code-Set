INCLUDE ASM32.INC
; 循环队列的实现

qi   PROTO C :DWORD, :DWORD , : DWORD
incp PROTO C :DWORD
qo   PROTO C :DWORD, :DWORD , : PTR BYTE 
qp   PROTO C :DWORD, :DWORD,  : DWORD
.data
		buf BYTE 16 dup(? )
		pi DD  0
		po DD  0
		N  DD 0
	    chr DB ?
.code
;入队函数
qi      PROC C USES EDX ECX EBX  buff:DWORD, ppi:DWORD, chrr:DWORD

		MOV EAX, 0
		CMP N, 16D
		JZ  FULL                       ;队满

		MOV  EBX, buff                 ;&buf
		MOV  DL, BYTE PTR chrr             ;&chr
		MOV  ECX, ppi
	    MOV  ECX, [ECX]
		LEA  EBX, [EBX + ECX]              
		MOV  BYTE PTR[EBX], DL            ;赋值

	    INVOKE incp, ppi               ;更新下标

		ADD N, 1
		MOV EAX, 1

FULL :  RET                            ;队满		
qi      ENDP

;模16，找到下标
incp    PROC C USES EAX EBX p:DWORD


		MOV EBX, p             ;&下标
		MOV EAX, 0FH
		MOV ECX, [EBX]
		INC ECX
		MOV [EBX], ECX
		AND [EBX], EAX               ;模16

		RET
incp    ENDP
; 出队函数
qo	    PROC C USES EBX EDX ESI pbuf:DWORD, ppo:DWORD, pchr:PTR BYTE

		MOV EAX, 0
		CMP N, 0
		JZ NONE                  ;为空

		MOV EAX, 1

	    MOV EBX, pbuf            ;&buf
		MOV ESI, ppo             ;&po
		MOV ESI, [ESI] 
		LEA EBX, [EBX + ESI]
		MOV DL, BYTE PTR[EBX]

	    MOV EBX, pchr
		MOV BYTE PTR[EBX], DL             ; &chr 
		

        INVOKE incp, ppo                  ;更新下标
		ADD N, -1

NONE:   RET            ;空
qo      ENDP         

;打印队列
 qp     PROC C USES EAX EBX ECX EDX  pbuf:DWORD, ppi:DWORD, ppo: DWORD

		MOV ECX, N
		CMP ECX, 0
		JZ  NO

		PUSH ECX
		INVOKE printf, chr$(0ah,0dh,"当前队列内容为：")
		POP ECX

		MOV EDX, ppo               ;&po
GOON:   MOV EBX, pbuf              ;&buf
		LEA EBX, [EBX + EDX]
		MOV AL, BYTE PTR[EBX]         ;依次输出
  
		PUSH ECX
		PUSH EDX
		INVOKE printf, chr$("%c"), AL
		POP EDX
		POP  ECX

        INC EDX
        AND EDX ,0FH

		DEC ECX
		CMP ECX, 0
		JNZ GOON

        PUSH ECX
        MOV EDX, ppo
        MOV EBX, ppi
        INVOKE printf, chr$("队首下标为%d，队尾下标为%d,元素个数为%d", 0dh, 0ah), EDX, EBX, N
        POP  ECX
        JMP  EXIT

NO :   PUSH ECX
		MOV EDX, ppo
		MOV EBX, ppi
		INVOKE printf, chr$(0dh,0ah,"当前队列内容为：队首下标为%d，队尾下标为%d，元素个数为%d",0dh,0ah), EBX, EBX,N
		PUSH ECX
EXIT :  RET
 qp     ENDP
 

MAIN    PROC
		INVOKE printf, chr$("请选择：ESC 退出； - 从队列提取元素显示 + 打印当前队列；0 - 9A - Z进入队列，其他抛弃。", 0dh, 0ah)
INP:    INVOKE _getche
		CMP EAX, 1BH
		JZ  OVER
		CMP EAX, '-'
		JZ  FQO
		CMP EAX, '+'
		JZ  FQP
		CMP EAX, '0'
		JB  INP
		CMP EAX, '9'
		JBE FQI
		CMP EAX, 'A'
		JB INP
		CMP EAX, 'Z'
		JBE FQI
		JMP INP
FQI :   INVOKE qi,OFFSET buf,OFFSET pi,EAX 
		CMP EAX, 1
		JNZ  FUL
		JMP  INP

FUL:    INVOKE printf, chr$(0dh, 0ah, "full!", 0dh, 0ah)
		JMP INP
FQO:    INVOKE qo, OFFSET buf,OFFSET po, OFFSET chr
		CMP EAX, 1
		JNZ NON
		INVOKE printf, chr$("提取的元素为 %c", 0dh, 0ah), chr
		JMP INP

NON :   INVOKE printf, chr$(0dh, 0ah, "none", 0dh, 0ah)
		JMP INP

FQP :   INVOKE qp,OFFSET buf,pi,po
		JMP INP

OVER :  INVOKE	 ExitProcess, 0
  MAIN  ENDP
	    END MAIN



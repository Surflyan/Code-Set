INCLUDE  ASM32.INC

COUNT=100
SRCL	PROTO C :PTR BYTE,:DWORD
CRC		PROTO C :PTR BYTE,:DWORD,:PTR BYTE
.DATA												; 数据段定义，全局变量在这儿
		S	BYTE    COUNT DUP(?)
	CRCS	BYTE	0,0,0

.CODE		
	SRCL	PROC C USES EBX ECX ESI SSS:PTR BYTE,N:DWORD
			MOV		EBX,SSS
			MOV		ECX,N
			MOV		ESI,ECX
			DEC		ESI
			CLC
	L:		RCL		BYTE PTR [EBX+ESI],1
			DEC		ESI
			LOOP	L
			RET
	SRCL	ENDP

		
	CRC		PROC  C USES EBX ECX ESI EDI  SSS:PTR BYTE,N:DWORD,CC:PTR BYTE
			LOCAL	TS[200]:BYTE,CNT:DWORD
			MOV		ESI,SSS
			LEA		EDI,TS
			MOV		ECX,N
			CLD
			REP		MOVSB
			MOV		WORD PTR [EDI],0
			MOV		BYTE PTR [EDI+2],0

			MOV		ECX,N
			ADD		ECX,2
			MOV		CNT,ECX

			LEA		EBX,TS
			MOV		ECX,N
			SHL		ECX,3
		LL: TEST	BYTE PTR [EBX],80H
			JZ		LOV
			XOR		BYTE PTR [EBX],80H
			XOR		BYTE PTR [EBX+1],05H
	LOV:	PUSH	CNT
			PUSH	EBX
			CALL	SRCL
			ADD		ESP,8
			;INVOKE  SRCL EBX,CNT		;不能嵌套!!!!!
			LOOP	LL

			MOV		ESI,CC
			MOV		CX,[EBX]
			MOV		[ESI],CX		
			RET
	CRC		ENDP
										; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			INVOKE	printf, chr$("请输入1个字符串：")
			INVOKE	scanf,chr$("%s"),OFFSET S
			INVOKE	getchar
			INVOKE	strlen,OFFSET S
			
			INVOKE 	CRC,OFFSET S,EAX,OFFSET CRCS

        ;把CF位加到最后一个元素的最低位，实现整串循环左移
			MOV		CX,WORD PTR CRCS
			MOV		WORD PTR S[EAX],CX
			MOV		BYTE PTR S[EAX+2],0

			INVOKE	printf, chr$("CRC:%02X %02X",0dh,0ah),CRCS[0],CRCS[1]

			INVOKE	getchar
			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main

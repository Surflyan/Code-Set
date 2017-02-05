INCLUDE  ASM32.INC

COUNT=100
.DATA												; 数据段定义，全局变量在这儿
		V	DWORD	COUNT DUP(0)	
.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始

			MOV		ECX,COUNT
			CLD
			MOV		EAX,0FFH
			LEA		EDI,V
			REP		STOSD				;数组元素全部初始化为0FFH


			MOV		ECX,COUNT
			CLD
			MOV		EAX,1
			LEA		EDI,V
		L1:	STOSD						;数组初始化为1、2、……100
			INC		EAX
			LOOP	L1

			MOV		ECX,COUNT
			CLD
			MOV		EDX,0
			LEA		ESI,V
		L2:	LODSD						;取数组元素
			ADD		EDX,EAX
			LOOP	L2

			INVOKE	printf, chr$("数组元素累加和为：%d",0DH,0AH),EDX
			INVOKE	getchar
			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main

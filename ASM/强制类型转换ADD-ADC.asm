INCLUDE  ASM32.INC

.DATA												; 数据段定义，全局变量在这儿
		X	QWORD	123456789ABCDEF0H
		Y	QWORD	0FEDCBA9876543210H
		Z	QWORD	?
.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			MOV		EAX,DWORD PTR X
			MOV		EDX,DWORD PTR X+4
			ADD		EAX,DWORD PTR Y
			ADC		EDX,DWORD PTR Y+4
			MOV		DWORD PTR Z,EAX
			MOV		DWORD PTR Z+4,EDX

			INVOKE	printf, chr$("Z=X+Y 为：%llX",0DH,0AH),Z
			INVOKE	getchar

			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main


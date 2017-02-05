INCLUDE  ASM32.INC

COUNT=100
.DATA												; 数据段定义，全局变量在这儿
		S	BYTE    COUNT DUP(?)

.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			INVOKE	printf, chr$("请输入1个字符串：")
			INVOKE	scanf,chr$("%s"),OFFSET S
			INVOKE	getchar
			INVOKE	strlen,OFFSET S
			
			MOV		ECX,EAX
			LEA		EBX,S
			MOV		ESI,ECX
			DEC		ESI
			CLC
	L:		RCL		BYTE PTR [EBX+ESI],1
			DEC		ESI
			LOOP	L
			ADC     BYTE PTR [EBX+EAX-1],0         ;把CF位加到最后一个元素的最低位，实现整串循环左移


			INVOKE	printf, chr$("移位后为:%s",0dh,0ah),offset S

			INVOKE	getchar
			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main


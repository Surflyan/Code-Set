INCLUDE  ASM32.INC

COUNT=100
.DATA												; 数据段定义，全局变量在这儿
		S1	BYTE    COUNT DUP(0)
		S2  BYTE	COUNT DUP(0)
.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			INVOKE	printf, chr$("请输入1个字符串：")
			INVOKE	scanf,chr$("%s"),OFFSET S1
			INVOKE	getchar
			INVOKE	strlen,OFFSET S1

			MOV		ECX,EAX
			CLD
			LEA		ESI,S1
			LEA		EDI,S2
			REP		MOVSB
			MOVSB						;把字符串结尾的0也复制过去						
			
			INVOKE	printf, chr$("目标串内容为:%s",0dh,0ah),offset S2
			
			INVOKE	getchar
			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main



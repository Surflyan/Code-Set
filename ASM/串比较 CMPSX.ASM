INCLUDE  ASM32.INC

COUNT=100
.DATA												; 数据段定义，全局变量在这儿
		S1	BYTE	"张老三",0
		S2	BYTE	"张老四",0

.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			MOV		ECX,lengthof S1
			CLD
			LEA		ESI,S1
			LEA		EDI,S2
			REPZ	CMPSB
			JGE		DAYUL
			INVOKE	printf, chr$("%s < %s",0DH,0AH),OFFSET S1,OFFSET S2
			JMP		OVER
	DAYUL:	INVOKE	printf, chr$("%s >= %s",0DH,0AH),OFFSET S1,OFFSET S2

	OVER:	INVOKE	getchar
			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main
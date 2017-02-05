INCLUDE  ASM32.INC

.DATA												; 数据段定义，全局变量在这儿
		X	DWORD	?
		Y	DWORD	?
		Z	DWORD	?
.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			INVOKE	printf, chr$("请输入X、Y：")
			INVOKE	scanf, chr$("%d%d"),OFFSET X,OFFSET Y
			INVOKE	getchar

			MOV		EAX,X
			ADD		EAX,Y
			MOV		Z,EAX 

			INVOKE	printf, chr$("Z=X+Y 为：%d",0DH,0AH),EAX
			INVOKE	getchar

			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main


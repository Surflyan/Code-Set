INCLUDE  ASM32.INC

.DATA												; 数据段定义，全局变量在这儿
		S	DD	1,2,3,4,5,6,7,8,9,0
.CODE												; 代码段开始
	MAIN	PROC									; 函数 - 子程序开始
			;四大准备
			MOV		ECX,lengthof S
			CLD
			MOV		EAX,6			;要搜索的元素值==》累加器
			LEA		EDI,S
			REPNZ	SCASD			;比较不相等则继续比较下一元素
			JZ      FLL
			INVOKE	printf, chr$("没找到",0dh,0ah)
			JMP		OVER
	FLL:	SUB		EDI,OFFSET S			;搜索到的元素位置在当前EDI指向元素的上一个
			SHR		EDI,2					
			DEC		EDI
			INVOKE	printf, chr$("找到了，下标为:%d",0dh,0ah),EDI
			
	OVER:	INVOKE	getchar
			INVOKE	 ExitProcess,0 
	MAIN	ENDP											; 函数 - 子程序结束

			END       MAIN									; END 指示所有程序到此结束，第一条可执行语句位置为main



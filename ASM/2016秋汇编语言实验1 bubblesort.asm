; 2016只需完成2-3即可
; 注本文件有6个程序main1~~~main6，分别对应要完成的sort1~sort5实验
; main6是额外的demo，可以参考
; 通过修改本文件的最后一行的最后一个字母1 - 6，就可以选择运行相应的程序了。
; 这样只是方便同学们运行测试，在乐学网提交的时候应该是sort1~sort5.asm共5个源程序
.586
.MODEL flat, stdcall
.STACK 4096
option casemap : none

printf      PROTO C : dword, : vararg
scanf       PROTO C : dword, : vararg
getchar		PROTO C
ExitProcess	PROTO : DWORD

includelib msvcrt.lib		;VS 2015 加上目录

chr$ MACRO any_text:vararg
   LOCAL textname
   .data
   textname db any_text,0
   ALIGN 4
   .code
   EXITM <OFFSET textname>
ENDM

.DATA
  arrayi SDWORD 100 DUP(0)
  count  DWORD ?
.CODE
	main1     PROC
	getcnt:  INVOKE printf,chr$("请输入要排序的数组个数：")
			 INVOKE scanf,chr$("%d"),OFFSET count
			 INVOKE getchar
			 CMP	count,1
			 JBE	getcnt

			 INVOKE printf,chr$("请按顺序输入各个元素：")
			 LEA	ebx,arrayi
			 MOV	ecx,count
	getarray:PUSH	ECX
			 INVOKE scanf,chr$("%d"	 ),ebx		;ADDR [EBX]
			 POP	ECX
			 ADD	ebx,4
			 LOOP	getarray
		 	 INVOKE getchar

			 MOV	ecx,count
			 DEC	ecx
	L1:      PUSH	ecx
			 LEA	ebx,arrayi
	L2:      MOV	eax,[ebx]
			 CMP	[ebx+4],eax
			 JG		L3
			 XCHG	eax,[ebx+4]
			 MOV	[ebx],eax
	L3:      ADD	ebx,4
			 LOOP	L2
			 POP	ecx
			 LOOP	L1

			 INVOKE printf,chr$("冒泡排序之后的结果是：")
			 LEA	ebx,arrayi
			 MOV	ecx,count
	prtarray:PUSH	ECX
			 INVOKE printf,chr$("%8d"),dword ptr[ebx]
			 POP	ECX
			 ADD	ebx,4
			 LOOP	prtarray
			 INVOKE printf,chr$(0dh,0ah)

			 INVOKE getchar
			 INVOKE ExitProcess,0
	main1     ENDP

	main2     PROC
	getcnt:  INVOKE printf,chr$("请输入要排序的数组个数：")
			 INVOKE scanf,chr$("%d"),OFFSET count
			 INVOKE getchar
			 CMP	count,1
			 JBE	getcnt

			 INVOKE printf,chr$("请按顺序输入各个元素：")
			 LEA	ebx,arrayi
			 MOV	ESI,0
	getarray:INVOKE scanf,chr$("%d"), ADDR [ebx+esi*4]
			 INC	ESI
			 CMP	ESI,count
			 JL		getarray
			 INVOKE getchar

			 MOV	ecx,count
			 DEC	ecx
	L1:      PUSH	ecx
			 mov	esi,0
	L2:      MOV	eax,[ebx+esi*4]
			 CMP	[ebx+esi*4+4],eax
			 JG		L3
			 XCHG	eax,[ebx+esi*4+4]
			 MOV	[ebx+esi*4],eax
	L3:      INC	esi
			 LOOP	L2
			 POP	ecx
			 LOOP	L1

			 INVOKE printf,chr$("冒泡排序之后的结果是：")
			 LEA	ebx,arrayi
			 MOV	esi,0
	prtarray:INVOKE printf,chr$("%8d"),dword ptr[ebx+esi*4]
			 inc	esi
			 CMP	esi,count
			 JL		prtarray
			 INVOKE printf,chr$(0dh,0ah)

			 INVOKE getchar
			 INVOKE ExitProcess,0
	main2     ENDP

	main3    PROC
	getcnt:  INVOKE printf,chr$("请输入要排序的数组个数：")
			 INVOKE scanf,chr$("%d"),OFFSET count
			 INVOKE getchar
			 CMP	count,1
			 JBE	getcnt

			 INVOKE	printf,chr$("请按顺序输入各个元素：")
			 MOV	ESI,0
	getarray:INVOKE scanf,chr$("%d"), ADDR arrayi[esi * 4]
			 INC	ESI
			 CMP	ESI,count
			 JL		getarray
			 INVOKE getchar

			 MOV	ecx,count
			 DEC	ecx
	L1:      PUSH	ecx
			 mov	esi,0
	L2:      MOV	eax,arrayi[esi*4]
			 CMP	arrayi[esi*4+4],eax
			 JG		L3
			 XCHG	eax,arrayi[esi*4+4]
			 MOV	arrayi[esi*4],eax
	L3:      INC	esi
			 LOOP	L2
			 POP	ecx
			 LOOP	L1

			 INVOKE printf,chr$("冒泡排序之后的结果是：")
			 MOV	esi,0
	prtarray:INVOKE printf,chr$("%8d"), arrayi[esi*4]
			 inc	esi
			 CMP	esi,count
			 JL		prtarray
			 INVOKE printf,chr$(0dh,0ah)

			 INVOKE getchar
			 INVOKE ExitProcess,0
	main3     ENDP

	main4    PROC
	getcnt:  INVOKE printf,chr$("请输入要排序的数组个数：")
			 INVOKE scanf,chr$("%d"),OFFSET count
			 INVOKE getchar
			 CMP	count,1
			 JBE	getcnt

			 INVOKE	printf,chr$("请按顺序输入各个元素：")
			 MOV	ESI,0
	getarray:INVOKE scanf,chr$("%d"), ADDR arrayi[esi * 4]
			 INC	ESI
			 CMP	ESI,count
			 JL		getarray
			 INVOKE getchar

			 MOV	esi,count
			 DEC	esi
	L1 :	 MOV	edi,0
	L2:      MOV	eax,arrayi[edi*4]
			 CMP	arrayi[edi*4+4],eax
			 JG		L3
			 XCHG	eax,arrayi[edi*4+4]
			 MOV	arrayi[edi*4],eax
	L3:      INC	edi
			 CMP	edi,esi
			 JNZ	L2
			 DEC	ESI
			 JNZ	L1	 						 		

			 INVOKE printf,chr$("冒泡排序之后的结果是：")
			 MOV	esi,0
	prtarray:INVOKE printf,chr$("%8d"), arrayi[esi*4]
			 inc	esi
			 CMP	esi,count
			 JL		prtarray
			 INVOKE printf,chr$(0dh,0ah)

			 INVOKE getchar
			 INVOKE ExitProcess,0
	main4     ENDP


	main5    PROC
			.REPEAT
				INVOKE	printf,chr$("请输入要排序的数组元素个数(>1)：")
				INVOKE	scanf,chr$("%d"),OFFSET count
				INVOKE	getchar
			.UNTIL count > 1

			MOV	esi,0
			INVOKE printf,chr$("请按顺序输入各个元素：")
			.REPEAT
				INVOKE	scanf,chr$("%d"),ADDR arrayi[esi*4]
				INC		esi
			.UNTIL ESI==count
			INVOKE getchar

			MOV		esi,count
			DEC		esi
			.REPEAT
				MOV	edi,0
				.REPEAT
				     MOV	eax,arrayi[edi*4]
					 .IF eax > arrayi[edi*4+4]
						XCHG	eax, arrayi[edi*4+4]
						MOV		arrayi[edi*4],eax			;VS2015 编译出错误硬指令
						nop									;可解决
					 .ENDIF
				     INC	edi
				 .UNTIL  edi==esi
				 DEC	esi
			.UNTIL esi==0

			 INVOKE printf,chr$("冒泡排序之后的结果是：")
			 MOV	esi,0
			.REPEAT
				INVOKE	printf,chr$("%8d"), arrayi[esi*4]
				INC		esi
			.UNTIL esi==count
			 INVOKE printf,chr$(0dh,0ah)

			 INVOKE getchar
			 INVOKE ExitProcess,0
	main5    ENDP

	main6    PROC
			MOV	[ebx+4],eax
			MOV	arrayi[edi * 4 + 4],eax
			MOV [ebx + esi * 4 + 4],eax

			.REPEAT
				INVOKE	printf,chr$("请输入要排序的数组元素个数>1：")
				INVOKE	scanf,chr$("%d"),OFFSET count
				INVOKE	getchar
			.UNTIL count > 1

			LEA	ebx,arrayi
			MOV	esi,0
			INVOKE printf,chr$("请按顺序输入各个元素：")
			.REPEAT
				INVOKE	scanf,chr$("%d"),addr [ebx+esi*4]
				INC		esi
			.UNTIL ESI==count
			INVOKE getchar


			MOV		esi,count
			DEC		esi
			.REPEAT
				MOV	edi,0
				.REPEAT
				     MOV	eax,[ebx+edi*4]
					 .IF eax > sdword ptr [ebx+edi*4+4]
						XCHG	eax, [ebx+edi*4+4]
						MOV		[ebx+edi*4],eax			;VS2015 编译出错误硬指令
						nop								;可解决
					 .ENDIF
				     INC	edi
				 .UNTIL  edi==esi
				 DEC	esi
			.UNTIL esi==0

			 INVOKE printf,chr$("冒泡排序之后的结果是：",0dh,0ah)
			 MOV	esi,0
			.REPEAT
				INVOKE	printf,chr$("%8d"),dword ptr[ebx+esi*4]
				INC		esi
			.UNTIL esi==count

			 INVOKE getchar
			 INVOKE ExitProcess,0
	main6     ENDP

			END		main1
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 14 21:55:28 2015

@author: bhwl
"""



#求1000以内中3或5的倍数的自然数之和
sum=0
for i in range (1,1000):
    if i%3==0 or i%5==0:
        sum+=i
print sum


#2000000以内的所有素数的和
sum=0
t=[1]*2000000

for i in range (2,2000000):
   if t[i]==1:
       for q in range (i*2,2000000,i):#筛去质数的倍数
           t[q]=0
   if t[i]==1:
       sum+=i
print sum

#计算星期天
count=0
mon=[31,28,31,30,31,30,31,31,30,31,30,31]
wee=365%7
for y in range (1901,2001):   
    if y % 4==0  or y%400==0  and y% 100 !=0:
        mon[1]=29
    for x in mon:
        wee+=x
        if wee % 7== 1:
            count+=1
print count 

#循环素数
count=0
for i in range(2,1000000):
    n=1# 保留素数本身
    wei=len(str(i))
    if t[i]==1:
        for x in range(1,wei ):
            y=i%(10**x)*(10**(wei-x))+i/(10**x)
            if t[y]==1:
                n=n+1 #去掉重复计算的循环素数
        if n==wei:
             count=count+1
print count
  

        
                   
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
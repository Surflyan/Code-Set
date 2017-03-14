# -*- coding: utf-8 -*-
"""
Created on Fri Nov 06 16:43:34 2015

@author: bhwl
"""

def isbn(list1):
    num=list1.count('-') 
    if len(list1)!=13 or num!=3: #判断 输入字符个数是否满足及连字符是否为3个
        print "Invalid ISBN Format"
        return
    elif list1[1]!="-" or list1[11]!="-" : #判断连字符位置
        print "Invalid ISBN Format"
        return
    elif list1[4]!='-':
        print "Invalid ISBN Format"  
    else:
        pass
    list2='0123456789'         
    list3=list1.split("-") #去除连字符
    st=''.join(list3)   #将去除后剩余部分连起来 
    for i in range (0,9):
        if st[i] in list2:#判断剩s余部分是否为数字或x
            pass         
        else:
            print 'Invalid ISBN Format'
            return
  
    sum=0 
    for i in range (0,10):           
        if st[i]!="X" and st[i]!="x" : #若不是x则按规则相加
            sum+=int(st[i])*(10-i)
                
        else:
            sum+=10  #若为x则尾数取为10          
    if sum % 11==0:    #判断是否整除11
        print "Valid ISBN"
        return
    else:
        print "Invalid ISBN"
        return    
list1=[]
while True:
    ISBN=raw_input()
    
    if ISBN=="$$$": # 直到输入$$$终止
        break
    else:
        list1.append(ISBN)
for i in list1:  
    isbn(i)        


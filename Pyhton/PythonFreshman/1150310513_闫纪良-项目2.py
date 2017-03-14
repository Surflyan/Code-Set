# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 16:21:19 2015

@author: bhwl

"""

import sqlite3

# crate a database
conn = sqlite3.connect('STUDENT.db')

try:
    conn.execute('''CREATE TABLE  STUDENT
      (ID INT PRIMARY KEY          ,
       NAME             TEXT       ,
       CHINESE          INTEGER    ,
       MATH             INTEGER   ,
       ENGLISH          INTEGER    ,
       PHYSICAL         INTEGER    ,
       CHEMICAL         INTEGER    ,
       ALLGRADE         INTEGER          )''')

except:
    pass



conn.commit()
conn.close()


conn = sqlite3.connect('STUDENT.db')
cur=conn.cursor()

#Import the report card file
    
f=open('scores.csv')
try:
    for i in range(40):
        line= f.readline()
       
       
        s =line.split(',') 
        name=unicode(s[1])
        s7=int(s[2])+int(s[3])+int(s[4])+int(s[5])+int(s[6])

        
        conn = sqlite3.connect('STUDENT.db')
        cur=conn.cursor()
        
        cur.execute('INSERT INTO STUDENT  \
             VALUES(:a1,:a2,:a3,:a4,:a5,:a6,:a7 ,:a8)',{"a1":int(s[0]),"a2":name,"a3":int(s[2]),"a4":int(s[3]),"a5":int(s[4]),"a6":int(s[5]),"a7":int(s[6]),"a8":s7})
       # add grade to table   STUDENT
        conn.commit()
except:
    pass
cur.close()
conn.close()




def id_query():
    # query grade by student’s  id number

    def ok():
              
        conn=sqlite3.connect('STUDENT.db')
      
        num=int(en.get())
  
        cursor=conn.execute('SELECT * FROM STUDENT WHERE ID =%d'% num)
        
        root1=Tk()
        id_=Listbox(root1,height=5,width=50)
        for row in cursor :                      
                personal=row[:]            
                id_.insert(END,personal)    # output the grade queryed
        id_.pack() 
        id_.mainloop()
        conn.commit()
        cursor.close()
  
        conn.close()
        
    root=Tk()
    Label(root, text='输入要查找学生学号').pack()
             
    var0=StringVar()
   
    en=Entry(root,textvariable=var0)
    en.pack()
    # get  user input id number
    button=Button (root,text=" 确定 ",command=ok) 
    button.pack()
    root.title('学号查询')
    root.mainloop()
    
def name_query():
    #     # query grade by student’s  id number

    def ok():
               
        conn=sqlite3.connect('STUDENT.db')
      
        num=entry.get()   
        cursor=conn.execute('SELECT * FROM STUDENT WHERE NAME ="%s" '% num)
     
        root1=Tk()
        name=Listbox(root1,height=5,width=50)

        for row in cursor :                      
                personal=row[:]            
                name.insert(END,personal)
        name.pack()   
        conn.commit()
        cursor.close() 
        conn.close()
    root=Tk()
    label=Label(root, text='输入查找学生学号')
    label.pack()
             
    var=StringVar()
   
    entry=Entry(root,textvariable=var)
    entry.pack()    
    button=Button (root,text=" 确定 ",command=ok) 
    button.pack()
    root.title('姓名查询')
    root.mainloop()
   
def delete():
    # Delete the input student grade

    def deltable():
        
        import tkMessageBox
        tkMessageBox.showinfo("提示", "删除成功")

        name=entry.get()
            
        conn=sqlite3.connect('STUDENT.db')
        cur=conn.cursor()
          
        cur.execute('DELETE FROM STUDENT WHERE NAME= "%s"' % name)
        conn.commit()
        cur.close()
        conn.close()
        
 
  
    root=Tk()
    label=Label(root, text='输入要删除学生姓名')
    label.pack()
             
    var=StringVar()
   
    entry=Entry(root,textvariable=var)
    entry.pack()
        
   
    button=Button (root,text=" 确定 ",command=deltable) 

    button.pack()
    root.title('删除成绩')
    root.mainloop()
    
    
def add_student():           
    # add student grade

    def ok():
        
        import tkMessageBox
        tkMessageBox.showinfo("提示", "添加成功") 
        
        va1=int(e1.get())
        va2=e2.get()
        va3=int(e3.get())
        va4=int(e4.get())
        va5=int(e5.get())
        va6=int(e6.get())
        va7=int(e7.get())
        va8=va3+va4+va5+va6+va6+va7
        conn=sqlite3.connect('STUDENT.db')
        cur=conn.cursor()
        
        cur.execute('INSERT INTO STUDENT  \
                    VALUES(:a1,:a2,:a3,:a4,:a5,:a6,:a7 ,:a8)',{"a1":va1,"a2":va2,"a3":va3,"a4":va4,"a5":va5,"a6":va6,"a7":va7,"a8":va8})
        # add the sudent grade to the table
           
        conn.commit()
        conn.close() 
        

    root=Tk()
    var1=StringVar()
    Label(root,text="学号").pack()
    e1=Entry(root ,textvariable=var1 )
    e1.pack()
    var2=StringVar()
    Label(root,text="姓名").pack()
    e2=Entry(root ,textvariable=var2 )
    e2.pack()
    var3=StringVar()
    Label(root,text="语文").pack()
    e3=Entry(root ,textvariable=var3 )
    e3.pack()
    var4=StringVar()
    Label(root,text="数学").pack()
    e4=Entry(root ,textvariable=var4 )
    e4.pack()                                     # get student's garde 
    var5=StringVar()
    Label(root,text="英语").pack()
    e5=Entry(root ,textvariable=var5 )
    e5.pack()
    var6=StringVar()
    Label(root,text="物理").pack()
    e6=Entry(root ,textvariable=var6 )
    e6.pack()
    var7=StringVar()
    Label(root,text="化学").pack()
    e7=Entry(root ,textvariable=var7 )
    e7.pack()    

    button=Button(root,text="确认",command=ok)
    button.pack()
    root.title('添加成绩')
    root.mainloop()   
    
    
    
def allgrade_update():
    
        # Modify the students total grade after  some other subject grade be changed


        import tkMessageBox
        tkMessageBox.showinfo("提示", "修改成功")
        
        conn=sqlite3.connect('STUDENT.db')
        curs=conn.cursor()

        curs.execute('SELECT CHINESE,MATH,ENGLISH,PHYSICAL,CHEMICAL FROM STUDENT WHERE NAME="%s"'%name1)
        
        for grade in curs:
            
            new_allgrade=sum(grade)  # To calculate total grade
            
        curs.execute('UPDATE STUDENT SET ALLGRADE=? WHERE NAME=?',(new_allgrade,name1))   
        conn.commit()
        curs.close()
        conn.close()
  
       
def update():
     # modify student grade
    def ok():
    
        conn=sqlite3.connect('STUDENT.db')
        curs=conn.cursor()
        global name1
        name1=e.get()      
        sub=e1.get()
     
        sc=int(e2.get())
     
        if sub==u'语文':
            curs.execute(('UPDATE  STUDENT  SET  CHINESE=:CHI WHERE NAME=:name_' ) ,{"CHI":sc,"name_":name1})
                     
        if sub==u'数学':          
            curs.execute(('UPDATE  STUDENT  SET  MATH=:CHI WHERE NAME=:name_' ) , {"CHI":sc,"name_":name1})
        if sub==u'英语':
            curs.execute(('UPDATE  STUDENT  SET  ENGLISH=:CHI WHERE NAME=:name_' ) ,{"CHI":sc,"name_":name1})
        if sub==u'物理':
            curs.execute(('UPDATE  STUDENT  SET  PHYSICAL=:CHI WHERE NAME=:name_' ) ,{"CHI":sc,"name_":name1})
        if sub==u'化学':
            curs.execute(('UPDATE  STUDENT  SET  CHEMICAL=:CHI WHERE NAME=:name_' ) ,{"CHI":sc,"name_":name1})
        conn.commit()
        curs.close()
        conn.close()
        
        allgrade_update()  # Call the function to modify total grade
 
    root=Tk()
    var1=StringVar()
    Label(root,text="输入姓名").pack()
    e=Entry(root ,textvariable=var1 )
    e.pack() 
    
    var2=StringVar()
    Label(root,text="修改科目").pack()
    e1=Entry(root ,textvariable=var2 )
    e1.pack()
    
    var3=StringVar()
    Label(root,text="修改分数").pack()
    e2=Entry(root ,textvariable=var3 )
    e2.pack()
 
    button=Button(root,text="确认",command=ok)
    button.pack()
    root.title('修改成绩')
    root.mainloop()
    

    
        
def query(subject):
    
     # query the only one subject grade
    conn=sqlite3.connect('STUDENT.db')
    if subject=='CHINESE':        
        cursor=conn.execute('SELECT ID,NAME, CHINESE FROM STUDENT order by -CHINESE')
    if subject=="MATH":
        cursor=conn.execute('SELECT ID,NAME, MATH FROM STUDENT order by -MATH')
    if subject=="ENGLISH":
        cursor=conn.execute('SELECT ID,NAME, ENGLISH FROM STUDENT order by -ENGLISH')
    if subject=="PHYSICAL":
        cursor=conn.execute('SELECT ID,NAME, PHYSICAL FROM STUDENT order by -PHYSICAL')
    if subject=="CHEMICAL":
        cursor=conn.execute('SELECT ID,NAME, CHEMICAL FROM STUDENT order by -CHEMICAL')
    if subject=="ALLGRADE":
        cursor=conn.execute('SELECT * FROM STUDENT order by -ALLGRADE')
    if subject=="TOTALGRADE":
        cursor=conn.execute('SELECT ID,NAME, ALLGRADE FROM STUDENT order by -ALLGRADE')
    root1=Tk()
    lb=Listbox(root1,height=20,width=50)
    for row in cursor:
        grade=row[:]
        lb.insert(END,grade)
    lb.pack()
    root1.title('成绩如下')
    root1.mainloop()
    cursor.close()
    conn.close
    

    
def level_query(subject):
     #  According to the band score query student grade
    
    def  judge() :   
        conn=sqlite3.connect('STUDENT.db')
        
        qu=e.get()
        qu=qu.split(' ')      # Get the user want the  grade band
        min_=min(int(qu[0]),int(qu[-1]))
        max_=max(int(qu[0]),int(qu[-1]))
        
        if subject=='ALLGRADE':            
            cursor=conn.execute('SELECT * FROM STUDENT  WHERE ALLGRADE>? AND ALLGRADE < ? order by -ALLGRADE',(min_,max_))
        if subject=='CHINESE':
            cursor=conn.execute('SELECT ID,NAME,CHINESE FROM STUDENT  WHERE CHINESE>? AND CHINESE < ? order by -CHINESE',(min_,max_))
        if subject=='MATH':
            cursor=conn.execute('SELECT ID,NAME,MATH FROM STUDENT  WHERE MATH>? AND MATH < ? order by -MATH',(min_,max_))
        if subject=='ENGLISH':
            cursor=conn.execute('SELECT ID,NAME,ENGLISH FROM STUDENT  WHERE ENGLISH>? AND ENGLISH < ? order by -ENGLISH',(min_,max_))
        if subject=='PHYSICAL':
            cursor=conn.execute('SELECT ID,NAME,PHYSICAL FROM STUDENT  WHERE PHYSICAL>? AND PHYSICAL < ? order by -PHYSICAL',(min_,max_))
        if subject=='CHEMICAL':
            cursor=conn.execute('SELECT ID,NAME,CHEMICAL FROM STUDENT  WHERE CHEMICAL>? AND CHEMICAL< ? order by -CHEMICAL',(min_,max_))
                
        root1=Tk()
        lb=Listbox(root1,height=20,width=50)
        for row in cursor:
            grade=row[:]
            lb.insert(END,grade)
  
        lb.pack()
        root1.title('成绩如下')
        root1.mainloop()
        cursor.close()
        conn.close

    root=Tk()
    var1=StringVar()
    Label(root,text="输入查询分数范围并用空格隔开").pack()
    e=Entry(root ,textvariable=var1,width=10)
    e.pack()
    qu=e.get()
    qu=qu.split(' ')
    button=Button(root,text="确认",command=judge)
    button.pack()
    root.title('分数段查询')
    root.mainloop() 


from  Tkinter import *


    
root=Tk()

canvas=Canvas(root,bg='Chartreuse')


# Create query menu

menubar=Menu(root)
filemenu=Menu(menubar,tearoff=0)
filemenu.add_command(label='全部成绩',command=lambda:query('ALLGRADE'))
filemenu.add_command(label='语文',command=lambda:query('CHINESE'))  
filemenu.add_command(label='数学',command=lambda:query('MATH'))
filemenu.add_command(label='英语',command=lambda:query('ENGLISH'))
filemenu.add_command(label='物理',command=lambda:query('PHYSICAL'))
filemenu.add_command(label='化学',command=lambda:query('CHEMICAL'))
filemenu.add_command(label='总成绩',command=lambda:query('TOTALGRADE'))
menubar.add_cascade(label='查询成绩',menu=filemenu)


levelmenu=Menu(menubar,tearoff=0)
levelmenu.add_command(label='总成绩',command=lambda :level_query('ALLGRADE'))
levelmenu.add_command(label='语文',command=lambda :level_query('CHINESE'))
levelmenu.add_command(label='数学',command=lambda :level_query('MATH'))
levelmenu.add_command(label='英语',command=lambda :level_query('ENGLISH'))
levelmenu.add_command(label='物理',command=lambda :level_query('PHYSICAL'))
levelmenu.add_command(label='化学',command=lambda :level_query('CHEMICAL'))
menubar.add_cascade(label='分段成绩查询',menu=levelmenu)

siglemenu=Menu(menubar,tearoff=0)
siglemenu.add_command (label='学号查询',command=id_query)
siglemenu.add_command (label='姓名查询',command=name_query)


menubar.add_cascade(label='单个学生成绩查询',menu=siglemenu)

addmenu=Menu(menubar,tearoff=0)
addmenu.add_command (label='添加学生成绩',command=add_student)
addmenu.add_command (label='删除学生成绩',command=delete)
addmenu.add_command (label='修改学生成绩',command=update)

menubar.add_cascade(label='学生成绩操作',menu=addmenu)

canvas.pack()

root.config(menu=menubar)
root.title('学生成绩管理系统')
root.mainloop()
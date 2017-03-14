# -*- coding: utf-8 -*-
"""
Created on Sun Nov 29 15:02:32 2015

@author: bhwl
"""

lis1=[]
count=0
while count<3:    
    grades=raw_input()
    lis1.append(grades) 
    
    if grades=='======':
        count+=1     

#  create a list contain all input,until  ===== appear three times        
       


lis1=';'.join(lis1)
a,b,c=lis1.split(';======;',2 )

all_grade=a.split(';')
sub_query=tuple(b.split(';'))
stu_id=c.split(';')[:-1]

# List 1 processing into corresponding to three query input


a_grades=[]
s=0
for i in range (len(all_grade)):
    s=0
    lis2=all_grade[i].split(',')
    
    for j in lis2[2:]:
        s+=int(j)
    lis2.append(str(s))
    lis2.append(str(s/5.0))
    a_grades.append(lis2)
    
# create new list contain id,name,grade,total score and average score




for i in range (len(a_grades)-1):
     max_=i
     for j in range(i+1,len(a_grades)):
        if int(a_grades[j][7])>int(a_grades[max_][7]):
             max_=j
        elif int(a_grades[j][7])==int(a_grades[max_][7]):
                
            for k in range(5,0,-1):             
                if int(a_grades[j][7-k])>int(a_grades[max_][7-k]):
                    max_=j
                    break
                elif int(a_grades[j][7-k])<int(a_grades[max_][7-k]):
                    break
                else :       # If tootal grade is equal, ordered by other subjects scores
                    pass
#  sort total score by  selection sort 
                    
     a_grades.insert(i,a_grades.pop(max_))
for l in range(len(a_grades)):
   
    output=str(l+1)+' ' +' '.join(map(str,a_grades[l]))   
    print output
    a_grades[l].append(str(l+1))

print '******'
#  Output all students all grades in turn





def bubblesort(numb):
    
   #  it used to sort students grade by their subject score in turn
    
    for j in range(len(numb)-1,0,-1):
        for i in range(j):
            if int(numb[i][b])<int(numb[i+1][b]):
                numb[i],numb[i+1] = numb[i+1],numb[i]
              
              #   sort by query subject
            elif int(numb[i][b])==int(numb[i+1][b]):
                
                if int(numb[i][7])<int(numb[i+1][7]):
                    numb[i],numb[i+1] = numb[i+1],numb[i]
                    break
              #  sort by total score
                elif int(numb[i][7])==int(numb[i+1][7]):
                              
                    for k in range(2,7):
               
              # sort by chinese ,math ...in turn 
                        if int(numb[i][k])<int(numb[i+1][k]):    
                            numb[i],numb[i+1] = numb[i+1],numb[i]
                            break
                        elif  int(numb[i][k])>int(numb[i+1][k]):
                            break
                        else:
                            pass
    for n in range(len(numb)):
          a_grade=str(n+1)+' '+numb[n][0]+' '+numb[n][1]+' '+numb[n][b]
          print a_grade
    # According to the query subject result output  students ranking
            
subs=('语文','数学','英语','物理','化学')
for sub in sub_query:
    b=subs.index(sub)+2
    bubblesort(a_grades)
print '******'
#  Establish a selection function





def bi_search(numb,query):
   #  bisection method  query students grades
        
    low=0
    up = len(numb)-1
   
    while low<=up:
        mid =(low+up)/2

        if numb[mid][0]<query:
            low = mid+1
        elif numb[mid][0]==query :
            return mid
        else:
            up= mid-1    
    return -1
  
for a_id in stu_id: 
   #  output  every query
    
   a_grades.sort(key=lambda x:x[0],reverse=False)   
   dex = bi_search(a_grades,a_id)  
   
   out=' '.join(map(str,a_grades[dex]))
   print out
print'******'


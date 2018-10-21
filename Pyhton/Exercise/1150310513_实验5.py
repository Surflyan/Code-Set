# -*- coding: utf-8 -*-
"""
Created on Mon Nov 16 22:22:49 2015

@author: bhwl
"""

#1 建立索引

dict1={}
for i in range(0,100):
    paragraph=raw_input()
    sentence=paragraph.split()
   
    for word in sentence:      
        if word in dict1:  
            dict1[word].append(i+1) 
        else :
            dict1[word]=[i+1]
# if word in dict,append it's line,if it's a new word ,add itself and line to dict


dict2=sorted(dict1.iteritems(),key=lambda d:d[0],reverse=False)

# Aligning key according to the words the first letters


# 打印索引

for i in range (len(dict2)):
    tup_word=dict2[i]     #Traverse each word
    
    lis_lines=set(tup_word[1]) 
   
    output =tup_word[0]+':'+' '+', '.join(map(str,lis_lines) )
#  print  word as required
     
    print output
  


# 检索

lis=[]

while True:
    query=raw_input()
    if len(query)==0:
        break
    else:
        query=query.split()
        lis=query

         
        
    
    if len(lis) ==1:       
        word_=lis[0]      
        if dict1.has_key(word_):
      
                list1=list(set(dict1[word_]))
                re_line=', '.join(map(str,list1))
                print re_line
        else:
            print 'None'
# if input one word ,print it's line
            

    else:  
        if lis[0]=='AND:' :   # start with AND：
            condition=True
            condition2=True
            output=set()
            
            for word_ in lis[1:]:
                if dict1.has_key(word_)==False:
                    condition2=False
                    break
            # if there are words not in dict, print None   
            
                elif dict1.has_key(word_):  
                    list2=set(dict1[word_])
                   
                    
                    lines=list2
                   
                    
                    if condition:  #  ensure get first word's line
                        output=lines
                        condition=False
                    else:
                        output=output & lines
                        
                        
               # print words' line & 
            output=list(output)
            
           
            output=', '.join(map(str,output))         
           
            if len(output)==0 or  condition2==False :           
                print 'None'
            else:
                print output
                
                
               
        elif lis[0]=='OR:':  # start with or:
        
               output=set( )
               for word_ in lis[1:]:
                    if dict1.has_key(word_):
                       list2=set(dict1[word_])
                       
                       liens=list2
                       
                       output=output|lines  #  qet union set
              
               output=list(output)
               output=', '.join(map(str,output))
               if len(output)==0:  
                   print 'None'
               else:
                   print output  
               
               
                   
           
        else:     # if not start with AND: or OR:,  Defaults to AND:
            condition=True
            condition2=True
            output=set()
            
            for word_ in lis:
                if dict1.has_key(word_)==False:
                    condition2=False
                    break
                
                elif dict1.has_key(word_):  
                    list2=set(dict1[word_])
                   
                    lines=list2
                    
                    if condition:
                        output=lines
                        condition=False
                    else:
                        output=output & lines
                
            output=list(output)
            output=', '.join(map(str,output))
            if len(output)==0 or  condition2==False :           
                print 'None'
            else:
                print output
                
        
       








    
    








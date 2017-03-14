# -*- coding: utf-8 -*-
"""
Created on Sun Nov 22 23:11:12 2015

@author: bhwl
"""

def en_decrypt(words):
    
    ''' It is used to encrypt and decrypt a paragraph
     '''  
    
    key=int(raw_input('please input your key:\n'))
    if key>0:
        key=key%26
    if key<0:
        key=-(-key%26)
     #   make key no more than 26 
        
    lis=[]
    for i in range(len(words)):

      if ord(words[i])>128:
          print 'your message contain liieagel string'    
            
          break
     #  If the input contains the string not belong to ASCII, prompting the user 
        
      elif  ord('A')<=ord(words[i])<ord('Z'):
      
     
          letters_ascii=ord(words[i])
      #  if the input is alphabet, shift it 
          
          global condition
          if condition :              
              letters_ascii=letters_ascii+key
          else:
              letters_ascii=letters_ascii-key
      #  According to users' need  ,choose encrypt or decrypt
              
          if letters_ascii<ord('A'):
                letters_ascii=26+letters_ascii
          if letters_ascii>ord('Z'):
                letters_ascii=letters_ascii-26
        
     #  Ensure circulation won't more than 26 letters
        
          secret_letters=chr(letters_ascii)
          lis.append(secret_letters)
          output=''.join(lis)
      else:
          lis.append(words[i])
      
       
    output=''.join(lis) 
    print output
   #  output the word encrypted


 
def cracking_code(words):
    
    ''' It is used to crack a Caesar password encryption of a paragraph
     '''
         
    k=int(raw_input('how many the most likely answer do you want? input number\n' ))
       
    dict1={}
    if k>len(words):
        print 'you input  the secrect word  too little to meet your k, please Reduce your k value'
        
    else:
    
        for i in range(len(words)):
    
            if words[i].isalpha():
   
       
               if words[i] in dict1:
                   dict1[words[i]]=dict1[words[i]]+1
               if words[i] not in dict1:
                   dict1[words[i]]=1
                   
            else:            # Set up the dict for letters
                pass
            lis=sorted(dict1.iteritems(),key=lambda d:d[1],reverse=True)
  
        a=lis[:k]
     
     #   Find  k letters appear most times

        for i in range (0,k):
           letter=a[i][0]
      
           key=ord('E')-ord(letter)
           
      #  calculate k
        
           lis2=[]
           for i in range(len(words)):

                if ord(words[i])>128:
                    print 'your message contain liieagel string'    
            
                    break
        
                elif  ord('A')<=ord(words[i])<ord('Z'):
            
                    letters_ascii=ord(words[i])
                    letters_ascii=letters_ascii-key
      
                    if letters_ascii<ord('A'):
                        letters_ascii=26+letters_ascii
                    if letters_ascii>ord('Z'):
                        letters_ascii=letters_ascii-26
          
                    secret_letters=chr(letters_ascii)
                    lis2.append(secret_letters)
                    output=''.join(lis2)
                else:
                    lis2.append(words[i])
     
       
           output=''.join(lis2) 
           print output
      #  According to the decryption method to deal with




#  The following mainly user interaction

print 'Hello, I\'m glad to severs for you!\nA represent encrypt\nB represent decrypt\nC represent cracking the code\n'
second=False
while True: 
    if second== True:
        get=raw_input('Do you want to continue play Caesar password,input YES or NO\n').upper()
        if get=='NO':
            break
    #   Users choose to continue or exit
            
    else:
        second=True
        
    condition=True
    
    choice=raw_input('Please choose which one you want to  experience , input the letters it corresponds\n').upper()
    
    if choice=='A':
        condition=True
        words=raw_input('please input the words you want to encrypt:\n').upper()  
        en_decrypt(words)
    elif choice=='B':
        condition=False
        words=raw_input('please input the words you want to decode:\n').upper()
        en_decrypt(words)
    elif choice=='C':
        words=raw_input('please input the secret words you want to crack :\n').upper()
        cracking_code(words)
    else:   
        print 'Please enter the correct option'
   #   The user to select which operation to perform
      
     
       
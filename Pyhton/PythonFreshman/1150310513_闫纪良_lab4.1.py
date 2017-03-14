# -*- coding: utf-8 -*-
"""
Created on Thu Nov 12 17:37:14 2015

@author: bhwl
"""
def piglatin (word):        
    word=word.lower()
    vowel='aeiou'
    vowel1='aeiouy' 
   
    if word[0] in vowel:
        new_word= word +'hay'
        print new_word,
        return 
      #  the first letter is vowel  , + hay
   
    elif word[0:2]=='qu':
        new_word=word[2:]+'qu'+'ay'
        print new_word,
        return
    #  Two letters for qu  change to the end  + ay      
        
    elif len(word)==1:
         new_word =word+'ay'
         print new_word,
         return
    #  only onr letter, +ay
    else:  
        for i in range (1,len(word)):
            if word[i] in vowel1 :
      
                word=word[i:] + word[:i]
                break
               # Continuous Consonants in a word , move to the end    
        new_word=word+'ay'
        print new_word,
        #  others, +'ay'
    

put=raw_input()  
word=put.split()
for i in word:   
    piglatin(i)
# Divided into words to judge 

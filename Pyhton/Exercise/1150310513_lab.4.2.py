# -*- coding: utf-8 -*-
"""
Created on Thu Nov 12 17:51:58 2015

@author: bhwl
"""
def piglatin(word):
    import re
    word=word.lower()

    a= re.match('[aeiou]',word)  #   the first letter is vowel
    b=re.match('[qu]',word)   #  the first two letter for qu
    c=re.search('[aeiouy]',word)  #  until find vowel
    
    if a:
        new_word=word+'hay'
        print new_word,
        return
    # the first letter is vowel  , + hay
        
    if b:
        new_word=word[2:]+word[:2]+'ay'
        print new_word,
        return
     # the first two letter for qu  ,move to the lst + ay
    if c:
         vowel=c.group()  
         # return to the vowel finded
         
         num=word.find(vowel)
         
         #  The location of the vowels 
         
         new_word=word[num:]+word[:num]+'ay'
         # Continuous Consonants in a word , move to the end,+ay
         print new_word,
         return
         
    else:
        new_word=word+'ay'
        print new_word,
        return
put=raw_input()
word=put.split()
for i in  word:
    piglatin(i)



    

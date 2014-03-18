import sys
import os
from time import time
from operator import itemgetter
import re
path = '/Users/renren/OpenCodeNLP/PCI/source/'
 
def getWordCount(fileName = 'blogData1.txt'): 
     count = {};
     wordList = {};
     # print fileName
     filePath = path + fileName
     fileString = open(filePath).read();
     wordlist = re.split(r'[^a-zA-Z\']',fileString)
     for word in wordlist:
         if count.has_key(word):
             count[word] = count[word] + 1
         else:
             if len(word):
                 count[word] = 1
     return count
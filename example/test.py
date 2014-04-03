#!/usr/bin/python  
#-*-coding:utf-8-*
import sys
import os
import re
import string

sys.path.append('/Users/renren/OpenCodeNLP/PCI/source');
sys.path.append('/Users/renren/OpenCodeNLP/PCI/lib');

from recommendations import critics
from calculateSimilarity import *
from recommendation import*

flag = 0;
file = open('txt.data').read();
fileOut = open('txt1.out','w')
mouth = [0,31,59,90,120,151,182,212,243,273,304,335]
search = re.compile('月|日')
count = 0;
for row in file.split():
    if flag : 
        for word in row.split(','):
             count %= 4
             time = 0;
             idx = 0;
             if count == 3:
                 for item in search.split(word):
                     if len(item)==0:break;
                     if idx == 0:
                        # time += mouth[item]
                         time += mouth[int(item)]
                     else :
                         # time += item;
                         time += int(item);
                     idx += 1;
                 fileOut.write(str(time));
             else :
                fileOut.write(word);
             fileOut.write(' ')
             count += 1
        fileOut.write('\n');
    flag = 1

import sys
import os
import re

inFile = open('txt1.out').read()
testData = open('testData.txt','w');
ln = 0;
for row in inFile.split('\n'):
    if ln == 0:
        ln += 1;
        continue;
    word = row.split();
    if len(word) <=0 :break;
    if len(word[0]) <= 0:break;
    if int(word[2]) == 1:
        if len(word[3]) <=0: continue;
        if int(word[3]) > 196:
            testData.write(word[0]);
            testData.write(" ");
            testData.write(word[1])
            testData.write("\n")
    
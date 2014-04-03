import sys
import os
import re
import string
    
    
inputFile = open('txt1.out').read();
outputFile = open('txt.output','w');
flag = 0;
frontName = 0;
frontPruduct = 0;
frontDate = 0
tmpWord = {}
scoreCount = 0;
count = 0
maxLen = 0;
countRow = 0;
countr = 0
Len =0
flag = 0
for row in inputFile.split('\n'):
    idx=0;
    word = row.split(' ');
    if len(word[0]) == 0 :
        break;
    if frontName == int(word[0])  and frontProduct == int(word[1]):
                if int(word[2]) == 1:
                    scoreCount += 4;
                if int(word[2]) == 3:
                    scoreCount += 3;
                if int(word[2]) == 2:
                    scoreCount += 2
                if int(word[2]) == 0:
                    scoreCount += 0;
                if scoreCount > 3:
                    countr += 1
                Len += int(word[3])
                count += 1;
    else :
        if scoreCount != 0:
                outputFile.write(str(frontName))
                outputFile.write(' ')
                outputFile.write(str(frontProduct))
                outputFile.write(' ')
                outputFile.write(str(scoreCount))
                outputFile.write(' ');
                outputFile.write(str(Len/count))
                outputFile.write('\n')
        frontName = int(word[0])
        frontDate = int(word[3]) 
        frontProduct = int(word[1])
        if int(word[2]) == 1:
            scoreCount = 4;
        if int(word[2]) == 3:
            scoreCount = 3;
        if int(word[2]) == 2:
            scoreCount = 2
        if int(word[2]) == 0:
            scoreCount = 0;
        Len = int(word[3]);
        count = 1 ;
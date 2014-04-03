import sys
import os
import re

rw =0;
infile = open('userBuy.txt').read()
vist = {};
for row in infile.split('\n'):
    word = row.split(' ');
    count = 0;
    rw2 = 0;
    rw +=1
    for row2 in infile.split('\n'):
        word2 = row2.split(' ')
        rw2 +=1
        if int(word[0]) == int(word2[0]) :
            if int(word[1]) == int(word2[1]):
                if vist.has_key(rw2): break;
                count += 1;
        if count >=2:
            vist[rw] = 1;
            print word[0]+' '+word[1];
            break;
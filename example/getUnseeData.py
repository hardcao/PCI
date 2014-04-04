import sys
import os
import re

infile = open('txt1.out').read();
for row in infile.split('\n'):
    word = row.split(' ')
    if len(word[0]) == 0 : break;
    if int(word[2]) == 0:continue;
    print row;
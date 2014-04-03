import sys
import io
import re

infile = open('txt1.out').read();
outfile = open('userBuy.out','w');

userBuy = {};
for row in infile.split('\n'):
    word = row.split(' ');
    if len(word[0]) == 0: break;
    if int(word[2]) == 1 :
        if userBuy.has_key(word[0]):
            cmd = userBuy[word[0]]
            if cmd.has_key(word[1]):
                userBuy[word[0]][word[1]] += 1;
            else:
                userBuy[word[0]][word[1]] = 1;
        else:
            cmd = {};
            cmd[word[1]] = 1;
            userBuy[word[0]] = cmd;
        
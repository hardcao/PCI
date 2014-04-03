import sys
import io
import re

infile = open('txt1.out').read();

userBuy = {};
for row in infile.split('\n'):
    word = row.split(' ');
    if len(word[0]) == 0: break;
    if int(word[3]) > 196 :continue;
    if int(word[2]) == 1 :
        ansStr = word[0] + ' ' + word[1] + ' ' + word[2] + ' ' + word[3];
        # print word[0]
#         print ' '
#         print word[1]
#         print ' '
#         print word[2]
#         print ''
#         print word[3]
#         print '\n'
        print ansStr
        
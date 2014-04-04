import sys
import os
import math

pfile = open('pfile.txt').read()
bfile = open('bfile.txt').read();

hfile = open('hfile.txt','w')

for prow in pfile.split('\n'):
    pword = prow.split()
    ppn = int(pword[0])
    pcd = int(pword[1])
    flg = 1;
    for brow in bfile.split('\n'):
        bword = brow.split();
        bpn = int(bword[0])
        bcd = int(bword[1])
        if flg == 0: break;
        if ppn == bpn:
            if pcd == bcd:
                hfile.write(bword[0])
                hfile.write(' ')
                hfile.write(bword[1])
                hfile.write('\n')
                flg = 0;
#!/usr/bin/env python

import random

#for i in range(1,5):
    #with open('input/matrix'+str(i)+'.txt','w') as f:
        #f.write(str(i*5)+'\n')
        #s = ''
        #for j in range(1,5*i+2):
            #s += str(random.randint(1,1000))+' '
        #f.write(s+'\n')

alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
print len(alpha)

first = [5,10,20,40,80]
second = [4,8,16,32,64]

#for i in first:
for i in second:
    with open('input/lcs-25-'+str(i)+'.txt','w') as f:
        buff = ''
        buff += '25 ' + str(i) +'\n';
        for j in range(0,25):
            buff += alpha[random.randint(0,25)] + ' '
        buff += '\n'
        for j in range(0,i):
            buff += alpha[random.randint(0,25)] + ' '
        buff += '\n'
        f.write(buff)



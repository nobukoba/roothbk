#!/usr/bin/python3

import sys
import re

#file = open('zebra.f', 'r')
input = sys.stdin
lines = input.readlines()
pattern1 = '^[\*cC\s]*[dD][aA][tT][aA]\s*\w*\s*/'
pattern2  = '\'[^\']*\''
for line in lines:
    result1 = re.findall(pattern1, line)
    result2 = re.finditer(pattern2, line)
    if (len(list(result1))):
        print (line[0:len(result1[0])].lower(),end='')
        print (line[len(result1[0]):],end='')
    elif (len(list(result2))): 
        spnt = 0
        for match in re.finditer(pattern2, line):
            line = line[:match.start()] + '"' + line[match.start()+1:]
            line = line[:match.end()-1] + '"' + line[match.end():]
            print (line[spnt:match.start()].lower(),end='')
            print (line[match.start():match.end()],end='')
            spnt = match.end()
        print (line[spnt:].lower(),end='')
    else:
            print (line.lower(),end='')
    

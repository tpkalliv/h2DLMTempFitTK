import sys
import os


filelist = sys.argv[1];

# Using readlines()
file = open(filelist, 'r')
Lines = file.readlines()
  
count = 0
# Strips the newline character
for line in Lines:
    count += 1
    com = "python3 LMTempFitFigs2.py {}".format(line.strip())
    print("command", com)
    os.system(com)
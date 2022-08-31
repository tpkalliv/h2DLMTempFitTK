import sys
import os
# one can do it with the following in the command line but we are here to do it in python
# ls 2.output_LMfits/*.root > LMfits.list
# cat LMfits.list | awk '{com=sprintf("python3 LMTempFitFigs2.py %s",$1); print(com)}' | sh
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
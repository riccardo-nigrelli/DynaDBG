#!/usr/bin/python3

import os
import re
import sys

def merge(path, count):
  
  files = sorted([files for files in os.listdir(path) if files.endswith('.txt')])
  if count > len(files): exit(0)

  end = 0
  sep = ['\t', '\n']
  for file in files:
    if end < count:
      with open(f"{path}/{file}") as f: lines = f.readlines()
      with open(f"{path}/union.txt", 'a') as fout: fout.write(''.join(list([f"{line.split(sep[0])[0]}{sep[1]}" for line in lines])))
    
    end += 1

if __name__ == "__main__":
  merge(sys.argv[1], int(sys.argv[2]))
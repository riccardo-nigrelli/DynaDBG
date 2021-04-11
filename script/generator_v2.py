import os
import random

files = [f'genome-pt_{str(i).zfill(4)}' for i in range(0, 5120)]

samples = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
subSamples = [int(i * 0.25) for i in samples]

basePath = './split-5120'

def mergeFile(name, array):
  with open(f'{folderPath}/{name}-{sample}.txt', 'wb') as output:
    for _file in array:
      with open(f'{basePath}/files/{_file}.txt', 'rb') as _input:
        output.write(_input.read())


for sample, subSample in zip(samples, subSamples): 
  union = random.sample(files, sample)  
  newKmer = random.sample(list(set(files) - set(union)), subSample)
  existingKmer = random.sample(union, subSample)
  
  if subSample == 1:
    mixKmer = random.sample(union, 1)
    mixKmer += random.sample(list(set(union) - set(mixKmer)), 1)
  else:
    mixKmer = random.sample(union, int(subSample / 2))
    mixKmer += random.sample(list(set(union) - set(mixKmer)), int(subSample / 2))
  
  folderPath = f'{basePath}/experiment-{sample}'
  if not os.path.exists(folderPath):
    os.makedirs(folderPath)
  
  mergeFile('union', union)
  mergeFile('new-kmer', newKmer)
  mergeFile('existing-kmer', existingKmer)
  mergeFile('mix-kmer', mixKmer)
  
  print(f'union-{sample}.txt => {union}')
  print(f'new-kmer-{sample}.txt => {newKmer}')
  print(f'existing-kmer-{sample}.txt => {existingKmer}')
  print(f'mix-kmer-{sample}.txt => {mixKmer}')
  print('\n')


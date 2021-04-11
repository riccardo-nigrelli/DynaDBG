#!/usr/bin/python3

import sys, os, re, json
from functools import reduce
import matplotlib.pyplot as plt

FOLDERS = ['union', 'new-kmer', 'existing-kmer', 'mix-kmer']
SUB_FOLDERS = [ 2**i for i in range(2, 13) ]
DIMENSION = json.load(open('./inputs_dimension.json'))

def analizer(base, cond, type):
  result = {}
  for folder in FOLDERS:
    partial = []
    for sub in SUB_FOLDERS:
      times, memory = ([], [])
      path = f'{base}/{folder}/{sub}'
      if type == True:
        for file in [f for f in os.listdir(path) if bool(re.search(fr'\b{cond}\b', f))]:
          _json = json.load(open(f'{path}/{file}'))
          times.append(_json['benchmarks'][0]['real_time'])

        partial.append(reduce(lambda x, y : x + y, times) / len(times))
      else:
        for file in [f for f in os.listdir(path) if bool(re.search(fr'\b{cond}\b', f))]:
          reader = open(f'{path}/{file}')
          content = reader.readlines()
          memory.append(float(content[9].strip().split(': ')[1]))

        partial.append(reduce(lambda x, y : x + y, memory) / len(memory))
    result[folder] = partial

  return result

if __name__ == '__main__':
  base = 'release' if sys.argv[1] == '1' else 'debug'

  STOP_TIMER_RESULT_GBENCH = analizer(base, 'notimer.json', True) # Sono inclusi i tempi di I/O su file
  STOP_TIMER_RESULT_MEMORY = analizer(base, 'notimer.time', False)

  TIMER_RESULT_GBENCH = analizer(base, 'timer.json', True) # Sono esclusi i tempi di I/O su file
  TIMER_RESULT_MEMORY = analizer(base, 'timer.time', False)

  fig, axs = plt.subplots(2, 2)
  fig.tight_layout(h_pad=4)
  for folder, name in zip(FOLDERS, ['Creation', 'Add new kmer', 'Add existing kmer', 'Add mix kmer']):
    axs[0][0].plot(DIMENSION[folder], STOP_TIMER_RESULT_GBENCH[folder], label=name)
    axs[0][1].plot(DIMENSION[folder], TIMER_RESULT_GBENCH[folder], label=name)

  for folder, name in zip(FOLDERS, ['Creation', 'Add new kmer', 'Add existing kmer', 'Add mix kmer']):
    axs[1][0].plot(DIMENSION[folder], STOP_TIMER_RESULT_MEMORY[folder], label=name)
    axs[1][1].plot(DIMENSION[folder], TIMER_RESULT_MEMORY[folder], label=name)

  axs[0][0].set_title('Operation - Total time')
  axs[0][1].set_title('Operation - DS time')
  axs[1][0].set_title('Operation - Total time')
  axs[1][1].set_title('Operation - DS time')

  axs[0][0].set_ylabel('Time [ms]')
  axs[0][0].set_xlabel('Dimension [MB]')
  axs[0][0].set_yscale('log')
  axs[0][0].set_xscale('log')
  axs[0][0].legend(loc=4)

  axs[0][1].set_ylabel('Time [ms]')
  axs[0][1].set_xlabel('Dimension [MB]')
  axs[0][1].set_yscale('log')
  axs[0][1].set_xscale('log')
  axs[0][1].legend(loc=4)

  axs[1][0].set_ylabel('Maximum resident set size [KByte]')
  axs[1][0].set_xlabel('Dimension [MB]')
  axs[1][0].set_yscale('log')
  axs[1][0].set_xscale('log')
  axs[1][0].legend(loc=4)

  axs[1][1].set_ylabel('Maximum resident set size [KByte]')
  axs[1][1].set_xlabel('Dimension [MB]')
  axs[1][1].set_yscale('log')
  axs[1][1].set_xscale('log')
  axs[1][1].legend(loc=4)

  plt.show()
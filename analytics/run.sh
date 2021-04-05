#!/bin/bash

function run_benchmark() {
  mkdir -p $1 && cd $1
  for k in {2..12}; do
    pow=$((2**$k))
    union=$3-$pow/sort-union-$pow.txt

    mkdir -p $pow && cd $pow
    echo Subset of dimension $pow
    for i in {1..10}; do
      echo "Iteration #$i"
      if [ $2 == 0 ]
      then
        echo Considering $union
        \\time -v -o $1-$i.time ./../../../../build/benchmark/Benchmark_Genome_Create $union --benchmark_out=$1-$i.json
      else
        add=$3-$pow/sort-$1-$pow.txt
        echo Considering $union and $add
        \\time -v -o $1-$i.time ./../../../../build/benchmark/Benchmark_Genome_Add $union $add --benchmark_out=$1-$i.json
      fi
    done
    cd ..
  done
  cd ..
}

if [ $1 == 0 ]
then
  mkdir -p release && cd release
  run_benchmark "union" $1 "/data/kmc-genome/split-5120/experiment"
elif [ $1 == 1 ] 
then
  mkdir -p release && cd release
  run_benchmark "new-kmer" $1 "/data/kmc-genome/split-5120/experiment"
  run_benchmark "existing-kmer" $1 "/data/kmc-genome/split-5120/experiment"
  run_benchmark "mix-kmer" $1 "/data/kmc-genome/split-5120/experiment"
else
  echo "Wrong input"
  exit 2
fi

exit 0
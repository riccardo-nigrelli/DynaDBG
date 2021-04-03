#!/bin/bash

function run_benchmark() {
  echo "Benchmar on $1..."
  mkdir $1 && cd $1
  for k in {2..12}; do # dimension of subset
    mkdir $((2**$k)) && cd $((2**$k))
    echo "Analizing $1-$((2**$k)) file..."
    for i in {1..10}; do
      echo "Iteration #$i..."
      echo "\\time -v -o '$1-$((2**$k)).time' ./benchmark/$2 $((2**$k)) --benchmark_out='$1-$((2**$k)).json'"
    done
    cd ..
  done
  echo "Benchmark ending..."
  cd ..
}

mkdir release && cd release
run_benchmark "union" Benchmark_Genome_Create
run_benchmark "new-kmer" Benchmark_Genome_New
run_benchmark "existing-kmer" Benchmark_Genome_Existing
run_benchmark "mix-kmer" Benchmark_Genome_Mix

exit 0
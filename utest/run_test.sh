#!	/bin/bash

mkdir -p results
./tests/parser > results/parser.txt

for f in results/*.txt
	do
		./read_tester_output.sh $f
	done

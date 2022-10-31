#!	/bin/bash

mkdir -p results
./tests/lexer > results/lexer.txt
./tests/parser > results/parser.txt
./tests/expander > results/expander.txt

for f in results/*.txt
	do
		./read_tester_output.sh $f
	done

#!/bin/sh

FILES="*.tsp"
ALGS=( h )

for f in $FILES
do
	for a in $ALGS
	do
	 	../main $a $f 5 5 > "solutions/$a.$f.out"
		echo "solutions/$a.$f.out is done"
	done
done

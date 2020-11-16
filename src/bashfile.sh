#! /bin/bash
echo "n_thread, elapsed_time"

for i in {1 2 3 4 5 6 7 8}
do
	for j in {1 2 3 4 5}
	do
		make clean -s
		cTime=$(/usr/bin/time -f "%e" make -j $i -s 2>&1 | tail  -n 1)
		echo "$i,$cTime"
	done
done
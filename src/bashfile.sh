#! /bin/bash
echo "n_thread, elapsed_time"

for i in {1 2 3 4 5 6 7 8}
do
	for j in {1 2 3 4 5}
	do
		TIME1=$(date +%s%3N)
		{
			make run PROD=$i CONS=$i PHILO=$i
		} &> /dev/null
		TIME2=$(date +%s%3N)
		DURATION=$(($TIME2 - $TIME1))
		echo "$i threads : $j try $(($DURATION/1000)) seconds and $(($DURATION%1000)) milliseconds"
	done
done
make clean
echo "finiiiiii"
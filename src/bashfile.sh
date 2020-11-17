#! /bin/bash
echo "n_thread, elapsed_time"

for i in {1 2 3 4 5 6 7 8}
do
	for j in {1 2 3 4 5}
	do
		SECONDS=0
		{
			make run PROD=$i CONS=$i PHILO=$i
		} &> /dev/null
		DURATION=$SECONDS
		echo "$i threads : $j try $(($DURATION/60)) minutes and $(($DURATION%60)) seconds"
	done
done
make clean
echo "finiiiiii"
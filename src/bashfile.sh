#! /bin/bash
{
	gcc src/Philosophers.c -o Philo -lpthread
} &> /dev/null
for i in {1 2 3 4 5 6 7 8}
do
	for j in {1 2 3 4 5}
	do
		TIME1=$(date +%s%3N)
		{
			./Philo $i
		} &> /dev/null
		TIME2=$(date +%s%3N)
		DURATION=$(($TIME2 - $TIME1))
		echo "$i threads : $j try $(($DURATION/1000)) seconds and $(($DURATION%1000)) milliseconds"
	done
done
rm -f Philo

{
	gcc src/prodCons.c -o Prod -lpthread
} &> /dev/null
for i in {1 2 3 4 5 6 7 8}
do
	for j in {1 2 3 4 5}
	do
		TIME1=$(date +%s%3N)
		{
			
			./Prod $i $i
		} &> /dev/null
		TIME2=$(date +%s%3N)
		DURATION=$(($TIME2 - $TIME1))
		echo "$i threads : $j try $(($DURATION/1000)) seconds and $(($DURATION%1000)) milliseconds"
	done
done
rm -f Prod

{
	gcc src/lecteurEcrivains.c -o Lect -lpthread
} &> /dev/null
for i in {1 2 3 4 5 6 7 8}
do
	for j in {1 2 3 4 5}
	do
		TIME1=$(date +%s%3N)
		{
			./Lect $i $i
		} &> /dev/null
		TIME2=$(date +%s%3N)
		DURATION=$(($TIME2 - $TIME1))
		echo "$i threads : $j try $(($DURATION/1000)) seconds and $(($DURATION%1000)) milliseconds"
	done
done
rm -f Lect

echo "finiiiiii"
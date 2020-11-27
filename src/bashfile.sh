#! /bin/bash
'''
echo "n_threads,time" > philo.csv
{
	gcc src/Philosophers.c -o Philo -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..15}
	do
		#TIME1=$(date +%s%3N)
		{	
			echo -n "$i," >>philo.csv
			/usr/bin/time -ao philo.csv -f %e ./Philo $i
		} &> /dev/null
		#TIME2=$(date +%s%3N)
		#DURATION=$(($TIME2 - $TIME1))
		#echo "$i threads : $j try $(($DURATION/1000)) seconds and $(($DURATION%1000)) milliseconds"
	done
done
rm -f Philo

echo "n_threads,time" > prodCons.csv
{
	gcc src/prodCons.c -o Prod -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>prodCons.csv
			/usr/bin/time -ao prodCons.csv -f %e ./Prod $(($i/2)) $((($i +1)/2))
		} &> /dev/null
	done
done
rm -f Prod

echo "n_threads,time" > lectEcr.csv
{
	gcc src/lecteurEcrivains.c -o Lect -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>lectEcr.csv
			/usr/bin/time -ao lectEcr.csv -f %e ./Lect $((($i +1)/2)) $(($i/2))
		} &> /dev/null
	done
done
rm -f Lect
'''
echo "n_threads,time" > testAndSet.csv
{
	gcc src/test_and_set.c src/TestASM.c -o TaS -lpthread
} &> /dev/null
for i in {1..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>testAndSet.csv
			/usr/bin/time -ao testAndSet.csv -f %e ./TaS $((($i +1)/2)) $(($i/2))
		} &> /dev/null
	done
done
rm -f TaS

echo "finiiiiii"
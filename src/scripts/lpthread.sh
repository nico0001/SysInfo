#! /bin/bash
echo "n_threads,time" > philo.csv
{
	gcc src/lpthread/Philosophers.c -o Philo -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..15}
	do
		{	
			echo -n "$i," >>philo.csv
			/usr/bin/time -ao philo.csv -f %e ./Philo $i
		} &> /dev/null
	done
done
rm -f Philo

echo "n_threads,time" > prodCons.csv
{
	gcc src/lpthread/prodCons.c -o Prod -lpthread
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
	gcc src/lpthread/lecteurEcrivains.c -o Lect -lpthread
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
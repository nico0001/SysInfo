#! /bin/bash
echo "n_threads,time" > philoTaTaS.csv
{
	gcc src/TaTaS/Philosophers.c -o Philo -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..15}
	do
		{	
			echo -n "$i," >>philoTaTaS.csv
			/usr/bin/time -ao philoTaTaS.csv -f %e ./Philo $i
		} &> /dev/null
	done
done
rm -f Philo

echo "n_threads,time" > prodConsTaTaS.csv
{
	gcc src/TaTaS/prodCons.c -o Prod -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>prodConsTaTaS.csv
			/usr/bin/time -ao prodConsTaTaS.csv -f %e ./Prod $(($i/2)) $((($i +1)/2))
		} &> /dev/null
	done
done
rm -f Prod

echo "n_threads,time" > lectEcrTaTaS.csv
{
	gcc src/TaTaS/lecteurEcrivains.c -o Lect -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>lectEcrTaTaS.csv
			/usr/bin/time -ao lectEcrTaTaS.csv -f %e ./Lect $((($i +1)/2)) $(($i/2))
		} &> /dev/null
	done
done
rm -f Lect
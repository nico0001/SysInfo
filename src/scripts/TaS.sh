#! /bin/bash
echo "n_threads,time" > philoTaS.csv
{
	gcc src/TaS/Philosophers.c -o Philo -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..15}
	do
		{	
			echo -n "$i," >>philoTaS.csv
			/usr/bin/time -ao philoTaS.csv -f %e ./Philo $i
		} &> /dev/null
	done
done
rm -f Philo

echo "n_threads,time" > prodConsTaS.csv
{
	gcc src/TaS/prodCons.c -o Prod -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>prodConsTaS.csv
			/usr/bin/time -ao prodConsTaS.csv -f %e ./Prod $(($i/2)) $((($i +1)/2))
		} &> /dev/null
	done
done
rm -f Prod

echo "n_threads,time" > lectEcrTaS.csv
{
	gcc src/TaS/lecteurEcrivains.c -o Lect -lpthread
} &> /dev/null
for i in {2..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>lectEcrTaS.csv
			/usr/bin/time -ao lectEcrTaS.csv -f %e ./Lect $((($i +1)/2)) $(($i/2))
		} &> /dev/null
	done
done
rm -f Lect
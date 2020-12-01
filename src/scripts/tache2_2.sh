#! /bin/bash

#cat /proc/cpuinfo | grep processor | wc -l

echo "n_threads,time" > testAndSet.csv
{
	gcc src/TaS/test_and_set.c src/TaS/PerfTS.c -o TaS -lpthread
} &> /dev/null
for i in {1..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>testAndSet.csv
			/usr/bin/time -ao testAndSet.csv -f %e ./TaS $i
		} &> /dev/null
	done
done
rm -f TaS

echo "n_threads,time" > testAndTestAndSet.csv
{
	gcc src/TaTaS/tts.c src/TaTaS/PerfTTS.c -o TaTaS -lpthread
} &> /dev/null
for i in {1..8}
do
	for j in {1..5}
	do
		{
			echo -n "$i," >>testAndTestAndSet.csv
			/usr/bin/time -ao testAndTestAndSet.csv -f %e ./TaTaS $i
		} &> /dev/null
	done
done
rm -f TaTaS
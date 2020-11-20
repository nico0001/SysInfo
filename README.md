# SysInfo
gcc src/Philosophers.c -o Philo -lpthread
./Philo n

gcc src/lecteurEcrivains.c -o lect -lpthread
./lect n m

gcc src/prodCons.c -o prod -lpthread
./prod n m

n et m sont les nombres des threads qu'on veut

./src/bashfile.sh
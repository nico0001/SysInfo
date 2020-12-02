# SysInfo - Projet 1
- Pour tout exécuter : 
./src/scripts/all.sh

- Pour executer les 3 programmes en utilisant les sémaphores et mutex POSIX:
./src/scripts/lpthread.sh

- Pour executer les 3 programmes en utilisant le mutex de test-and-set:
./src/scripts/TaS.sh

- Pour executer les 3 programmes en utilisant le mutex de test-and-test-and-set:
./src/scripts/TaTaS.sh

- Pour executer un test pour les mutex test-and-set et test-and-test-and-set:
./src/scripts/tache2_2.sh

Dans le fichier python appelé problemes.py, 
il y a un programme pour afficher les trois plots des 3 problèmes.

Dans le fichier mutex.py, il y a le programme pour afficher le plot pour
test-and-set et test-and-test-and-set.


```
Projet
│   README.md
|   Les CSV et PNG des performances
│
└───src
│   │   graphs.py       #Génère les graphes liés aux problèmes
│   │   graphs2_2.py    #Génère le graphe de performance des verrous
│   │
│   └───scripts         #Scripts bash pour lancer les fichiers compilés
│   |   │   all.sh    #Lance l'ensemble des scripts ci-dessous
│   |   │   lpthread.sh
│   |   │   TaS.sh     #test and set
│   |   │   TaTaS.sh
│   |   │   tache2_2.sh        #tache 2.2: test des verrous
|   |
│   └───lpthread        #Problèmes implémentés avec les mutex/sémaphores de la librairie lpthread
│   |   │   Philosophers.c
│   |   │   prodCons.c
│   |   │   lecteurEcrivains.c
│   |
│   └───TaS    #Problèmes implémentés nos mutex/sémaphores implémentés avec la logique "test and set"
│   |   │   test_and_set.c
│   |   │   Philosophers.c
│   |   ...
│   |
│   └───TaTaS   #Problèmes implémentés nos mutex/sémaphores implémentés avec la logique "test and test and set"
│   |   ...
|   |
│   └───graphes   #les fichiers python pour plot les performances
        ...

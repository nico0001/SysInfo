import matplotlib.pyplot as plt
import numpy as np
import pandas

TaSData = pandas.read_csv('testAndSet.csv')["time"]
TaTaSData = pandas.read_csv('testAndTestAndSet.csv')["time"]

TaSAverages = []
stdTaS = []
for i in range(0,len(TaSData),5) :
	n = TaSData[i: i+5]
	TaSAverages.append(np.mean(n))
	stdTaS.append(np.std(n))

TaTaSAverages = []
stdTaTaS = []
for i in range(0,len(TaTaSData),5) :
	n = TaTaSData[i: i+5]
	TaTaSAverages.append(np.mean(n))
	stdTaTaS.append(np.std(n))

plt.xlabel('Nombre des threads')
plt.ylabel("Temps moyen d'exécution")
plt.title("Temps d'exécution en fonction du nombre des threads")
plt.errorbar(range(1,len(TaSData)//5+1),TaSAverages, yerr=stdTaS, color = 'r', linestyle="--")
plt.errorbar(range(1,len(TaTaSData)//5+1),TaTaSAverages, yerr=stdTaTaS, color = 'b', linestyle="--")
plt.axis(ymin=0)
plt.legend(["TestAndSet","TestAndTestAndSet"])
plt.savefig("TaS.png")
plt.show()
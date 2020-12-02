import matplotlib.pyplot as plt
import numpy as np
import pandas

philoData = pandas.read_csv('philo.csv')["time"]
prodConsData = pandas.read_csv('prodCons.csv')["time"]
lectEcrvData = pandas.read_csv('lectEcr.csv')["time"]
TaSData = pandas.read_csv('testAndSet.csv')["time"]
TaTaSData = pandas.read_csv('testAndTestAndSet.csv')["time"]

philoAverages = []
stdPhilo = []
for i in range(0,len(philoData),15) :
	n = philoData[i: i+15]
	philoAverages.append(np.mean(n))
	stdPhilo.append(np.std(n))

plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(2,len(philoData)//15+2),philoAverages, yerr=stdPhilo)
plt.axis(ymin=0)
plt.savefig("Philo.png")
plt.show()

prodAverages = []
stdProd = []
for i in range(0,len(prodConsData),5) :
	n = prodConsData[i: i+5]
	prodAverages.append(np.mean(n))
	stdProd.append(np.std(n))

plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(2,len(prodConsData)//5+2),prodAverages, yerr=stdProd)
plt.axis(ymin=0)
plt.savefig("Prod.png")
plt.show()

lectAverages = []
stdLect = []
for i in range(0,len(lectEcrvData),5) :
	n = lectEcrvData[i: i+5]
	lectAverages.append(np.mean(n))
	stdLect.append(np.std(n))

plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(2,len(lectEcrvData)//5+2),lectAverages, yerr = stdLect)
plt.axis(ymin=0)
plt.savefig("Lect.png")
plt.show()

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

plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(1,len(TaSData)//5+1),TaSAverages, yerr=stdTaS, color = 'r', linestyle="--")
plt.errorbar(range(1,len(TaTaSData)//5+1),TaTaSAverages, yerr=stdTaTaS, color = 'b', linestyle="--")
plt.axis(ymin=0)
plt.legend(["TestAndSet","TestAndTestAndSet"])
plt.savefig("TaS.png")
plt.show()
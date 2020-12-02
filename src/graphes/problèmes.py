import matplotlib.pyplot as plt
import numpy as np
import pandas

philoData = pandas.read_csv('philo.csv')["time"]
philoTaSData = pandas.read_csv('philoTaS.csv')["time"]
philoTaTaSData = pandas.read_csv('philoTaTaS.csv')["time"]
prodConsData = pandas.read_csv('prodCons.csv')["time"]
prodConsTaSData = pandas.read_csv('prodConsTaS.csv')["time"]
prodConsTaTaSData = pandas.read_csv('prodConsTaTaS.csv')["time"]
lectEcrvData = pandas.read_csv('lectEcr.csv')["time"]
lectEcrvTaSData = pandas.read_csv('lectEcrTaS.csv')["time"]
lectEcrvTaTaSData = pandas.read_csv('lectEcrTaTaS.csv')["time"]


philoAverages = []
stdPhilo = []
for i in range(0,len(philoData),15) :
	n = philoData[i: i+15]
	philoAverages.append(np.mean(n))
	stdPhilo.append(np.std(n))
'''
philoTaSAverages = []
stdPhiloTaS = []
for i in range(0,len(philoTaSData),15) :
	n = philoTaSData[i: i+15]
	philoTaSAverages.append(np.mean(n))
	stdPhiloTaS.append(np.std(n))

philoTaTaSAverages = []
stdPhiloTaTaS = []
for i in range(0,len(philoTaTaSData),15) :
	n = philoTaTaSData[i: i+15]
	philoTaTaSAverages.append(np.mean(n))
	stdPhiloTaTaS.append(np.std(n))
'''
plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(2,len(philoData)//15+2),philoAverages, yerr=stdPhilo)
#plt.errorbar(range(2,len(philoTaSData)//15+2),philoTaSAverages, yerr=stdPhiloTaS, color = 'r')
#plt.errorbar(range(2,len(philoTaTaSData)//15+2),philoTaTaSAverages, yerr=stdPhiloTaTaS, color = 'g')
plt.axis(ymin=0)
plt.savefig("Philo.png")
plt.show()

prodAverages = []
stdProd = []
for i in range(0,len(prodConsData),5) :
	n = prodConsData[i: i+5]
	prodAverages.append(np.mean(n))
	stdProd.append(np.std(n))

prodTaSAverages = []
stdProdTaS = []
for i in range(0,len(prodConsTaSData),5) :
	n = prodConsTaSData[i: i+5]
	prodTaSAverages.append(np.mean(n))
	stdProdTaS.append(np.std(n))

prodTaTaSAverages = []
stdProdTaTaS = []
for i in range(0,len(prodConsTaTaSData),5) :
	n = prodConsTaTaSData[i: i+5]
	prodTaTaSAverages.append(np.mean(n))
	stdProdTaTaS.append(np.std(n))

plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(2,len(prodConsData)//5+2),prodAverages, yerr=stdProd)
plt.errorbar(range(2,len(prodConsTaSData)//5+2),prodTaSAverages, yerr=stdProdTaS, color = 'r')
plt.errorbar(range(2,len(prodConsTaTaSData)//5+2),prodTaTaSAverages, yerr=stdProdTaTaS, color = 'g')
plt.axis(ymin=0)
plt.savefig("Prod.png")
plt.show()

lectAverages = []
stdLect = []
for i in range(0,len(lectEcrvData),5) :
	n = lectEcrvData[i: i+5]
	lectAverages.append(np.mean(n))
	stdLect.append(np.std(n))

lectTaSAverages = []
stdLectTaS = []
for i in range(0,len(lectEcrvTaSData),5) :
	n = lectEcrvTaSData[i: i+5]
	lectTaSAverages.append(np.mean(n))
	stdLectTaS.append(np.std(n))

lectTaTaSAverages = []
stdLectTaTaS = []
for i in range(0,len(lectEcrvTaTaSData),5) :
	n = lectEcrvTaTaSData[i: i+5]
	lectTaTaSAverages.append(np.mean(n))
	stdLectTaTaS.append(np.std(n))

plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title("Temps d'execution avec différentes coeurs")
plt.errorbar(range(2,len(lectEcrvData)//5+2),lectAverages, yerr = stdLect)
plt.errorbar(range(2,len(lectEcrvTaSData)//5+2),lectTaSAverages, yerr = stdLectTaS, color = 'r')
plt.errorbar(range(2,len(lectEcrvTaTaSData)//5+2),lectTaTaSAverages, yerr = stdLectTaTaS, color = 'g')
plt.axis(ymin=0)
plt.savefig("Lect.png")
plt.show()
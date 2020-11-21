import matplotlib.pyplot as plt
import numpy as np
import pandas

philoData = pandas.read_csv('philo.csv')["time"]
prodConsData = pandas.read_csv('prodCons.csv')["time"]
lectEcrvData = pandas.read_csv('lectEcr.csv')["time"]

philoAverages = []
stdPhilo = []
for i in range(0,len(philoData),15) :
	n = philoData[i: i+15]
	philoAverages.append(np.mean(n))
stdPhilo = np.std(n)
print(philoAverages)
print(stdPhilo)
plt.subplot(311)
plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title('Temps avec différentes coeurs')
#plt.plot(range(2,len(philoData)//15+2),philoAverages)
plt.errorbar(range(2,len(philoData)//15+2),philoAverages, yerr='stdPhilo')


prodAverages = []
for i in range(0,len(prodConsData),5) :
	n = prodConsData[i: i+5]
	prodAverages.append(np.mean(n))
plt.subplot(312)
plt.plot(range(2,len(prodConsData)//5+2),prodAverages)

lectAverages = []
for i in range(0,len(lectEcrvData),5) :
	n = lectEcrvData[i: i+5]
	lectAverages.append(np.mean(n))
plt.subplot(313)
plt.plot(range(2,len(lectEcrvData)//5+2),lectAverages)

plt.show()


'''i=0
averages = []

while i < 35:
	n = data['elapsed_time'][i: i+5]
	averages.append(np.mean(n) / 5)
	i = i+5

print(averages)
figure = plt.figure()
 


plt.savefig("exo.png")
plt.show()
plt.close()
'''
import matplotlib.pyplot as plt
import numpy as np
import pandas

philosData = pandas.read_csv('philos.csv')
prodConsData = pandas.read_csv('prodCons.csv')
lectEcrvData = pandas.read_csv('lectEcr.csv')

i=0
averages = []

while i < 40:
	n = data['elapsed_time'][i: i+5]
	averages.append(np.mean(n) / 5)
	i = i+5

print(averages)
figure = plt.figure()
 
M = [1,2,3,4,5,6,7,8]
 
plt.plot(M, averages, color="blue", linewidth=1.0)
plt.xlabel('Nombre des coeurs')
plt.ylabel("Temps moyenne d'execution")
plt.title('Temps avec différentes coeurs')

plt.savefig("exo.png")
plt.show()
plt.close()
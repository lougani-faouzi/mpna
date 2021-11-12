import matplotlib.pyplot as plt 
	
#x : represente les valeurs de la taille de la matrice A
#y : represente le temps d'execution (en ms) de la fonction arnoldi 
x = [4, 8, 12, 16, 20, 24, 28, 32]
y1  = [8, 9, 10, 10.2, 10.60, 11.02,12.01,14]

y2 = [5,6.5, 7, 8.30, 8.60, 9.02,9.41,10.2]
plt.xlabel("taille de la matrice A")
plt.ylabel("temps d exec (ms)")

plt.plot(x,y1)
plt.plot(x,y2)
plt.show()


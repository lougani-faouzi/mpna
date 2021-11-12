import matplotlib.pyplot as plt 
	
#x : represente les valeurs de la taille de la matrice A
#y : represente le temps d'execution (en ms) de la fonction arnoldi 
x = [4, 8, 12, 16, 20, 24, 28, 32]
y = [2.69e-02, 4.70e-02, 8.01e-02, 1.27e01, 2.00e-01, 3.23e-01,3.85e-01,5.09e-01]

plt.xlabel("taille de la matrice A")
plt.ylabel("temps d exec (ms)")
plt.plot(x,y)
plt.show()


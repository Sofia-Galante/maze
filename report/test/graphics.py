import matplotlib.pyplot as plt
import pandas as pd

t1 = pd.read_csv('test1.csv', names = ['x', 'seq', 'par'], sep=';')
t2 = pd.read_csv('test2.csv', names = ['x', 'seq', 'par'], sep=';')
t3 = pd.read_csv('test3.csv', names = ['x', 'seq', 'par'], sep=';')
t3_2 = pd.read_csv('test3_2.csv', names = ['x', 'par1', 'par2', 'par3'], sep=';')

plt.plot(t1["x"], t1["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t1["x"], t1["par"], color = 'red', label = 'parallelo')
plt.xlabel("dimensioni labirinto (numero di celle)")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("test1.png")
plt.show()


plt.plot(t2["x"], t2["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t2["x"], t2["par"], color = 'red', label = 'parallelo')
plt.xlabel("numero di particelle")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("test2.png")
plt.show()


plt.plot(t3["x"], t3["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t3["x"], t3["par"], color = 'red', label = 'parallelo')
plt.xlabel("numero di thread")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("test3.png")
plt.show()

plt.plot(t3_2["x"], t3_2["par1"], color = 'blue', label = 'threads = 10')
plt.plot(t3_2["x"], t3_2["par2"], color = 'red', label = 'threads = 100')
plt.plot(t3_2["x"], t3_2["par3"], color = 'green', label = 'threads = 500')
plt.xlabel("numero di particelle")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("test3_2.png")
plt.show()

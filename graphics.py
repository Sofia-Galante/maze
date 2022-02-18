import matplotlib.pyplot as plt
import pandas as pd

t1 = pd.read_csv('test1.csv', names = ['x', 'seq', 'par'], sep=';')
t2 = pd.read_csv('test2.csv', names = ['x', 'seq', 'par'], sep=';')
t3 = pd.read_csv('test3.csv', names = ['x', 'seq', 'par'], sep=';')

plt.plot(t1["x"], t1["seq"], color = 'blue', label = 'sequential')
plt.plot(t1["x"], t1["par"], color = 'red', label = 'parallel')
plt.legend(loc="upper left")
plt.savefig("test1.png")
plt.show()

plt.plot(t2["x"], t2["seq"], color = 'blue', label = 'sequential')
plt.plot(t2["x"], t2["par"], color = 'red', label = 'parallel')
plt.legend(loc="upper left")
plt.savefig("test2.png")
plt.show()


plt.plot(t3["x"], t3["seq"], color = 'blue', label = 'sequential')
plt.plot(t3["x"], t3["par"], color = 'red', label = 'parallel')
plt.legend(loc="upper left")
plt.savefig("test3.png")
plt.show()

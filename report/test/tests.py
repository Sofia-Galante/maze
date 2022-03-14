import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

n = 10

t1 = list()
t1_2 = list()
t2 = list()
t3 = list()
t3_2 = list()
t4 = list()

os.makedirs("dimTest", exist_ok=True)
os.makedirs("dimTestV2", exist_ok=True)
os.makedirs("particlesTest", exist_ok=True)
os.makedirs("threadsTest", exist_ok=True)
os.makedirs("threadsTestV2", exist_ok=True)
os.makedirs("lockTest", exist_ok=True)

for i in range(n):
    filename = f"test_{i+1}.csv"
    os.system(f"maze {filename}")
    t1.append(pd.read_csv(f"dimTest/{filename}", names = ['x', 'seq', 'par'], sep=';'))
    t1_2.append(pd.read_csv(f"dimTestV2/{filename}", names = ['x', 'seq', 'par1', 'par2'], sep=';'))
    t2.append(pd.read_csv(f"particlesTest/{filename}", names = ['x', 'seq', 'par'], sep=';'))
    t3.append(pd.read_csv(f"threadsTest/{filename}", names = ['x', 'seq', 'par'], sep=';'))
    t3_2.append(pd.read_csv(f"threadsTestV2/{filename}", names = ['x', 'par1', 'par2', 'par3'], sep=';'))
    t4.append(pd.read_csv(f"lockTest/{filename}", names = ['x', 'Sequenziale', 'Parallelo senza lock', 'Parallelo con lock'], sep=';'))
    
def compute_mean(df_list, filename):
    df = pd.concat(df_list).reset_index(drop=True)
    for col in df.columns:
        if col != "x":
            df.loc[df.groupby("x")[col].idxmin(), col] = np.nan
            df.loc[df.groupby("x")[col].idxmax(), col] = np.nan
    df = df.groupby("x").mean().reset_index()
    for col in df.columns:
        if col != "x":
            df[col] = df[col].round(decimals = 3)
    df.to_csv(filename, header = None, index = None, sep = ';')
    return df

t1 = compute_mean(t1, "dimTest/result.csv")
t1_2 = compute_mean(t1_2, "dimTestV2/result.csv")
t2 = compute_mean(t2, "particlesTest/result.csv")
t3 = compute_mean(t3, "threadsTest/result.csv")
t3_2 = compute_mean(t3_2, "threadsTestV2/result.csv")
t4 = compute_mean(t4, "lockTest/result.csv")

t4 = t4.drop(['x'], axis=1)
t4[['Sequenziale', 'Parallelo senza lock', 'Parallelo con lock']] = t4[['Sequenziale', 'Parallelo senza lock', 'Parallelo con lock']].astype(str) + " ms"
t4.to_csv("lockTest/result.csv", index = None, sep = ';')



plt.plot(t1["x"], t1["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t1["x"], t1["par"], color = 'red', label = 'parallelo')
plt.xlabel("dimensioni labirinto (numero di celle)")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("dimTest/result.png")
plt.clf()

plt.plot(t1_2["x"], t1_2["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t1_2["x"], t1_2["par1"], color = 'red', label = 'threads = 2')
plt.plot(t1_2["x"], t1_2["par2"], color = 'green', label = 'threads = 10')
plt.xlabel("dimensioni labirinto (numero di celle)")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("dimTestV2/result.png")
plt.clf()

plt.plot(t2["x"], t2["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t2["x"], t2["par"], color = 'red', label = 'parallelo')
plt.xlabel("numero di particelle")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("particlesTest/result.png")
plt.clf()


plt.plot(t3["x"], t3["seq"], color = 'blue', label = 'sequenziale')
plt.plot(t3["x"], t3["par"], color = 'red', label = 'parallelo')
plt.xlabel("numero di thread")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("threadsTest/result.png")
plt.clf()

plt.plot(t3_2["x"], t3_2["par1"], color = 'blue', label = 'threads = 10')
plt.plot(t3_2["x"], t3_2["par2"], color = 'red', label = 'threads = 100')
plt.plot(t3_2["x"], t3_2["par3"], color = 'green', label = 'threads = 500')
plt.xlabel("numero di particelle")
plt.ylabel("tempo in ms")
plt.legend(loc="upper left")
plt.savefig("threadsTestV2/result.png")
plt.clf()

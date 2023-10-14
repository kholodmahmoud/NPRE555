import numpy as np
from matplotlib import pyplot as plt

data = np.genfromtxt('flux_output.txt')
x = np.linspace(0,1,10)
plt.figure(figsize=(8,7))
plt.plot(x,data,marker='*',color='g')
plt.xlabel("Thickness (m)",fontsize=16)
plt.ylabel("Flux (N/cm2*s)",fontsize=16)
plt.legend(fontsize=10)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend()
plt.grid(True)
plt.savefig("Flux")

plt.show()

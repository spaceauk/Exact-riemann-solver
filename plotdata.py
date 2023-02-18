import numpy as np
import matplotlib.pyplot as plt
from os import listdir
import sys

print("Plotting graphs...")
n=int(sys.argv[1])

datapath = "./data/"
allfiles=listdir(datapath)
allfiles_sorted=sorted(allfiles)

for fil_name in allfiles_sorted:
    fname=datapath+fil_name
    print(fname)
    data=np.loadtxt(fname)
    x=np.reshape(data[:,0],n)
    den=np.reshape(data[:,1],n)
    u=np.reshape(data[:,2],n)
    P=np.reshape(data[:,3],n)
    ie=np.reshape(data[:,4],n)
    fig, axs=plt.subplots(2,2)
    axs[0,0].plot(x,den)
    axs[0,0].set_title("Exact Riemann solver")
    axs[0,0].set(ylabel="Density")
    axs[0,1].plot(x,u)
    axs[0,1].set(ylabel="U_vel")
    axs[0,1].set_title(fil_name)
    axs[1,0].plot(x,P)
    axs[1,0].set(ylabel="Pressure")
    axs[1,1].plot(x,ie)
    axs[1,1].set(ylabel="Internal energy")
    for ax in axs.flat:
        ax.set(xlabel='x')
        ax.grid()
    plt.show()
    #plt.savefig(fname+'.png')
    plt.clf

print("Plotting done!")


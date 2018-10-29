from heatermod import HeaterCustom
import numpy as np
import time

h = HeaterCustom()

dm_water = 0.1
P_natural_gas = 10000
Tin = 298;		           

u = np.array([dm_water,P_natural_gas,Tin] )
dt = np.array([1.0])


h.Initialize(u)
t0 = time.time()
while h.GetTime() < 1000:
    h.CalculateLargeStep(u, dt)

t1  =time.time()
print(t1-t0)


h.Initialize(u)
t2 = time.time()
dt = np.array([10.0])
while h.GetTime() < 1000:
    h.CalculateLargeStep(u, dt)

t3 = time.time()
print(t3-t2)

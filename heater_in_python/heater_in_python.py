from heatermod import Heater
from environment import Environment
import numpy as np
import time
from matplotlib import pyplot as plt
from simple_pid import PID

# Settings
dt = 1.0
nCycles = 3
T_sp = 453 # Setpoint in K

# Heater
h = Heater()

# Environment
env = Environment('environment_1.pkl')
tEnd = env.t_cycle * nCycles

# Controller
# Create PID controller with typical setting for current problem
pid = PID(200, 20, 10, setpoint=T_sp , sample_time=dt, output_limits=(0, 10000) )



# Initialize
P_initial = 0
u_initial = np.concatenate( (np.array([P_initial]) , env(0) ) )
h.init(u_initial)
t = h.getTime()

t0 = time.time()

# Allocate memory for output
nt = int(tEnd / dt + 5)
Y  = np.zeros((nt,11))
T  = np.zeros((nt))
U  = np.zeros((nt,3))


# Loop
it = 0
P = 0
while t < tEnd:
    # Get current time of simulation model
    t = h.getTime()

    # Build input vector
    u = np.concatenate( (np.array([P]) , env(t) ) )

    # Simulate time step
    y = h.calc(u, dt)

    # Determine power setting for next iteration:
    #P = max(0,min(10000,300 * (453 - y[1])))    # Proportional controller
    P =  pid(y[6],dt)                            # PID controller
    #P = 9000                                    # Constant power

    # Store in output buffer
    Y[it,:] = y[:]
    T[it]   = t
    U[it,:] = u[:] 

    it = it + 1



# Plot data
fig, (ax1, ax2, ax3) = plt.subplots(3, 1)

ax1.plot(T[0:it],Y[0:it,10] , color=plt.cm.jet(100) , linestyle='-' ,label="layer 5, water")
ax1.plot(T[0:it],Y[0:it,9] , color=plt.cm.jet(125) , linestyle='-'  ,label="layer 4, water")
ax1.plot(T[0:it],Y[0:it,8] , color=plt.cm.jet(150) , linestyle='-'  ,label="layer 3, water")
ax1.plot(T[0:it],Y[0:it,7] , color=plt.cm.jet(175) , linestyle='-'  ,label="layer 2, water")
ax1.plot(T[0:it],Y[0:it,6] , color=plt.cm.jet(225) , linestyle='-'  ,label="Output")
ax1.plot(T[0:it],Y[0:it,5] , color=plt.cm.jet(100) , linestyle=':'  ,label="layer 5, steel")
ax1.plot(T[0:it],Y[0:it,4] , color=plt.cm.jet(125) , linestyle=':'  ,label="layer 4, steel")
ax1.plot(T[0:it],Y[0:it,3] , color=plt.cm.jet(150) , linestyle=':'  ,label="layer 3, steel")
ax1.plot(T[0:it],Y[0:it,2] , color=plt.cm.jet(175) , linestyle=':'  ,label="layer 2, steel")
ax1.plot(T[0:it],Y[0:it,1] , color=plt.cm.jet(225) , linestyle=':'  ,label="layer 1, steel")
ax1.plot(T[0:it],U[0:it,1] , color=plt.cm.jet(0  ) , linestyle='-'  ,label="Input")
ax1.set_ylabel('Temperature (degC)')
ax1.legend(fontsize=4)

ax2.plot(T[0:it],U[0:it,0] , color=plt.cm.hsv(100) , linestyle='-' )
ax2.plot(T[0:it],Y[0:it,0] , color=plt.cm.hsv(200) , linestyle='-' )
ax2.set_ylabel('Power (W)')

ax3.plot(T[0:it],U[0:it,2] , color=plt.cm.hsv(130) , linestyle='-' )
ax3.set_xlabel('time (s)')
ax3.set_ylabel('water flow (kg/s)')



# Analyze last cycle
idx = np.logical_and( T >= (nCycles-1)*env.t_cycle , T < nCycles*env.t_cycle )

t = T[idx]
dT = Y[idx,6]-U[idx,1]
dm = U[idx,2]
cp = 4180
dt = max(t) - min(t)
error = Y[idx,6] - T_sp

print("Error:")
print("std = %f" % error.std())
print("avg = %f" % error.mean())
print("min = %f" % error.min())
print("max = %f" % error.max())


plt.show()

import pandas as pd
import numpy as np
from scipy.interpolate import interp1d
class Environment(object):
    
    def __init__(self,environment='environment_1.pkl'):
        '''
        Environment class
        :param str environment: filename containing environment data
        '''
        self.environment = environment

        # Pandas DataFrame that contains measurement data of 
        # flow rate and input temperature. Two cycles are stored
        # in the dataset
        df = pd.read_pickle(environment)

        # Extract time values and rescale to seconds
        t = df.index.values.astype('int64')*1e-9
        t = t - t[0]
        self.t_cycle = t[-1]

        # Extract input temperature and convert to K
        y0 = df.crio01_TT2_HTF_htr_ret.values + 273.15

        # Extract flow rate and convert to kg/s
        y1 = df.ws01_FT1_HTF_hot.values / 60.0 

        # Combine flow rate and input temperature in single matrix
        y = np.array([y0,y1])

        # Define interpolation function
        f = interp1d(t,y)

        # Define lambda function which takes modulus of input time to create 
        # periodic function
        self.fp = lambda t: np.transpose(f(t%self.t_cycle))


    def __call__(self,t):
        '''
        Evaluate the environment
        :param numpy.ndarray t: Scalar or vector containing time
        :return: vector containing: mass flow {kg/s}, input temperature {K}
        :rtype: numpy.ndarray
        '''
        return self.fp(t)
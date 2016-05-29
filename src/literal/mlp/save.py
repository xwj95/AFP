import scipy.io as spio
import numpy as np

def result(w1, b1, w2, b2, w3, b3, w4, b4, w5, b5):
	spio.savemat('net.mat', {'w1': w1, 'b1': b1, 'w2': w2, 'b2': b2, 'w3': w3, 'b3': b3, 'w4': w4, 'b4': b4, 'w5': w5, 'b5': b5})

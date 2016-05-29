import scipy.io as spio
import numpy as np

def one_hot(x, n):
	o_h = np.zeros((n, x.size))
	o_h[x - 1, np.arange(x.size)] = 1
	return o_h

def dataset(onehot = True):
	data = spio.loadmat('data_mlp.mat', struct_as_record = True)
	train_x = data['trainX'].astype(float)
	train_y = data['trainY'].astype(int)
	test_x = data['testX'].astype(float)
	test_y = data['testY'].astype(int)

	if onehot:
		train_y = one_hot(train_y, 20)
		test_y = one_hot(test_y, 20)

	train_x = train_x.T
	train_y = train_y.T
	test_x = test_x.T
	test_y = test_y.T

	return train_x, train_y, test_x, test_y

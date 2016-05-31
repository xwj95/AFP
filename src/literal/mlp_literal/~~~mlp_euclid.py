import theano
import theano.tensor as T
import scipy.io as spio
import numpy as np
import time

def floatX(X):
	return np.asarray(X, dtype = theano.config.floatX)

def init_weights(shape):
	return theano.shared(floatX(np.random.randn(*shape) * 0.1))

def init_bias(length):
	return theano.shared(floatX(np.zeros(length)))

def sgd(cost, params, learning_rate):
	grads = T.grad(cost = cost, wrt = params)
	updates = []
	for p, g in zip(params, grads):
		updates.append([p, p - g * learning_rate])
	return updates

def relu(X):
    return T.maximum(X, 0.)

def euclid(X, Y):
	return T.mean(T.sum((X - Y) ** 2, axis = 0))

def model(X, w1, b1, w2, b2, w3, b3, w4, b4, w5, b5, activation = 'relu'):
	if (activation == 'relu'):
		h1 = relu(T.dot(X, w1) + b1)
		h2 = relu(T.dot(h1, w2) + b2)
		h3 = relu(T.dot(h2, w3) + b3)
		h4 = relu(T.dot(h3, w4) + b4)
		h5 = relu(T.dot(h4, w5) + b5)
	else:
		h1 = T.nnet.sigmoid(T.dot(X, w1) + b1)
		h2 = T.nnet.sigmoid(T.dot(h1, w2) + b2)
		h3 = T.nnet.sigmoid(T.dot(h2, w3) + b3)
		h4 = T.nnet.sigmoid(T.dot(h3, w4) + b4)
		h5 = T.nnet.sigmoid(T.dot(h4, w5) + b5)
	return h5

def mlp_euclid(train_x, train_y, test_x, test_y, activation = 'relu', learning_rate = 0.05, batch = 100, epochs = 2000):
	X = T.fmatrix()
	Y = T.fmatrix()

	w1 = init_weights((7060, 1500))
	b1 = init_bias(1500)
	w2 = init_weights((1500, 300))
	b2 = init_bias(300)
	w3 = init_weights((300, 60))
	b3 = init_bias(60)
	w4 = init_weights((60, 10))
	b4 = init_bias(10)
	w5 = init_weights((10, 2))
	b5 = init_bias(2)

	py_x = model(X, w1, b1, w2, b2, w3, b3, w4, b4, w5, b5, activation = activation)
	y_pred = T.argmax(py_x, axis = 1)

	cost = euclid(py_x, Y)
	params = [w1, b1, w2, b2, w3, b3, w4, b4, w5, b5]
	update = sgd(cost, params, learning_rate)

	train = theano.function(inputs = [X, Y], outputs = cost, updates = update, allow_input_downcast = True)
	predict = theano.function(inputs = [X], outputs = y_pred, allow_input_downcast = True)

	now = time.strftime('%X', time.localtime())
	print '[%s] Start training' % (now)
	for epoch in range(epochs):
		for start, end in zip(range(0, train_x.shape[0], batch), range(batch, train_x.shape[0], batch)):
			cost = train(train_x[start:end, :], train_y[start:end, :])
		accuracy = float(np.sum(np.argmax(train_y, axis = 1) == predict(train_x))) / train_y.shape[0]
		now = time.strftime('%X', time.localtime())
		print '[%s] epoch %d, train accuracy = %.4f' % (now, epoch + 1, accuracy)

	list_w1 = w1.get_value(borrow = True)
	list_b1 = b1.get_value(borrow = True)
	list_w2 = w2.get_value(borrow = True)
	list_b2 = b2.get_value(borrow = True)
	list_w3 = w3.get_value(borrow = True)
	list_b3 = b3.get_value(borrow = True)
	list_w4 = w4.get_value(borrow = True)
	list_b4 = b4.get_value(borrow = True)
	list_w5 = w5.get_value(borrow = True)
	list_b5 = b5.get_value(borrow = True)

	return list_w1, list_b1, list_w2, list_b2, list_w3, list_b3, list_w4, list_b4, list_w5, list_b5

def one_hot(x, n):
	o_h = np.zeros((n, x.size))
	o_h[x - 1, np.arange(x.size)] = 1
	return o_h

def load(onehot = True):
	data = spio.loadmat('data_mlp.mat', struct_as_record = True)
	train_x = data['trainX'].astype(float)
	train_y = data['trainY'].astype(int)
	test_x = data['testX'].astype(float)
	test_y = data['testY'].astype(int)

	if onehot:
		train_y = one_hot(train_y, 2)
		test_y = one_hot(test_y, 2)

	train_x = train_x.T
	train_y = train_y.T
	test_x = test_x.T
	test_y = test_y.T

	return train_x, train_y, test_x, test_y

def save(w1, b1, w2, b2, w3, b3, w4, b4, w5, b5):
	spio.savemat('net.mat', {'w1': w1, 'b1': b1, 'w2': w2, 'b2': b2, 'w3': w3, 'b3': b3, 'w4': w4, 'b4': b4, 'w5': w5, 'b5': b5})

train_x, train_y, test_x, test_y = load(onehot = True)
list_w1, list_b1, list_w2, list_b2, list_w3, list_b3, list_w4, list_b4, list_w5, list_b5 = mlp_euclid(train_x, train_y, test_x, test_y)
save(list_w1, list_b1, list_w2, list_b2, list_w3, list_b3, list_w4, list_b4, list_w5, list_b5)

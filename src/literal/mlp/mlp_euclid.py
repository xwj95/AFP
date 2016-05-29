import theano
import theano.tensor as T
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

	w1 = init_weights((198, 162))
	b1 = init_bias(162)
	w2 = init_weights((162, 96))
	b2 = init_bias(96)
	w3 = init_weights((96, 64))
	b3 = init_bias(64)
	w4 = init_weights((64, 36))
	b4 = init_bias(36)
	w5 = init_weights((36, 20))
	b5 = init_bias(20)

	py_x = model(X, w1, b1, w2, b2, w3, b3, w4, b4, w5, b5, activation = activation)
	y_pred = T.argmax(py_x, axis = 1)

	cost = euclid(py_x, Y)
	params = [w1, b1, w2, b2, w3, b3, w4, b4, w5, b5]
	update = sgd(cost, params, learning_rate)

	train = theano.function(inputs = [X, Y], outputs = cost, updates = update, allow_input_downcast = True)
	predict = theano.function(inputs = [X], outputs = y_pred, allow_input_downcast = True)

	now = time.strftime('%X', time.localtime())
	print '[%s] Start training' %(now)
	for epoch in range(epochs):
		for start, end in zip(range(0, train_x.shape[0], batch), range(batch, train_x.shape[0], batch)):
			cost = train(train_x[start:end, :], train_y[start:end, :])
		accuracy = float(np.sum(np.argmax(train_y, axis = 1) == predict(train_x))) / train_y.shape[0]
		now = time.strftime('%X', time.localtime())
		print '[%s] epoch %d, train accuracy = %.4f' %(now, epoch + 1, accuracy)
		accuracy = float(np.sum(np.argmax(test_y, axis = 1) == predict(test_x))) / test_y.shape[0]
		now = time.strftime('%X', time.localtime())
		print '[%s] epoch %d, test accuracy = %.4f' %(now, epoch + 1, accuracy)
		if accuracy > 0.44:
			break;

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

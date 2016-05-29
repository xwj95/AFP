from load import dataset
from save import result
from mlp_euclid import mlp_euclid

train_x, train_y, test_x, test_y = dataset(onehot = True)
list_w1, list_b1, list_w2, list_b2, list_w3, list_b3, list_w4, list_b4, list_w5, list_b5 = mlp_euclid(train_x, train_y, test_x, test_y)
result(list_w1, list_b1, list_w2, list_b2, list_w3, list_b3, list_w4, list_b4, list_w5, list_b5)

clear;
load('net/data.mat');
split = 90000;
n = size(train_x, 2);
test_x = train_x(:, split+1:n);
test_y = train_y(:, split+1:n);
train_x = train_x(:, 1:split);
train_y = train_y(:, 1:split);
save('data.mat', 'train_x', 'train_y', 'test_x', 'test_y', '-v7.3');

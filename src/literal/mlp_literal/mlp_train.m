clear;

model = Network();
model = add(model, fcLayer('fc1',7060,500,0.01,0.001,0.005,0.9));
model = add(model, Relu('relu1'));
model = add(model, fcLayer('fc2',500,30,0.01,0.001,0.005,0.9));
model = add(model, Relu('relu2'));
model = add(model, fcLayer('fc3',30,2,0.01,0.001,0.005,0.9));
model = add(model, Relu('relu3'));
model = add(model, euclideanLossLayer('loss'));

load('data.mat');

% mean_value = mean(train_x, 2);
% train_x = bsxfun(@minus, train_x, mean_value);
% test_x = bsxfun(@minus, test_x, mean_value);

epoch = 20;
model = Fit_mlp(model, train_x, train_y, test_x, test_y,...
	100, epoch, 1, epoch, epoch);

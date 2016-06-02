clear;
load('data.mat');
load('net_iter_200.mat');
% load('net_iter_10.mat');

test_data = test_x;
test_label = test_y;
batchsize = 100;

num_test_input = size(test_data, 2);
test_iters = ceil(num_test_input / batchsize);
test_loss = [];
test_indx = [];
test_accuracy = [];
for j = 1:test_iters
    [lss, pred_indx, acc] = Predict(net, test_data(:,(j-1)*batchsize+1:min(j*batchsize, num_test_input)),...
        test_label(:,(j-1)*batchsize+1:min(j*batchsize, num_test_input)));
    test_loss = [test_loss, lss];
    test_indx = [test_indx, pred_indx];
    test_accuracy = [test_accuracy, acc];
end
save('result.mat', 'test_indx');
test_mean_loss = mean(test_loss);
test_mean_accuracy = mean(test_accuracy);
now = clock;
fprintf('[%02d:%02d:%05.2f]   test results: loss %.5f, accuracy %.4f\n',...
now(4), now(5), now(6), test_mean_loss, test_mean_accuracy);

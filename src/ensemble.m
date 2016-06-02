clear;
load('literal/mlp_literal/data.mat');

load('literal/mlp_literal/net_validate1/result.mat');
test_indx1 = test_indx - 1;
load('literal/mlp_literal/net_validate2/result.mat');
test_indx2 = test_indx - 1;
load('literal/mlp_literal/net_validate3/result.mat');
test_indx3 = test_indx - 1;
load('literal/mlp_literal/net_validate4/result.mat');
test_indx4 = test_indx - 1;
load('literal/mlp_literal/net_validate5/result.mat');
test_indx5 = test_indx - 1;
load('literal/mlp_literal/net_validate6/result.mat');
test_indx6 = test_indx - 1;
load('literal/mlp_literal/net_validate7/result.mat');
test_indx7 = test_indx - 1;
load('literal/mlp_literal/net_validate8/result.mat');
test_indx8 = test_indx - 1;
load('literal/mlp_literal/net_validate9/result.mat');
test_indx9 = test_indx - 1;
load('literal/mlp_literal/net_validate10/result.mat');
test_indx10 = test_indx - 1;
load('literal/mlp_literal/net_validate11/result.mat');
test_indx11 = test_indx - 1;

n = 11;
test_indx = test_indx1 + test_indx2 + test_indx3 + test_indx4 + ...
    test_indx5 + test_indx6 + test_indx7 + test_indx8 + test_indx9 + ...
    test_indx10 + test_indx11;
for i = 1:length(test_indx)
    if test_indx(i) >= n/2
        test_indx(i) = 1;
    else
        test_indx(i) = 0;
    end
end
accuracy = sum(test_indx == (test_y - 1)) / length(test_indx);
fprintf('Bagging accuracy = %f\n', accuracy);

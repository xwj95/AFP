clear;
train_v = textread('../txt/train_literal.txt');
train_y = textread('../txt/train_label.txt');
test_v = textread('../txt/test_literal.txt');
test_y = zeros(size(test_v, 1), 1);

train_x = zeros(size(train_v, 1), 7060);
for i = 1:size(train_v, 1)
    for j = 1:size(train_v, 2)
        if train_v(i, j) < 0
            break;
        end
        train_x(i, train_v(i, j) + 1) = 1;
    end
end
train_y = train_y + 1;
test_x = zeros(size(test_v, 1), 7060);
for i = 1:size(test_v, 1)
    for j = 1:size(test_v, 2)
        if test_v(i, j) < 0
            break;
        end
        test_x(i, test_v(i, j) + 1) = 1;
    end
end
test_y = test_y + 1;

train_x = train_x';
train_y = train_y';
test_x = test_x';
test_y = test_y';

save('data.mat', 'train_x', 'train_y', 'test_x', 'test_y', '-v7.3');

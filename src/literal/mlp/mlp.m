function result = mlp(img)
    load('net.mat');
    h0 = img';
    h1 = max(h0 * w1 + b1, 0);
    h2 = max(h1 * w2 + b2, 0);
    h3 = max(h2 * w3 + b3, 0);
    h4 = max(h3 * w4 + b4, 0);
    h5 = max(h4 * w5 + b5, 0);
    [~, result] = max(h5);
end

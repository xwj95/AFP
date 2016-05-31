classdef euclideanLossLayer
    
    properties
        name;
        input;
        input_shape;
        
        output;
        delta;
        loss;
        accuracy;
    end
    
    methods
        function layer = euclideanLossLayer(name)
            layer.name = name;
        end
    
        function layer = forward(layer, input)
            layer.input = input;
            layer.output = layer.input;
        end
        
        function layer = backprop(layer, label)
            layer.loss = sum(sum(layer.delta.^2)) / 2;
            [~, pred_indx] = max(layer.output);
            layer.accuracy = sum(pred_indx == label) / size(label, 2);
            layer.delta = zeros(size(layer.output));
            for k = 1:size(layer.output,2)
                layer.delta(label(k),k) = 1;
            end
            layer.delta = layer.output - layer.delta;
        end
    end
end
